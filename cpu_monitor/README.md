# System Monitor (rtop-Ubuntu)

A comprehensive real-time system monitoring tool built in Rust for ARM-based systems, specifically designed for Rockchip RK3528A/RK3588 platforms. This TUI (Terminal User Interface) application provides detailed monitoring of CPU, GPU, NPU, RGA, memory, and thermal metrics with beautiful charts and real-time updates.

## Features

### 🖥️ **Multi-Component Monitoring**
- **CPU**: Usage percentage and frequency monitoring
- **GPU**: Mali GPU load and frequency tracking
- **NPU**: Neural Processing Unit utilization and frequency
- **RGA**: Rockchip Graphics Accelerator monitoring
- **Memory**: RAM and swap usage statistics
- **Thermal**: Temperature sensors and fan control state

### 📊 **Rich Visualization**
- Real-time line charts with adaptive Y-axis scaling
- Dual-chart view for each component (usage + frequency)
- Color-coded metrics for easy identification
- Historical data retention (2 minutes at 200ms intervals)

### ⚡ **High-Performance Updates**
- 200ms update frequency (5 times per second)
- Non-blocking UI with responsive controls
- Efficient memory management with rolling data windows

### 🎛️ **Interactive Interface**
- Tab-based navigation between different system components
- Current values display with timestamps
- Device identification from device tree
- Keyboard shortcuts for easy navigation

## Screenshots

```
┌System Monitor - armsom,sige1, rockchip,rk3528a - Press 'q' to quit, ←/→ to switch tabs┐
│ CPU │ GPU │ NPU │ RGA │ Memory │ Thermal                                              │
└─────────────────────────────────────────────────────────────────────────────────────┘
┌Current Values───────────────────────────────────────────────────────────────────────┐
│CPU Usage: 85.7% | Frequency: 2016 MHz | Last Update: 19:04:59                      │
└─────────────────────────────────────────────────────────────────────────────────────┘
┌CPU Usage (%)────────────────────────────────────────────────────────────────────────┐
│     •••••••••                                                                       │
│   ••         ••                                                                     │
│ ••             •••                                                                  │
└─────────────────────────────────────────────────────────────────────────────────────┘
```

## Installation

### Prerequisites

- Rust 1.70+ (2024 edition)
- Linux system with access to `/proc`, `/sys` filesystems
- Sudo privileges for NPU and RGA monitoring (debug filesystem access)

### Build from Source

```bash
# Clone the repository
git clone <repository-url>
cd cpu_monitor

# Build the application
cargo build --release

# Run with sudo for full functionality
sudo ./target/release/cpu_monitor
```

### Dependencies

The application uses the following Rust crates:
- `ratatui` - Terminal UI framework
- `crossterm` - Cross-platform terminal manipulation
- `chrono` - Date and time handling
- `sysinfo` - System information
- `nvml-wrapper` - NVIDIA GPU support (fallback)

## Usage

### Running the Application

```bash
# Basic run (some metrics may not be available)
./target/debug/cpu_monitor

# Recommended: Run with sudo for full access
sudo ./target/debug/cpu_monitor
```

### Controls

| Key | Action |
|-----|--------|
| `q` or `Esc` | Quit the application |
| `←` / `→` | Navigate between tabs |
| `Tab` | Next tab |

### Tabs Overview

1. **CPU Tab**: CPU usage percentage and frequency in MHz
2. **GPU Tab**: GPU utilization and frequency for Mali GPU
3. **NPU Tab**: Neural Processing Unit load and frequency
4. **RGA Tab**: Rockchip Graphics Accelerator usage percentage and three frequency clocks:
   - ACLK (AXI Clock) - typically ~339 MHz
   - Core Clock - processing frequency
   - HCLK (AHB Clock) - typically ~148 MHz
5. **Memory Tab**: RAM usage and swap utilization percentages
6. **Thermal Tab**: System temperature (°C) and fan state

## System Requirements

### Supported Platforms
- Rockchip RK3528A/RK3588 based systems
- ARM-based Linux distributions
- Systems with Mali GPU
- Compatible with Orange Pi, Armsom, and similar SBCs

### File System Dependencies

