#pragma once
#include "BleChessDevice.h"
#include <ArduinoBLE.h>

class ArduinoBleChessClass
{
public:
    void begin(const String& deviceName, BleChessDevice& device);
    void begin(BleChessDevice& device);

    void send(const String& str);
};

extern ArduinoBleChessClass ArduinoBleChess;