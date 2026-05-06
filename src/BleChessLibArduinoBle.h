#pragma once
#include "BleChessDefines.h"
#ifdef BLE_CHESS_BLE_LIB_ARDUINO_BLE
#include "BleChessUuids.h"
#include "BleChessData.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "BleChessConnectCallbacks.h"

class BleChessProtocol;

class BleChessLib {
 public:
    BleChessLib();

    bool begin(const char* deviceName, BleChessPeripheral& peripheral);
    bool begin(BleChessPeripheral& peripheral);
    bool begin(const char* deviceName, BleChessPeripheral& peripheral, BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessPeripheral& peripheral, BleChessOfflineCentral& offlineCentral);

    void setConnectCallbacks(BleChessConnectCallbacks&);
    void onConnect();
    void onDisconnect();

 private:
    friend BleChessProtocol;
    void send(const String& str);

    BleChessConnectCallbacks* _connectCallbacks;
};

extern BleChessLib ArduinoBleChess;
#endif
