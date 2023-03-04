#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <ArduinoBLE.h>

class CecpProtocol;

class ArduinoBleChessClass
{
public:
    bool begin(const String& deviceName,
               BleChessPeripheral& peripheral);
    bool begin(BleChessPeripheral& peripheral);
    bool begin(const String& deviceName,
               BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessPeripheral& peripheral,
               BleChessOfflineCentral& offlineCentral);

    void onConnect();
    void onDisconnect();

private:
    friend CecpProtocol;
    void send(const String& str);
};

extern ArduinoBleChessClass ArduinoBleChess;