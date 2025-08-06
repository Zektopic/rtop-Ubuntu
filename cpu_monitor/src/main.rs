use std::time::{Duration, Instant};
use std::io;
use std::fs;
use chrono::{DateTime, Local};
use crossterm::{
    event::{self, DisableMouseCapture, EnableMouseCapture, Event, KeyCode},
    execute,
    terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen},
};
use ratatui::{
    backend::{Backend, CrosstermBackend},
    layout::{Constraint, Direction, Layout},
    style::{Color, Modifier, Style},
    symbols,
    widgets::{
        Axis, Block, Borders, Chart, Dataset, GraphType, Paragraph, Tabs
    },
    Frame, Terminal, text::{Line, Span},
};

#[derive(Default, Debug)]
struct SystemMetrics {
    timestamp: DateTime<Local>,
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

#[derive(Default)]
struct App {
    metrics_history: Vec<SystemMetrics>,
    time_counter: f64,
    current_tab: usize,
    tab_titles: Vec<String>,
}

impl App {
    fn new() -> App {
        App {
            metrics_history: Vec::new(),
            time_counter: 0.0,
            current_tab: 0,
            tab_titles: vec![
                "CPU".to_string(),
                "GPU".to_string(),
                "NPU".to_string(),
                "RGA".to_string(),
                "Memory".to_string(),
                "Thermal".to_string(),
            ],
        }
    }

    fn update(&mut self, metrics: SystemMetrics) {
        self.metrics_history.push(metrics);
        
        // Keep only last 600 data points (2 minutes of data at 200ms intervals)
        if self.metrics_history.len() > 600 {
            self.metrics_history.remove(0);
        }
        
        self.time_counter += 0.2; // 200ms interval
    }

    fn get_data_for_chart(&self, metric_type: &str) -> (Vec<(f64, f64)>, (f64, f64)) {
        let mut data = Vec::new();
        let mut min_val = f64::MAX;
        let mut max_val = f64::MIN;

        for (i, metrics) in self.metrics_history.iter().enumerate() {
            let value = match metric_type {
                "cpu_usage" => metrics.cpu_usage,
                "cpu_freq" => metrics.cpu_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "gpu_usage" => metrics.gpu_usage,
                "gpu_freq" => metrics.gpu_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "npu_usage" => metrics.npu_usage,
                "npu_freq" => metrics.npu_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "rga_usage" => metrics.rga_usage,
                "rga_aclk_freq" => metrics.rga_aclk_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "rga_core_freq" => metrics.rga_core_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "rga_hclk_freq" => metrics.rga_hclk_freq as f64 / 1_000_000.0, // Convert Hz to MHz
                "memory_usage" => metrics.memory_usage,
                "swap_usage" => metrics.swap_usage,
                "temperature" => metrics.temperature / 1000.0, // Convert millidegrees to degrees
                "fan_state" => metrics.fan_state as f64,
                _ => 0.0,
            };

            data.push((i as f64 * 0.2, value));
            if value < min_val { min_val = value; }
            if value > max_val { max_val = value; }
        }

        // Add some padding to the Y-axis bounds
        let padding = (max_val - min_val) * 0.1;
        let y_bounds = if max_val == min_val {
            (0.0, max_val + 10.0)
        } else {
            ((min_val - padding).max(0.0), max_val + padding)
        };

        (data, y_bounds)
    }

    fn next_tab(&mut self) {
        self.current_tab = (self.current_tab + 1) % self.tab_titles.len();
    }

