# RLCV3 - RGB LED Controller Version 3

RLCV3 is a comprehensive firmware and hardware project for an embedded LED controller based on the Seeedstudio XIAO ESP32-C3 microcontroller. It is designed to control various LED fixtures including light tubes, panels, and spotlights using DMX512 (wired) and Art-Net (wireless) protocols.

## Features

*   **Multi-Protocol Support**:
    *   **DMX512**: Wired communication via RS485 with termination control.
    *   **Art-Net**: Wireless control over WiFi.
*   **Versatile Hardware Support**: Configurable for different hardware profiles (Addressable Strips, PWM MOSFETs, I2C Panels).
*   **Local User Interface**:
    *   128x32 OLED Display (SSD1306).
    *   Rotary Encoder with Push Button for menu navigation.
*   **Thermal Management**: Integrated PWM fan control with zero-RPM mode support.
*   **Software Architecture**: Hybrid event-driven and polling architecture for responsive UI and high-throughput data processing.

## Hardware Variations

The firmware supports four mutually exclusive hardware profiles defined in `config.h`:

1.  **RGB_IC_TUBE**: For addressable RGB LED strips (e.g., WS2815, WS2811).
2.  **RGB_TUBE**: For non-addressable RGB LED strips controlled via MOSFETs (PWM).
3.  **PANEL**: For configurations involving slave devices controlled via I2C (requires cooling fan).
4.  **SPOT**: For single COB RGB LEDs with MOSFET control and active cooling.

## Getting Started

### Prerequisites

*   **Arduino IDE**: The primary development environment.
*   **ESP32 Board Support**: Install the ESP32 core via Board Manager.

### Dependencies

To ensure stability, the following library versions are recommended (as of Firmware 2.0):

*   **ESP Core**: 3.30.3
*   **Adafruit GFX Library**: 1.12.1
*   **Adafruit NeoPixel**: 1.13.0
*   **Adafruit SSD1306**: 2.5.14
*   **ArtnetWifi**: 1.6.1
*   **EncoderButton**: 1.0.6
*   **FastLED**: 3.9.16
*   **esp_dmx**: 4.1.0 (Note: May require specific fixes for ESP32-C3, see Issue #181)

### Configuration

Before compiling, navigate to `RLC_V3/config.h` and select your hardware profile by uncommenting exactly one of the following lines:

```c
#define RGB_IC_TUBE
// #define RGB_TUBE
// #define PANEL
// #define SPOT
```

You can also toggle debug output in the same file:

```c
// #define DEBUGGING_ENABLED
```

## Repository Structure

*   **RLC_V3/**: Main firmware source code.
*   **LaTeX/**: Comprehensive project documentation, including hardware design, theoretical background, and software architecture details.
*   **Scripts/**: Helper scripts (e.g., Python scripts for bitmap generation).

## Documentation

Detailed documentation regarding the hardware design, PCB fabrication, and theoretical background can be found in the `LaTeX` directory.