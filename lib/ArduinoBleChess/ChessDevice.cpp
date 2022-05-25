#include "ChessDevice.h"
#include "CecpProtocol.h"

void ChessDevice::deviceMove(const BleString& mv)
{
    Protocol.onDeviceMove(mv);
}