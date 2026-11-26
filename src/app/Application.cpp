#include "Application.h"

void Application::begin() {
    _display.begin();
    _trackball.begin();
    _irReceiver.begin();
    _irTransmitter.begin();
    render();
}

void Application::update() {
    _irReceiver.update();
    const TrackballEvent event = _trackball.update();
    if (event != TrackballEvent::NONE) {
        handleEvent(event);
        _lastRefresh = 0;
    }

    if (millis() - _lastRefresh >= 250) {
        if (_screen == Screen::TRACKBALL_TEST) {
            _trackballStatus = _trackball.getState();
            render();
        } else if (_screen == Screen::IR_RECEIVER && _irReceiver.isEnabled()) {
            render();
        }
        _lastRefresh = millis();
    }
}

void Application::handleEvent(TrackballEvent event) {
    if (_screen == Screen::HOME) {
        if (event == TrackballEvent::UP) {
            _selectedItem = (_selectedItem + 3) % 4;
            render();
        } else if (event == TrackballEvent::DOWN) {
            _selectedItem = (_selectedItem + 1) % 4;
            render();
        } else if (event == TrackballEvent::PRESS) {
            openSelectedItem();
        }
        return;
    }

    if (_screen == Screen::TRACKBALL_TEST && event != TrackballEvent::PRESS) {
        _trackballStatus = _trackball.getState();
        render();
        return;
    }
    if (event == TrackballEvent::PRESS) returnHome();
}

void Application::openSelectedItem() {
    switch (_selectedItem) {
        case 0:
            _screen = Screen::IR_RECEIVER;
            render();
            break;
        case 1:
            _screen = Screen::IR_TRANSMITTER;
            if (_irTransmitter.isEnabled()) _irTransmitter.sendTestSignal();
            render();
            break;
        case 2:
            _screen = Screen::TRACKBALL_TEST;
            _trackballStatus = _trackball.getState();
            render();
            break;
        case 3:
            _screen = Screen::SYSTEM_INFO;
            render();
            break;
    }
}

void Application::returnHome() {
    _screen = Screen::HOME;
    render();
}

void Application::render() {
    switch (_screen) {
        case Screen::HOME:
            _display.drawHome(_selectedItem,
                (_irReceiver.isEnabled() || _irTransmitter.isEnabled())
                    ? "IR hardware configured" : "Display + trackball test");
            break;
        case Screen::TRACKBALL_TEST:
            _display.drawTrackballTest(_trackballStatus);
            break;
        case Screen::IR_RECEIVER:
            _display.drawMessage("IR RECEIVER", _irReceiver.lastMessage());
            break;
        case Screen::IR_TRANSMITTER:
            _display.drawMessage("IR TRANSMITTER",
                _irTransmitter.isEnabled() ? "NEC test frame sent" : "TX GPIO not configured");
            break;
        case Screen::SYSTEM_INFO:
            _display.drawSystemInfo();
            break;
    }
}
