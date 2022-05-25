#pragma once
#include "ChessDevice.h"
#include <ArduinoBLE.h>

class ArduinoBleChessClass
{
public:
    void begin(const String& deviceName, ChessDevice& device);
    void begin(ChessDevice& device);

    void send(const String& str);
};

extern ArduinoBleChessClass ArduinoBleChess;