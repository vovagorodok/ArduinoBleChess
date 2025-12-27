#pragma once
#include "BleChessDefines.h"
#ifdef BLE_CHESS_BLE_LIB_FAKE
#include "BleChessUuids.h"
#include "BleChessData.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"

using BleChessServerFake = int;

class BleChessProtocol;

class BleChessLib
{
public:
    bool begin(const char* deviceName,
               BleChessPeripheral& peripheral);
    bool begin(BleChessPeripheral& peripheral);
    bool begin(const char* deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral);
    bool begin(BleChessServerFake* server,
               BleChessPeripheral& peripheral);
    bool begin(const std::string& deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessServerFake* server,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);

    void onConnect();
    void onDisconnect();

private:
    friend BleChessProtocol;
    void send(const BleChessString& str);
};

extern BleChessLib ArduinoBleChess;
#endif