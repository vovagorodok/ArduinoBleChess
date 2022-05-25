#include "ChessDevice.h"
#include "CecpProtocol.h"

void ChessDevice::deviceMove(const StringDecl& mv)
{
    Protocol.onDeviceMove(mv);
}