    fn previous_tab(&mut self) {
        if self.current_tab > 0 {
            self.current_tab -= 1;
        } else {
            self.current_tab = self.tab_titles.len() - 1;
        }
    }
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

fn get_device_info() -> String {
    if let Some(content) = read_file_safe("/sys/firmware/devicetree/base/compatible") {
        return content.replace('\0', ", ");
    }
    "Unknown".to_string()
}

fn collect_system_metrics() -> SystemMetrics {
    let (memory_usage, swap_usage) = get_memory_info();
    let (rga_aclk, rga_core, rga_hclk) = get_rga_frequencies();
    
    SystemMetrics {
        timestamp: Local::now(),
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

fn draw_ui(f: &mut Frame, app: &App) {
    let chunks = Layout::default()
        .direction(Direction::Vertical)
        .margin(1)
        .constraints([
            Constraint::Length(3),
            Constraint::Length(3),
            Constraint::Length(3),
            Constraint::Min(0),
        ])
        .split(f.size());

    // Title with device info
    let device_info = get_device_info();
    let title = Paragraph::new(format!("System Monitor - {} - Press 'q' to quit, ←/→ to switch tabs", device_info))
        .style(Style::default().fg(Color::Cyan).add_modifier(Modifier::BOLD))
        .block(Block::default().borders(Borders::ALL));
    f.render_widget(title, chunks[0]);

    // Tabs
    let titles: Vec<ratatui::text::Line> = app.tab_titles
        .iter()
        .map(|t| Line::from(vec![Span::styled(t.clone(), Style::default().fg(Color::White))]))
        .collect();
    
    let tabs = Tabs::new(titles)
        .block(Block::default().borders(Borders::ALL).title("Metrics"))
        .select(app.current_tab)
        .style(Style::default().fg(Color::White))
        .highlight_style(Style::default().fg(Color::Yellow).add_modifier(Modifier::BOLD));
    f.render_widget(tabs, chunks[1]);

    // Current metrics display with values
    if let Some(latest) = app.metrics_history.last() {
        let info_text = match app.current_tab {
            0 => format!("CPU Usage: {:.1}% | Frequency: {:.0} MHz | Last Update: {}", 
                        latest.cpu_usage, latest.cpu_freq as f64 / 1_000_000.0, latest.timestamp.format("%H:%M:%S")),
            1 => format!("GPU Usage: {:.1}% | Frequency: {:.0} MHz | Last Update: {}", 
                        latest.gpu_usage, latest.gpu_freq as f64 / 1_000_000.0, latest.timestamp.format("%H:%M:%S")),
            2 => format!("NPU Usage: {:.1}% | Frequency: {:.0} MHz | Last Update: {}", 
                        latest.npu_usage, latest.npu_freq as f64 / 1_000_000.0, latest.timestamp.format("%H:%M:%S")),
            3 => format!("RGA Usage: {:.1}% | ACLK: {:.0} MHz | Core: {:.0} MHz | HCLK: {:.0} MHz | Last Update: {}", 
                        latest.rga_usage, 
                        latest.rga_aclk_freq as f64 / 1_000_000.0,
                        latest.rga_core_freq as f64 / 1_000_000.0,
                        latest.rga_hclk_freq as f64 / 1_000_000.0,
                        latest.timestamp.format("%H:%M:%S")),
            4 => format!("Memory: {:.1}% | Swap: {:.1}% | Last Update: {}", 
                        latest.memory_usage, latest.swap_usage, latest.timestamp.format("%H:%M:%S")),
            5 => format!("Temperature: {:.1}°C | Fan State: {} | Last Update: {}", 
                        latest.temperature / 1000.0, latest.fan_state, latest.timestamp.format("%H:%M:%S")),
            _ => String::new(),
        };

        // Status bar with current values
        let status = Paragraph::new(info_text)
            .style(Style::default().fg(Color::Green).add_modifier(Modifier::BOLD))
            .block(Block::default().borders(Borders::ALL).title("Current Values"));
        f.render_widget(status, chunks[2]);

        // Split the main chart area for dual charts where applicable
        let chart_chunks = Layout::default()
            .direction(Direction::Vertical)
            .constraints([Constraint::Percentage(50), Constraint::Percentage(50)])
            .split(chunks[3]);

        // Draw charts based on current tab
        match app.current_tab {
            0 => { // CPU
                draw_dual_chart(f, app, chart_chunks, "cpu_usage", "cpu_freq", 
                               "CPU Usage (%)", "CPU Frequency (MHz)", Color::Yellow, Color::Red);
            },
            1 => { // GPU
                draw_dual_chart(f, app, chart_chunks, "gpu_usage", "gpu_freq", 
                               "GPU Usage (%)", "GPU Frequency (MHz)", Color::Green, Color::Blue);
            },
            2 => { // NPU
                draw_dual_chart(f, app, chart_chunks, "npu_usage", "npu_freq", 
                               "NPU Usage (%)", "NPU Frequency (MHz)", Color::Magenta, Color::Cyan);
            },
            3 => { // RGA
                draw_rga_charts(f, app, chunks[3]);
            },
            4 => { // Memory
                draw_dual_chart(f, app, chart_chunks, "memory_usage", "swap_usage", 
                               "Memory Usage (%)", "Swap Usage (%)", Color::Yellow, Color::Red);
            },
            5 => { // Thermal
                draw_dual_chart(f, app, chart_chunks, "temperature", "fan_state", 
                               "Temperature (°C)", "Fan State", Color::Red, Color::Blue);
            },
            _ => {}
        }
    } else {
        // Show message when no data is available yet
        let no_data = Paragraph::new("Collecting system data...")
            .style(Style::default().fg(Color::Yellow))
            .block(Block::default().borders(Borders::ALL).title("Status"));
        f.render_widget(no_data, chunks[2]);
    }
}

fn draw_rga_charts(f: &mut Frame, app: &App, area: ratatui::layout::Rect) {
    let chunks = Layout::default()
        .direction(Direction::Vertical)
        .constraints([
            Constraint::Percentage(25), // RGA Usage
            Constraint::Percentage(25), // ACLK Frequency  
            Constraint::Percentage(25), // Core Frequency
            Constraint::Percentage(25), // HCLK Frequency
        ])
        .split(area);

    // RGA Usage Chart
    let (usage_data, usage_bounds) = app.get_data_for_chart("rga_usage");
    let usage_datasets = vec![Dataset::default()
        .name("RGA Usage (%)")
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(Color::White))
        .graph_type(GraphType::Line)
        .data(&usage_data)];

    let usage_chart = Chart::new(usage_datasets)
        .block(Block::default().title("RGA Usage (%)").borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (usage_data.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title("Usage %")
            .style(Style::default().fg(Color::Gray))
            .bounds([usage_bounds.0, usage_bounds.1]));

    f.render_widget(usage_chart, chunks[0]);

    // ACLK Frequency Chart
    let (aclk_data, aclk_bounds) = app.get_data_for_chart("rga_aclk_freq");
    let aclk_datasets = vec![Dataset::default()
        .name("ACLK Frequency (MHz)")
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(Color::Yellow))
        .graph_type(GraphType::Line)
        .data(&aclk_data)];

    let aclk_chart = Chart::new(aclk_datasets)
        .block(Block::default().title("RGA ACLK Frequency (MHz)").borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (aclk_data.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title("Frequency (MHz)")
            .style(Style::default().fg(Color::Gray))
            .bounds([aclk_bounds.0, aclk_bounds.1]));

    f.render_widget(aclk_chart, chunks[1]);

    // Core Frequency Chart
    let (core_data, core_bounds) = app.get_data_for_chart("rga_core_freq");
    let core_datasets = vec![Dataset::default()
        .name("Core Frequency (MHz)")
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(Color::Green))
        .graph_type(GraphType::Line)
        .data(&core_data)];

    let core_chart = Chart::new(core_datasets)
        .block(Block::default().title("RGA Core Frequency (MHz)").borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (core_data.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title("Frequency (MHz)")
            .style(Style::default().fg(Color::Gray))
            .bounds([core_bounds.0, core_bounds.1]));

    f.render_widget(core_chart, chunks[2]);

    // HCLK Frequency Chart
    let (hclk_data, hclk_bounds) = app.get_data_for_chart("rga_hclk_freq");
    let hclk_datasets = vec![Dataset::default()
        .name("HCLK Frequency (MHz)")
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(Color::Blue))
        .graph_type(GraphType::Line)
        .data(&hclk_data)];

    let hclk_chart = Chart::new(hclk_datasets)
        .block(Block::default().title("RGA HCLK Frequency (MHz)").borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (hclk_data.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title("Frequency (MHz)")
            .style(Style::default().fg(Color::Gray))
            .bounds([hclk_bounds.0, hclk_bounds.1]));

    f.render_widget(hclk_chart, chunks[3]);
}

fn draw_dual_chart(f: &mut Frame, app: &App, chunks: std::rc::Rc<[ratatui::layout::Rect]>, 
                   metric1: &str, metric2: &str, title1: &str, title2: &str, color1: Color, color2: Color) {
    let (data1, bounds1) = app.get_data_for_chart(metric1);
    let (data2, bounds2) = app.get_data_for_chart(metric2);

    // First chart
    let datasets1 = vec![Dataset::default()
        .name(title1)
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(color1))
        .graph_type(GraphType::Line)
        .data(&data1)];

    let chart1 = Chart::new(datasets1)
        .block(Block::default().title(title1).borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (data1.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title(title1)
            .style(Style::default().fg(Color::Gray))
            .bounds([bounds1.0, bounds1.1]));

    f.render_widget(chart1, chunks[0]);

    // Second chart
    let datasets2 = vec![Dataset::default()
        .name(title2)
        .marker(symbols::Marker::Dot)
        .style(Style::default().fg(color2))
        .graph_type(GraphType::Line)
        .data(&data2)];

    let chart2 = Chart::new(datasets2)
        .block(Block::default().title(title2).borders(Borders::ALL))
        .x_axis(Axis::default()
            .title("Time (seconds)")
            .style(Style::default().fg(Color::Gray))
            .bounds([0.0, (data2.len() as f64 * 0.2).max(120.0)]))
        .y_axis(Axis::default()
            .title(title2)
            .style(Style::default().fg(Color::Gray))
            .bounds([bounds2.0, bounds2.1]));

    f.render_widget(chart2, chunks[1]);
}

fn run_app<B: Backend>(terminal: &mut Terminal<B>, mut app: App) -> io::Result<()> {
    let mut last_refresh = Instant::now();

    loop {
        terminal.draw(|f| draw_ui(f, &app))?;

        // Check for user input
        if crossterm::event::poll(Duration::from_millis(100))? {
            if let Event::Key(key) = event::read()? {
                match key.code {
                    KeyCode::Char('q') | KeyCode::Esc => return Ok(()),
                    KeyCode::Left => app.previous_tab(),
                    KeyCode::Right => app.next_tab(),
                    KeyCode::Tab => app.next_tab(),
                    _ => {}
                }
            }
        }

        // Update system info every 200ms (0.2 seconds)
        if last_refresh.elapsed() >= Duration::from_millis(200) {
            let metrics = collect_system_metrics();
            app.update(metrics);
            last_refresh = Instant::now();
        }
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // Setup terminal
    enable_raw_mode()?;
    let mut stdout = io::stdout();
    execute!(stdout, EnterAlternateScreen, EnableMouseCapture)?;
    let backend = CrosstermBackend::new(stdout);
    let mut terminal = Terminal::new(backend)?;

    // Create app and run it
    let app = App::new();
    let res = run_app(&mut terminal, app);

    // Restore terminal
    disable_raw_mode()?;
    execute!(
        terminal.backend_mut(),
        LeaveAlternateScreen,
        DisableMouseCapture
    )?;
    terminal.show_cursor()?;

    if let Err(err) = res {
        println!("{:?}", err)
    }

    Ok(())
}