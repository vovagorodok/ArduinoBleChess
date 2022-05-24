#pragma once
#include "ChessDevice.h"
#include <ArduinoBLE.h>

class ArduinoBleChessClass
{
public:
    void begin(const std::string &deviceName, ChessDevice& device);
    void begin(ChessDevice& device);

    void send(const std::string& str);
};

extern ArduinoBleChessClass ArduinoBleChess;