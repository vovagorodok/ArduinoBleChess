#pragma once
#include "ChessDevice.h"
#include <NimBLEDevice.h>

class ArduinoBleChessClass: public BLECharacteristicCallbacks
{
public:
    void begin(const std::string &deviceName, ChessDevice& device);
    void begin(NimBLEServer* server, ChessDevice& device);

    void onWrite(BLECharacteristic* characteristic) override;
    void send(const std::string& str);

private:
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;