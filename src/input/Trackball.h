#pragma once
#include <Arduino.h>

enum class TrackballEvent { NONE, UP, DOWN, LEFT, RIGHT, PRESS };

class Trackball {
public:
    void begin();
    TrackballEvent update();
    String getState() const;

private:
    struct Button {
        int pin;
        bool lastReading;
        bool stableState;
        uint32_t lastChange;
    };
    Button _buttons[5];
    bool isPressed(int pin) const;
    TrackballEvent updateButton(Button& button, TrackballEvent event);
};
