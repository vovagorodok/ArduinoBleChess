#pragma once
#include "BleChessDevice.h"
#include <ArduinoBLE.h>

class ArduinoBleChessClass
{
public:
    bool begin(const String& deviceName, BleChessDevice& device);
    bool begin(BleChessDevice& device);

    void send(const String& str);
    void checkIfValueRecived();
};

extern ArduinoBleChessClass ArduinoBleChess;