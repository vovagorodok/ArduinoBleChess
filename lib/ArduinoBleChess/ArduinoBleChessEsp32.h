#pragma once
#include "BleChessDevice.h"
#include <NimBLEDevice.h>

class ArduinoBleChessClass: public BLECharacteristicCallbacks
{
public:
    void begin(const std::string &deviceName, BleChessDevice& device);
    void begin(NimBLEServer* server, BleChessDevice& device);

    void onWrite(BLECharacteristic* characteristic) override;
    void send(const std::string& str);

private:
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;