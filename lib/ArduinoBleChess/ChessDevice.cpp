#include "ChessDevice.h"
#include "CecpProtocol.h"

void ChessDevice::deviceMove(const BleString& mv)
{
    Protocol.onDeviceMove(mv);
}

void ChessDevice::telluser(const BleString& text)
{
    Protocol.telluser(text);
}