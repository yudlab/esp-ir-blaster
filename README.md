# ESP IR Blaster

Modular firmware for the GOOUUU ESP32-S3-CAM N16R8 using PlatformIO and Arduino.

The first milestone is a small TFT + Blackberry-style trackball test application. IR classes are included but remain disabled until safe GPIOs and wiring are confirmed. A separate RGBW PWM driver is included, but its pins remain unassigned. Camera and microSD pins are reserved.

## Hardware target
- ESP32-S3-WROOM-1 N16R8 (16 MB flash, 8 MB octal PSRAM)
- GOOUUU ESP32-S3-CAM carrier
- ST7789 SPI TFT, default 240x320
- Hall-effect Blackberry trackball (4 motion outputs + push switch) with 4-channel RGBW PWM lighting
- Optional IR receiver and IR LED driver

## Pin allocation

| Function | GPIO | Notes |
|---|---:|---|
| TFT SCLK | 42 | TFT connector |
| TFT MOSI | 41 | TFT connector |
| TFT DC | 45 | TFT connector |
| TFT CS | 47 | TFT connector |
| TFT RESET | 0 | TFT connector; boot strap pin |
| TFT backlight | 21 | TFT connector |
| Trackball UP | 1 | QWIIC SDA pad; QWIIC unused |
| Trackball DOWN | 2 | QWIIC SCL pad; QWIIC unused |
| Trackball LEFT | 14 | GPIO |
| Trackball RIGHT | 43 | UART0 TX pad; USB CDC used for logs |
| Trackball PRESS | 44 | UART0 RX pad; USB CDC used for logs |
| IR RX / TX | Disabled | Set after confirming free physical pads |

### Reserved board resources
- Camera: GPIO 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18.
- microSD (1-bit SDMMC): GPIO 38, 39, 40.
- Onboard RGB LED: GPIO 48.
- Avoid GPIO 26-37: flash/PSRAM connections on this module/variant.
- GPIO 0 is a boot-strapping pin. Ensure the TFT reset input does not force it to the wrong level during reset.
- GPIO 43/44 are UART0 pads. Native USB CDC is enabled for serial diagnostics.

Board variants can have different carrier-board wiring. Confirm the silkscreen and schematic before connecting peripherals. The pin table is a starting configuration for the GOOUUU carrier, not a universal ESP32-S3-CAM pinout.

## Build and upload
1. Install Visual Studio Code and the PlatformIO IDE extension.
2. Open this repository as a PlatformIO project.
3. Connect the board over USB-C.
4. Run PlatformIO: Build, then PlatformIO: Upload.
5. Open PlatformIO: Monitor at 115200 baud.

The environment targets esp32-s3-devkitc-1 with 16 MB flash, OPI PSRAM and native USB CDC. Update the Espressif32 platform package if your installed version does not recognise these options.

## First test
- TFT displays a four-item menu.
- Move the trackball to navigate and press to select.
- Trackball Test reports directional/button inputs.
- IR menu items report that GPIOs are not configured.
- System Information reports flash, heap and PSRAM status.

## GPIO capacity and expansion\n\nThe complete requested direct-GPIO budget is 15 signals: IR TX/RX (2), TFT (4 minimum as specified by the user; this repository's current TFT_eSPI setup also uses reset and backlight GPIOs), trackball motion/button (5), and RGBW PWM (4). The carrier does not provide 15 safe spare GPIOs once camera, microSD, flash/PSRAM, TFT and USB functions are reserved. Do not wire the full design using the current provisional pin table.\n\nRecommended expansion: use an MCP23017 (or equivalent) for the five trackball digital inputs and a PCA9685 for the four RGBW PWM channels. These can share an I²C bus, subject to confirming the board's accessible SDA/SCL pins and voltage levels. Keep IR TX/RX on two remaining suitable native GPIOs. The PCA9685 is preferable to an MCP23017 for dimming because it provides hardware PWM.\n\n## Structure
- include/config.h: central hardware configuration
- src/main.cpp: Arduino setup() and loop()
- src/display: TFT class
- src/input: trackball class
- src/infrared: IR receive/transmit classes
- src/app: menu and application state

Keep hardware access inside each component class. Keep menu/state decisions inside Application. Put board-specific values in config.h. Avoid adding hardware logic to main.cpp.

## Dependencies
- TFT_eSPI
- IRremoteESP8266
