#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <NimBLEDevice.h>

class ArduinoBleChessClass: public BLECharacteristicCallbacks,
                            public BLEServerCallbacks
{
public:
    bool begin(const std::string &deviceName,
               BleChessPeripheral& peripheral);
    bool begin(NimBLEServer* server,
               BleChessPeripheral& peripheral);
    bool begin(const std::string &deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(NimBLEServer* server,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);

    void send(const std::string& str);

private:
    void onConnect(NimBLEServer* srv) override;
    void onDisconnect(NimBLEServer* srv) override;
    void onWrite(BLECharacteristic* characteristic) override;
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;