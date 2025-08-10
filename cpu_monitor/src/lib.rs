use serde::{Deserialize, Serialize};
use std::ffi::CString;
use std::os::raw::c_char;
use std::time::{Duration, Instant};
use std::io;
use std::fs;
use chrono::{DateTime, Local};

#[derive(Serialize, Deserialize, Default, Debug)]
struct SystemMetrics {
    timestamp: String,
    cpu_usage: f64,
    cpu_freq: u64,
    gpu_usage: f64,
    gpu_freq: u64,
    npu_usage: f64,
    npu_freq: u64,
    rga_usage: f64,
    rga_aclk_freq: u64,
    rga_core_freq: u64,
    rga_hclk_freq: u64,
    memory_usage: f64,
    swap_usage: f64,
    temperature: f64,
    fan_state: u32,
}

fn read_file_safe(path: &str) -> Option<String> {
    fs::read_to_string(path).ok()
}

fn parse_cpu_stats() -> f64 {
    if let Some(content) = read_file_safe("/proc/stat") {
        if let Some(line) = content.lines().next() {
            let parts: Vec<&str> = line.split_whitespace().collect();
            if parts.len() >= 5 && parts[0] == "cpu" {
                let user: u64 = parts[1].parse().unwrap_or(0);
                let nice: u64 = parts[2].parse().unwrap_or(0);
                let system: u64 = parts[3].parse().unwrap_or(0);
                let idle: u64 = parts[4].parse().unwrap_or(0);
                let total = user + nice + system + idle;
                let active = total - idle;
                if total > 0 {
                    return (active as f64 / total as f64) * 100.0;
                }
            }
        }
    }
    0.0
}

fn get_cpu_frequency() -> u64 {
    // Try multiple CPU cores
    for cpu_id in 0..8 {
        let path = format!("/sys/devices/system/cpu/cpu{}/cpufreq/scaling_cur_freq", cpu_id);
        if let Some(content) = read_file_safe(&path) {
            if let Ok(freq) = content.trim().parse::<u64>() {
                return freq * 1000; // Convert kHz to Hz
            }
        }
    }
    0
}

fn get_gpu_usage() -> f64 {
    // Try the path you specified for RK3588
    if let Some(content) = read_file_safe("/sys/class/devfreq/ff700000.gpu/load") {
        if let Some(load_str) = content.split('@').next() {
            if let Ok(load) = load_str.trim().parse::<f64>() {
                return load;
            }
        }
    }
    
    // Fallback to NVML for NVIDIA GPUs
    match nvml_wrapper::Nvml::init() {
        Ok(nvml) => {
            if let Ok(device_count) = nvml.device_count() {
                if device_count > 0 {
                    if let Ok(device) = nvml.device_by_index(0) {
                        if let Ok(utilization) = device.utilization_rates() {
                            return utilization.gpu as f64;
                        }
                    }
                }
            }
        }
        Err(_) => {}
    }
    
    0.0
}

fn get_gpu_frequency() -> u64 {
    if let Some(content) = read_file_safe("/sys/class/devfreq/ff700000.gpu/cur_freq") {
        if let Ok(freq) = content.trim().parse::<u64>() {
            return freq;
        }
    }
    0
}

fn get_npu_usage() -> f64 {
    if let Some(content) = read_file_safe("/sys/kernel/debug/rknpu/load") {
        // Parse NPU load format
        for line in content.lines() {
            if line.contains("NPU load:") {
                if let Some(load_str) = line.split(':').nth(1) {
                    if let Some(percent_str) = load_str.split('%').next() {
                        if let Ok(load) = percent_str.trim().parse::<f64>() {
                            return load;
                        }
                    }
                }
            }
        }
    }
    0.0
}

fn get_npu_frequency() -> u64 {
    if let Some(content) = read_file_safe("/sys/class/devfreq/fdab0000.npu/cur_freq") {
        if let Ok(freq) = content.trim().parse::<u64>() {
            return freq;
        }
    }
    0
}

fn get_rga_usage() -> f64 {
    if let Some(content) = read_file_safe("/sys/kernel/debug/rkrga/load") {
        // Parse RGA load format
        for line in content.lines() {
            if line.contains("load:") {
                if let Some(load_str) = line.split(':').nth(1) {
                    if let Some(percent_str) = load_str.split('%').next() {
                        if let Ok(load) = percent_str.trim().parse::<f64>() {
                            return load;
                        }
                    }
                }
            }
        }
    }
    0.0
}

