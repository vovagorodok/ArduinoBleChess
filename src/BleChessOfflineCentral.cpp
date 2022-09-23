#include "BleChessOfflineCentral.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessOfflineCentral::connect()
{
    bleChessConnection.connectOfflineCentral();
    connected = true;
}

void BleChessOfflineCentral::disconnect()
{
    bleChessConnection.disconnectOfflineCentral();
    connected = false;
}

bool BleChessOfflineCentral::isConnected() const
{
    return connected;
}

BleChessPeripheral& BleChessOfflineCentral::peripheral()
{
    return bleChessConnection.peripheralForOffline();;
}