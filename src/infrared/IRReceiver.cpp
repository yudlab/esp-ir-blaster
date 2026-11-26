#include "IRReceiver.h"
#include "config.h"

bool IRReceiver::begin() {
    if (IRConfig::PIN_RECEIVER < 0) {
        _lastMessage = "IR RX GPIO not configured";
        return false;
    }
    _receiver = new IRrecv(IRConfig::PIN_RECEIVER,
        IRConfig::RECEIVER_BUFFER_SIZE, IRConfig::RECEIVER_TIMEOUT_MS, true);
    _receiver->enableIRIn();
    _lastMessage = "Waiting for IR signal";
    return true;
}

void IRReceiver::update() {
    if (!_receiver) return;
    if (_receiver->decode(&_results)) {
        _lastMessage = resultToHumanReadableBasic(&_results);
        _receiver->resume();
    }
}

bool IRReceiver::isEnabled() const { return _receiver != nullptr; }
String IRReceiver::lastMessage() const { return _lastMessage; }
