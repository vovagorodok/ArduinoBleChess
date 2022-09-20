#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessPeripheral::peripheralMove(const Ble::String& mv)
{
    bleChessConnection.peripheralMove(mv);
}

void BleChessPeripheral::telluser(const Ble::String& text)
{
    bleChessConnection.telluser(text);
}