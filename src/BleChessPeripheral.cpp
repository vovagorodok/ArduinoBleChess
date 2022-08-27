#include "BleChessPeripheral.h"
#include "CecpProtocol.h"

void BleChessPeripheral::peripheralMove(const Ble::String& mv)
{
    Protocol.onPeripheralMove(mv);
}

void BleChessPeripheral::telluser(const Ble::String& text)
{
    Protocol.telluser(text);
}