fn get_rga_frequencies() -> (u64, u64, u64) {
    let mut aclk_freq = 0u64;
    let mut core_freq = 0u64;
    let mut hclk_freq = 0u64;
    
    if let Some(content) = read_file_safe("/sys/kernel/debug/clk/clk_summary") {
        for line in content.lines() {
            if line.contains("aclk_rga2e") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                if parts.len() >= 5 {
                    if let Ok(freq) = parts[4].parse::<u64>() {
                        aclk_freq = freq;
                    }
                }
            } else if line.contains("clk_core_rga2e") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                if parts.len() >= 5 {
                    if let Ok(freq) = parts[4].parse::<u64>() {
                        core_freq = freq;
                    }
                }
            } else if line.contains("hclk_rga2e") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                if parts.len() >= 5 {
                    if let Ok(freq) = parts[4].parse::<u64>() {
                        hclk_freq = freq;
                    }
                }
            }
        }
    }
    (aclk_freq, core_freq, hclk_freq)
}

fn get_memory_info() -> (f64, f64) {
    if let Some(content) = read_file_safe("/proc/meminfo") {
        let mut mem_total = 0u64;
        let mut mem_available = 0u64;
        let mut swap_total = 0u64;
        let mut swap_free = 0u64;

        for line in content.lines() {
            if line.starts_with("MemTotal:") {
                mem_total = line.split_whitespace().nth(1).unwrap_or("0").parse().unwrap_or(0);
            } else if line.starts_with("MemAvailable:") {
                mem_available = line.split_whitespace().nth(1).unwrap_or("0").parse().unwrap_or(0);
            } else if line.starts_with("SwapTotal:") {
                swap_total = line.split_whitespace().nth(1).unwrap_or("0").parse().unwrap_or(0);
            } else if line.starts_with("SwapFree:") {
                swap_free = line.split_whitespace().nth(1).unwrap_or("0").parse().unwrap_or(0);
            }
        }

        let memory_usage = if mem_total > 0 {
            ((mem_total - mem_available) as f64 / mem_total as f64) * 100.0
        } else {
            0.0
        };

        let swap_usage = if swap_total > 0 {
            ((swap_total - swap_free) as f64 / swap_total as f64) * 100.0
        } else {
            0.0
        };

        return (memory_usage, swap_usage);
    }
    (0.0, 0.0)
}

fn get_temperature() -> f64 {
    if let Some(content) = read_file_safe("/sys/class/thermal/thermal_zone0/temp") {
        if let Ok(temp) = content.trim().parse::<f64>() {
            return temp;
        }
    }
    0.0
}

fn get_fan_state() -> u32 {
    if let Some(content) = read_file_safe("/sys/class/thermal/cooling_device4/cur_state") {
        if let Ok(state) = content.trim().parse::<u32>() {
            return state;
        }
    }
    0
}

fn collect_system_metrics() -> SystemMetrics {
    let (memory_usage, swap_usage) = get_memory_info();
    let (rga_aclk, rga_core, rga_hclk) = get_rga_frequencies();
    
    SystemMetrics {
        timestamp: Local::now().to_string(),
        cpu_usage: parse_cpu_stats(),
        cpu_freq: get_cpu_frequency(),
        gpu_usage: get_gpu_usage(),
        gpu_freq: get_gpu_frequency(),
        npu_usage: get_npu_usage(),
        npu_freq: get_npu_frequency(),
        rga_usage: get_rga_usage(),
        rga_aclk_freq: rga_aclk,
        rga_core_freq: rga_core,
        rga_hclk_freq: rga_hclk,
        memory_usage,
        swap_usage,
        temperature: get_temperature(),
        fan_state: get_fan_state(),
    }
}

#[no_mangle]
pub extern "C" fn get_system_metrics_json() -> *mut c_char {
    let metrics = collect_system_metrics();
    let json = serde_json::to_string(&metrics).unwrap();
    CString::new(json).unwrap().into_raw()
}

#[no_mangle]
pub extern "C" fn free_string(s: *mut c_char) {
    if s.is_null() { return }
    unsafe {
        let _ = CString::from_raw(s);
    }
}
