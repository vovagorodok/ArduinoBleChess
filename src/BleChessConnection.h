#pragma once
#include "BleChessString.h"

class BleChessPeripheral;
class BleChessOfflineCentral;

class BleChessConnection
{
public:
    BleChessConnection();

    void onConnected();
    void onDisconnected();

    void peripheralMove(const BleChessString& mv);
    void telluser(const BleChessString& text);

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

extern BleChessConnection bleChessConnection;