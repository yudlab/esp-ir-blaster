#pragma once
#include <Arduino.h>

// Four independent PWM channels for the trackball's red, green, blue and white LEDs.
// Pins remain -1 until the final GPIO-expander/pin allocation is confirmed.
class TrackballLED {
public:
    void begin();
    void setRGBW(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
    void setBrightness(uint8_t brightness);
    void off();

private:
    uint8_t _levels[4] = {0, 0, 0, 0};
    uint8_t _brightness = 255;
    void apply();
};
