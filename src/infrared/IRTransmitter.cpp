#include "IRTransmitter.h"
#include "config.h"

bool IRTransmitter::begin() {
    if (IRConfig::PIN_TRANSMITTER < 0) return false;
    _transmitter = new IRsend(IRConfig::PIN_TRANSMITTER);
    _transmitter->begin();
    return true;
}

bool IRTransmitter::sendTestSignal() {
    if (!_transmitter) return false;
    // NEC test frame. Drive an IR LED through a suitable transistor circuit.
    _transmitter->sendNEC(0x20DF10EF, 32);
    return true;
}

bool IRTransmitter::isEnabled() const { return _transmitter != nullptr; }
