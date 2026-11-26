#include "TrackballLED.h"
#include "config.h"

namespace {
const int LED_PINS[4] = {
    TrackballLedConfig::PIN_RED,
    TrackballLedConfig::PIN_GREEN,
    TrackballLedConfig::PIN_BLUE,
    TrackballLedConfig::PIN_WHITE
};
}

void TrackballLED::begin() {
    for (int pin : LED_PINS) {
        if (pin < 0) continue;
        pinMode(pin, OUTPUT);
        analogWriteFrequency(pin, TrackballLedConfig::PWM_FREQUENCY);
        analogWrite(pin, 0);
    }
}

void TrackballLED::setRGBW(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    _levels[0] = red;
    _levels[1] = green;
    _levels[2] = blue;
    _levels[3] = white;
    apply();
}

void TrackballLED::setBrightness(uint8_t brightness) {
    _brightness = brightness;
    apply();
}

void TrackballLED::off() {
    setRGBW(0, 0, 0, 0);
}

void TrackballLED::apply() {
    for (size_t i = 0; i < 4; ++i) {
        if (LED_PINS[i] < 0) continue;
        const uint16_t scaled = (static_cast<uint16_t>(_levels[i]) * _brightness) / 255;
        analogWrite(LED_PINS[i], static_cast<uint8_t>(scaled));
    }
}
