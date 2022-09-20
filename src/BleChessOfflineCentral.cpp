#include "BleChessOfflineCentral.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessOfflineCentral::connect()
{
    bleChessConnection.connectOfflineCentral();
}

void BleChessOfflineCentral::disconnect()
{
    bleChessConnection.disconnectOfflineCentral();
}

BleChessPeripheral& BleChessOfflineCentral::peripheral()
{
    return bleChessConnection.peripheralForOffline();;
}