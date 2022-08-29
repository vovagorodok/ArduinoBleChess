#include "BleChessOfflineCentral.h"
#include "BleChessPeripheral.h"
#include "BleConnection.h"

void BleChessOfflineCentral::connect()
{
    bleConnection.connectOfflineCentral();
}

void BleChessOfflineCentral::disconnect()
{
    bleConnection.disconnectOfflineCentral();
}

BleChessPeripheral& BleChessOfflineCentral::peripheral()
{
    return bleConnection.peripheralForOffline();;
}