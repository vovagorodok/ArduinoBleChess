#pragma once
#include "BleChessDefines.h"
#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
#include "BleChessUuids.h"
#include "BleChessData.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "BleChessConnectCallbacks.h"

class BleChessProtocol;

class BleChessLib: public BLECharacteristicCallbacks,
                   public BLEServerCallbacks
{
public:
    BleChessLib();

    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral);
    bool begin(BLEServer* server,
               BleChessPeripheral& peripheral);
    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BLEServer* server,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);

    void setConnectCallbacks(BleChessConnectCallbacks&);
    void onConnect();
    void onDisconnect();

private:
    friend BleChessProtocol;
#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
    void onConnect(BLEServer* srv) override;
    void onDisconnect(BLEServer* srv) override;
    void onSubscribe(BLECharacteristic* characteristic, ble_gap_conn_desc* desc, uint16_t subValue) override;
    void onWrite(BLECharacteristic* characteristic) override;
#else
    void onConnect(BLEServer* srv, BLEConnInfo& connInfo) override;
    void onDisconnect(BLEServer* srv, BLEConnInfo& connInfo, int reason) override;
    void onSubscribe(BLECharacteristic* characteristic, BLEConnInfo& connInfo, uint16_t subValue) override;
    void onWrite(BLECharacteristic* characteristic, BLEConnInfo& connInfo) override;
#endif
    void send(const std::string& str);

    BLECharacteristic* _txCharacteristic;
    BleChessConnectCallbacks* _connectCallbacks;
};

extern BleChessLib ArduinoBleChess;
#endif