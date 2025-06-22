#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <NimBLEDevice.h>

class BleChessProtocol;

class ArduinoBleChessClass: public BLECharacteristicCallbacks,
                            public BLEServerCallbacks
{
public:
    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral);
    bool begin(BleChessPeripheral& peripheral);
    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);

    void onConnect();
    void onDisconnect();

private:
    friend BleChessProtocol;
    void onConnect(BLEServer* srv) override;
    void onDisconnect(BLEServer* srv) override;
    void send(const std::string& str);
    void onWrite(BLECharacteristic* characteristic) override;
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;