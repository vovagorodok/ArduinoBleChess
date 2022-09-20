#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessPeripheral::peripheralMove(const BleChess::String& mv)
{
    bleChessConnection.peripheralMove(mv);
}

void BleChessPeripheral::telluser(const BleChess::String& text)
{
    bleChessConnection.telluser(text);
}