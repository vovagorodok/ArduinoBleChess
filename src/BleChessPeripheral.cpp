#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessPeripheral::peripheralMove(const BleChessString& mv)
{
    bleChessConnection.peripheralMove(mv);
}

void BleChessPeripheral::telluser(const BleChessString& text)
{
    bleChessConnection.telluser(text);
}