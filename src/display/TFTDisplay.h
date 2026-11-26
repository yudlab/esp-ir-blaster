#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

class TFTDisplay {
public:
    bool begin();
    void drawHome(int selectedItem, const String& status);
    void drawTrackballTest(const String& inputStatus);
    void drawMessage(const String& title, const String& message);
    void drawSystemInfo();

private:
    TFT_eSPI _tft;
    void drawHeader(const String& title);
    void drawMenuItem(int y, const String& label, bool selected);
};
