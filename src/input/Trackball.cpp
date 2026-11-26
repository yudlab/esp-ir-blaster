#include "Trackball.h"
#include "config.h"

void Trackball::begin() {
    const int pins[5] = {
        TrackballConfig::PIN_UP, TrackballConfig::PIN_DOWN,
        TrackballConfig::PIN_LEFT, TrackballConfig::PIN_RIGHT,
        TrackballConfig::PIN_PRESS
    };
    for (int i = 0; i < 5; ++i) {
        if (pins[i] < 0) {
            _buttons[i] = {pins[i], HIGH, HIGH, millis()};
            continue;
        }
        pinMode(pins[i], INPUT_PULLUP);
        const bool reading = digitalRead(pins[i]);
        _buttons[i] = {pins[i], reading, reading, millis()};
    }
}

bool Trackball::isPressed(int pin) const {
    if (pin < 0) return false;
    const bool level = digitalRead(pin);
    return TrackballConfig::ACTIVE_LOW ? !level : level;
}

TrackballEvent Trackball::updateButton(Button& button, TrackballEvent event) {
    if (button.pin < 0) return TrackballEvent::NONE;
    const bool reading = digitalRead(button.pin);
    if (reading != button.lastReading) {
        button.lastChange = millis();
        button.lastReading = reading;
    }
    if (millis() - button.lastChange >= TrackballConfig::DEBOUNCE_MS) {
        if (reading != button.stableState) {
            button.stableState = reading;
            const bool pressed = TrackballConfig::ACTIVE_LOW
                ? button.stableState == LOW : button.stableState == HIGH;
            if (pressed) return event;
        }
    }
    return TrackballEvent::NONE;
}

TrackballEvent Trackball::update() {
    const TrackballEvent events[5] = {
        TrackballEvent::UP, TrackballEvent::DOWN, TrackballEvent::LEFT,
        TrackballEvent::RIGHT, TrackballEvent::PRESS
    };
    for (int i = 0; i < 5; ++i) {
        TrackballEvent event = updateButton(_buttons[i], events[i]);
        if (event != TrackballEvent::NONE) return event;
    }
    return TrackballEvent::NONE;
}

String Trackball::getState() const {
    String result;
    const char* names[5] = {"UP", "DOWN", "LEFT", "RIGHT", "PRESS"};
    for (int i = 0; i < 5; ++i) {
        if (isPressed(_buttons[i].pin)) {
            if (result.length()) result += ", ";
            result += names[i];
        }
    }
    return result.length() ? result : "No input";
}
