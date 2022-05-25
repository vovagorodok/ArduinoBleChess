#include "BleChessDevice.h"
#include "CecpProtocol.h"

void BleChessDevice::deviceMove(const BleString& mv)
{
    Protocol.onDeviceMove(mv);
}

void BleChessDevice::telluser(const BleString& text)
{
    Protocol.telluser(text);
}