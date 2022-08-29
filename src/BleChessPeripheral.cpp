#include "BleChessPeripheral.h"
#include "BleConnection.h"

void BleChessPeripheral::peripheralMove(const Ble::String& mv)
{

    bleConnection.peripheralMove(mv);
}

void BleChessPeripheral::telluser(const Ble::String& text)
{
    bleConnection.telluser(text);
}