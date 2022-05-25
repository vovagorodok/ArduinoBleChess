#pragma once
#include "BleChessDevice.h"
#include <NimBLEDevice.h>

class ArduinoBleChessClass: public BLECharacteristicCallbacks
{
public:
    bool begin(const std::string &deviceName, BleChessDevice& device);
    bool begin(NimBLEServer* server, BleChessDevice& device);

    void onWrite(BLECharacteristic* characteristic) override;
    void send(const std::string& str);

private:
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;