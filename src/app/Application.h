#pragma once
#include <Arduino.h>
#include "display/TFTDisplay.h"
#include "input/Trackball.h"
#include "lighting/TrackballLED.h"
#include "infrared/IRReceiver.h"
#include "infrared/IRTransmitter.h"

class Application {
public:
    void begin();
    void update();

private:
    enum class Screen { HOME, TRACKBALL_TEST, IR_RECEIVER, IR_TRANSMITTER, SYSTEM_INFO };

    TFTDisplay _display;
    Trackball _trackball;
    TrackballLED _trackballLED;
    IRReceiver _irReceiver;
    IRTransmitter _irTransmitter;

    Screen _screen = Screen::HOME;
    int _selectedItem = 0;
    uint32_t _lastRefresh = 0;
    String _trackballStatus = "No input";
    bool _pressToExit = false;

    void handleEvent(TrackballEvent event);
    void render();
    void openSelectedItem();
    void returnHome();
};
