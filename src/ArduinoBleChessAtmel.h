#pragma once
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include <ArduinoBLE.h>

class CecpProtocol;

class ArduinoBleChessClass
{
public:
    bool begin(const String& deviceName,
               BleChessPeripheral& device);
    bool begin(BleChessPeripheral& device);
    bool begin(const String& deviceName,
               BleChessPeripheral& device,
               BleChessOfflineCentral& offlineCentral);
    bool begin(BleChessPeripheral& device,
               BleChessOfflineCentral& offlineCentral);

private:
    friend CecpProtocol;
    void send(const String& str);
};

extern ArduinoBleChessClass ArduinoBleChess;