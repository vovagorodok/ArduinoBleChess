#include "BleChessDevice.h"
#include "CecpProtocol.h"

void BleChessDevice::deviceMove(const Ble::String& mv)
{
    Protocol.onDeviceMove(mv);
}

void BleChessDevice::telluser(const Ble::String& text)
{
    Protocol.telluser(text);
}