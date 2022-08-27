#pragma once
#include "BleChessPeripheral.h"
#include <ArduinoBLE.h>

class ArduinoBleChessClass
{
public:
    bool begin(const String& deviceName, BleChessPeripheral& device);
    bool begin(BleChessPeripheral& device);

    void send(const String& str);
};

extern ArduinoBleChessClass ArduinoBleChess;