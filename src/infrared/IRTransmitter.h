#pragma once
#include <Arduino.h>
#include <IRsend.h>

class IRTransmitter {
public:
    bool begin();
    bool sendTestSignal();
    bool isEnabled() const;

private:
    IRsend* _transmitter = nullptr;
};
