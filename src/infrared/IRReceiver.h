#pragma once
#include <Arduino.h>
#include <IRrecv.h>
#include <IRutils.h>

class IRReceiver {
public:
    bool begin();
    void update();
    bool isEnabled() const;
    String lastMessage() const;

private:
    IRrecv* _receiver = nullptr;
    decode_results _results;
    String _lastMessage = "IR receiver not configured";
};
