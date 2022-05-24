#include "ChessDevice.h"
#include "CecpProtocol.h"

void ChessDevice::deviceMove(const std::string& mv)
{
    Protocol.onDeviceMove(mv);
}