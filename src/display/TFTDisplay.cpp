#include "TFTDisplay.h"
#include "config.h"

bool TFTDisplay::begin() {
    pinMode(DisplayConfig::PIN_BACKLIGHT, OUTPUT);
    digitalWrite(DisplayConfig::PIN_BACKLIGHT,
        DisplayConfig::BACKLIGHT_ACTIVE_HIGH ? HIGH : LOW);
    _tft.init();
    _tft.setRotation(1);
    _tft.fillScreen(TFT_BLACK);
    _tft.setTextWrap(false);
    drawMessage("ESP IR BLASTER", "Display initialised");
    return true;
}

void TFTDisplay::drawHeader(const String& title) {
    _tft.fillRect(0, 0, _tft.width(), 34, TFT_NAVY);
    _tft.setTextColor(TFT_WHITE, TFT_NAVY);
    _tft.drawString(title, 10, 9, 2);
    _tft.drawFastHLine(0, 34, _tft.width(), TFT_DARKGREY);
}

void TFTDisplay::drawMenuItem(int y, const String& label, bool selected) {
    const uint16_t bg = selected ? TFT_DARKCYAN : TFT_BLACK;
    const uint16_t fg = selected ? TFT_WHITE : TFT_LIGHTGREY;
    _tft.fillRoundRect(8, y, _tft.width() - 16, 32, 5, bg);
    _tft.setTextColor(fg, bg);
    _tft.drawString(selected ? "> " + label : "  " + label, 16, y + 8, 2);
}

void TFTDisplay::drawHome(int selectedItem, const String& status) {
    _tft.fillScreen(TFT_BLACK);
    drawHeader("ESP IR BLASTER");
    drawMenuItem(43, "IR Receiver", selectedItem == 0);
    drawMenuItem(81, "IR Transmitter", selectedItem == 1);
    drawMenuItem(119, "Trackball Test", selectedItem == 2);
    drawMenuItem(157, "System Information", selectedItem == 3);
    _tft.setTextColor(TFT_CYAN, TFT_BLACK);
    _tft.drawString("SYSTEM", 10, 197, 2);
    _tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    _tft.drawString(status, 10, 216, 2);
    _tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    _tft.drawString("Move: navigate  Press: select", 10, 231, 1);
}

void TFTDisplay::drawTrackballTest(const String& inputStatus) {
    _tft.fillScreen(TFT_BLACK);
    drawHeader("TRACKBALL TEST");
    _tft.setTextColor(TFT_GREEN, TFT_BLACK);
    _tft.drawString("INPUT DETECTED", 12, 58, 2);
    _tft.setTextColor(TFT_WHITE, TFT_BLACK);
    _tft.drawString(inputStatus, 12, 100, 2);
    _tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    _tft.drawString("Move or press the trackball", 12, 170, 2);
    _tft.drawString("Press twice to return", 12, 200, 2);
}

void TFTDisplay::drawMessage(const String& title, const String& message) {
    _tft.fillScreen(TFT_BLACK);
    drawHeader(title);
    _tft.setTextColor(TFT_CYAN, TFT_BLACK);
    _tft.drawString(message, 12, 70, 2);
    _tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    _tft.drawString("Press to return", 12, 220, 1);
}

void TFTDisplay::drawSystemInfo() {
    _tft.fillScreen(TFT_BLACK);
    drawHeader("SYSTEM INFORMATION");
    _tft.setTextColor(TFT_WHITE, TFT_BLACK);
    _tft.drawString("Board: ESP32-S3-CAM", 10, 50, 2);
    _tft.drawString("Flash: " + String(ESP.getFlashChipSize() / (1024 * 1024)) + " MB", 10, 78, 2);
    _tft.drawString("Free heap: " + String(ESP.getFreeHeap() / 1024) + " KB", 10, 106, 2);
    _tft.drawString(String("PSRAM: ") + (psramFound() ? "Available" : "Not found"), 10, 134, 2);
    _tft.drawString("Camera: reserved", 10, 162, 2);
    _tft.drawString("SD card: reserved", 10, 190, 2);
    _tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    _tft.drawString("Press to return", 10, 225, 1);
}
