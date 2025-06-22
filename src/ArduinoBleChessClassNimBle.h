#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <NimBLEDevice.h>
#include <mutex>

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
    void onWrite(BLECharacteristic* characteristic) override;
    void onStatus(BLECharacteristic* pCharacteristic,
                  BLECharacteristicCallbacks::Status s,
                  int code) override;
    void send(const std::string& str);
    BLECharacteristic* txCharacteristic;
    std::mutex mutex;
};

extern ArduinoBleChessClass ArduinoBleChess;