# ESP IR Blaster

Modular firmware for the GOOUUU ESP32-S3-CAM N16R8 using PlatformIO and Arduino.

The first milestone is a small TFT + Blackberry-style trackball test application. IR classes are included but remain disabled until safe GPIOs and wiring are confirmed. Camera and microSD pins are reserved.

## Hardware target
- ESP32-S3-WROOM-1 N16R8 (16 MB flash, 8 MB octal PSRAM)
- GOOUUU ESP32-S3-CAM carrier
- ST7789 SPI TFT, default 240x320
- Five-switch Blackberry trackball
- Optional IR receiver and IR LED driver

## Pin allocation

| Function | GPIO | Notes |
|---|---:|---|
| TFT SCLK | 42 | Onboard TFT connector |
| TFT MOSI | 41 | Onboard TFT connector |
| TFT DC | 45 | Onboard TFT connector |
| TFT CS | -1 | CS tied low |
| TFT RESET | 0 | Onboard TFT connector; boot strap pin |
| TFT backlight | 21 | Onboard TFT connector |
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

## Structure
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
