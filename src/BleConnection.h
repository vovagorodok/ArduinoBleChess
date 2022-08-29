#pragma once
#include "BleString.h"

class BleChessPeripheral;
class BleChessOfflineCentral;

class BleConnection
{
public:
    BleConnection();

    void onConnected();
    void onDisconnected();

    void peripheralMove(const Ble::String& mv);
    void telluser(const Ble::String& text);

    void connectOfflineCentral();
    void disconnectOfflineCentral();
    BleChessPeripheral& peripheralForOffline();
    BleChessPeripheral& peripheralForOnline();

    void registerPeripheral(BleChessPeripheral& peripheral);
    void registerOfflineCentral(BleChessOfflineCentral& central);

private:
    BleChessPeripheral* registeredPeripheral;
    BleChessOfflineCentral* registeredCentral;
    BleChessPeripheral* offlinePeripheral;
    BleChessOfflineCentral* offlineCentral;
};

extern BleConnection bleConnection;