#pragma once
#include "BleChessPeripheral.h"
#include <NimBLEDevice.h>

class ArduinoBleChessClass: public BLECharacteristicCallbacks
{
public:
    bool begin(const std::string &deviceName, BleChessPeripheral& device);
    bool begin(NimBLEServer* server, BleChessPeripheral& device);

    void send(const std::string& str);

private:
    void onWrite(BLECharacteristic* characteristic) override;
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;