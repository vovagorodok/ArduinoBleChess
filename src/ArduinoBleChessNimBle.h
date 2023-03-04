#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <NimBLEDevice.h>

class CecpProtocol;

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
    friend CecpProtocol;
    void onConnect(NimBLEServer* srv) override;
    void onDisconnect(NimBLEServer* srv) override;
    void send(const std::string& str);
    void onWrite(BLECharacteristic* characteristic) override;
    BLECharacteristic* txCharacteristic;
};

extern ArduinoBleChessClass ArduinoBleChess;