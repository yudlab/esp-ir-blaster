#pragma once

#include <Arduino.h>

// Target: GOOUUU ESP32-S3-CAM N16R8.
// Keep camera, SD, PSRAM and onboard LED pins reserved.

namespace BoardConfig {
    constexpr char NAME[] = "GOOUUU ESP32-S3-CAM N16R8";
    constexpr uint32_t SERIAL_BAUD = 115200;
}

// Default panel: ST7789, 240x320. Pin map follows the carrier TFT header.
// GPIO0 is TFT reset and an ESP32-S3 strapping pin.
namespace DisplayConfig {
    constexpr int WIDTH = 240;
    constexpr int HEIGHT = 320;
    constexpr int PIN_SCLK = 42;
    constexpr int PIN_MOSI = 41;
    constexpr int PIN_MISO = -1;
    constexpr int PIN_CS = 47;
    constexpr int PIN_DC = 45;
    constexpr int PIN_RESET = 0;
    constexpr int PIN_BACKLIGHT = 21;
    constexpr bool BACKLIGHT_ACTIVE_HIGH = true;
}

// Inputs connect to GND when pressed. QWIIC must remain unused.
// GPIO43/44 are UART0 pads; native USB CDC is enabled for diagnostics.
namespace TrackballConfig {
    constexpr int PIN_UP = 1;
    constexpr int PIN_DOWN = 2;
    constexpr int PIN_LEFT = 14;
    constexpr int PIN_RIGHT = -1; // Pending GPIO-expander allocation.
    constexpr int PIN_PRESS = -1; // Pending GPIO-expander allocation.
    constexpr bool ACTIVE_LOW = true;
    constexpr uint32_t DEBOUNCE_MS = 25;
}

// Deliberately disabled until final IR wiring and safe GPIOs are confirmed.
namespace TrackballLedConfig {
    // PWM channels are deliberately unassigned until the GPIO-expander/pin plan is finalised.
    constexpr int PIN_RED = -1;
    constexpr int PIN_GREEN = -1;
    constexpr int PIN_BLUE = -1;
    constexpr int PIN_WHITE = -1;
    constexpr uint32_t PWM_FREQUENCY = 5000;
    constexpr uint8_t PWM_RESOLUTION = 8;
}

namespace IRConfig {
    constexpr int PIN_RECEIVER = -1;
    constexpr int PIN_TRANSMITTER = -1;
    constexpr uint16_t RECEIVER_BUFFER_SIZE = 1024;
    constexpr uint8_t RECEIVER_TIMEOUT_MS = 50;
}

namespace ReservedPins {
    constexpr int CAMERA[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18};
    constexpr int SD_CARD[] = {38, 39, 40};
    constexpr int RGB_LED = 48;
    // GPIO26-37 are connected to flash/PSRAM resources on N16R8 modules.
}