The application reads from the following system files:

**CPU Monitoring:**
- `/proc/stat` - CPU usage statistics
- `/sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq` - CPU frequency

**GPU Monitoring:**
- `/sys/class/devfreq/fb000000.gpu/load` - GPU load
- `/sys/class/devfreq/fb000000.gpu/cur_freq` - GPU frequency

**NPU Monitoring:**
- `/sys/kernel/debug/rknpu/load` - NPU load (requires sudo)
- `/sys/class/devfreq/fdab0000.npu/cur_freq` - NPU frequency

**RGA Monitoring:**
- `/sys/kernel/debug/rkrga/load` - RGA load (requires sudo)
- `/sys/kernel/debug/clk/clk_summary` - RGA frequencies (requires sudo)
  - `aclk_rga2e` - AXI clock frequency
  - `clk_core_rga2e` - Core processing frequency  
  - `hclk_rga2e` - AHB clock frequency

**Memory Monitoring:**
- `/proc/meminfo` - Memory and swap information

**Thermal Monitoring:**
- `/sys/class/thermal/thermal_zone0/temp` - Temperature sensor
- `/sys/class/thermal/cooling_device4/cur_state` - Fan state

**Device Information:**
- `/sys/firmware/devicetree/base/compatible` - Device identification

## Configuration

### Customizing Update Frequency

The update frequency is set to 200ms by default. To modify:

```rust
// In src/main.rs, line ~540
if last_refresh.elapsed() >= Duration::from_millis(200) {
    // Change 200 to desired milliseconds
}
```

### Adjusting Data Retention

Historical data is kept for 2 minutes (600 points at 200ms). To modify:

```rust
// In src/main.rs, line ~65
if self.metrics_history.len() > 600 {
    // Change 600 to desired number of data points
}
```

## Troubleshooting

### Common Issues

**1. Permission Denied Errors**
```bash
# Solution: Run with sudo
sudo ./target/debug/cpu_monitor
```

**2. Missing NPU/RGA Data**
- Ensure you're running on a compatible Rockchip platform
- Verify debug filesystem is mounted: `mount | grep debugfs`
- Run with sudo privileges

**3. GPU Metrics Show Zero**
- Check if GPU path exists: `ls /sys/class/devfreq/fb000000.gpu/`
- Verify GPU is active (may show 0 when idle)

**4. Build Errors**
```bash
# Clean and rebuild
cargo clean
cargo build
```

### Debug Mode

To enable verbose output for debugging:

```bash
# Set environment variable
RUST_LOG=debug cargo run
```

## Performance Notes

- **Memory Usage**: ~2-10 MB depending on data history
- **CPU Overhead**: <1% on modern ARM systems
- **Update Rate**: 5 Hz (200ms intervals)
- **Data Retention**: 2 minutes of historical data

## Contributing

### Development Setup

```bash
# Install Rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# Clone and setup
git clone <repository-url>
cd cpu_monitor
cargo check
```

### Adding New Metrics

1. Add fields to `SystemMetrics` struct
2. Implement data collection function
3. Add metric to `collect_system_metrics()`
4. Update UI in `draw_ui()` function
5. Add tab entry if needed

## License

[Specify your license here]

## Acknowledgments

- Built with [Ratatui](https://github.com/ratatui-org/ratatui) TUI framework
- Inspired by `htop`, `btop`, and other system monitors
- Designed for Rockchip ARM platforms and SBCs

## Platform Compatibility

| Platform | CPU | GPU | NPU | RGA | Memory | Thermal |
|----------|-----|-----|-----|-----|--------|---------|
| RK3528A  | ✅  | ✅  | ✅  | ✅  | ✅     | ✅      |
| RK3588   | ✅  | ✅  | ✅  | ✅  | ✅     | ✅      |
| Generic ARM | ✅ | ❓  | ❌  | ❌  | ✅     | ✅      |

✅ Fully Supported | ❓ Partial Support | ❌ Not Supported

---

**Note**: This tool is specifically optimized for Rockchip-based ARM systems. While CPU, memory, and thermal monitoring may work on other platforms, GPU, NPU, and RGA monitoring requires Rockchip-specific drivers and filesystem paths.
