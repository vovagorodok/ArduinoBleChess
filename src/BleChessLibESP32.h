#pragma once
#include "BleChessDefines.h"
#ifdef BLE_CHESS_BLE_LIB_ESP32
#include "BleChessUuids.h"
#include "BleChessData.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "BleChessConnectCallbacks.h"

class BleChessProtocol;

class BleChessLib : public BLECharacteristicCallbacks,
                    public BLEServerCallbacks {
 public:
    BleChessLib();

    void begin(const std::string& deviceName, BleChessPeripheral& peripheral);
    void begin(BLEServer* server, BleChessPeripheral& peripheral);
    void begin(const std::string& deviceName, BleChessPeripheral& peripheral, BleChessOfflineCentral& offlineCentral);
    void begin(BLEServer* server, BleChessPeripheral& peripheral, BleChessOfflineCentral& offlineCentral);

    void setConnectCallbacks(BleChessConnectCallbacks&);
    void onConnect();
    void onDisconnect();

 private:
    friend BleChessProtocol;
    void onConnect(BLEServer* srv) override;
    void onDisconnect(BLEServer* srv) override;
    void onWrite(BLECharacteristic* characteristic) override;
    void send(const std::string& str);

    BLECharacteristic* _txCharacteristic;
    BleChessConnectCallbacks* _connectCallbacks;
};

extern BleChessLib ArduinoBleChess;
#endif
