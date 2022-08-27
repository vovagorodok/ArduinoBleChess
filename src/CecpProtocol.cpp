#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include <regex>
#endif

namespace
{
#if defined(NIM_BLE_ARDUINO_LIB)
static const std::regex uci("[a-h,A-H][1-8][a-h,A-H][1-8][nbrqNBRQ]{0,1}");
#endif
}

void CecpProtocol::begin(BleChessPeripheral& device)
{
    this->device = &device;
}

void CecpProtocol::onMessage(const Ble::String& cmd)
{
    if (startsWith(cmd, "xboard") || startsWith(cmd, "accepted"))
    {
    }
    else if (startsWith(cmd, "protover"))
    {
        send("feature setboard=1");
    }
    else if (startsWith(cmd, "new"))
    {
        isForceMode = false;
        askPeripheralStopMove();
    }
    else if (startsWith(cmd, "setboard"))
    {
        auto fen = getCmdParams(cmd);
        device->onNewRound(fen);
    }
    else if (startsWith(cmd, "go"))
    {
        isForceMode = false;
        askPeripheralMakeMove();
    }
    else if (startsWith(cmd, "force"))
    {
        isForceMode = true;
        askPeripheralStopMove();
    }
    else if (startsWith(cmd, "Illegal move (without promotion)"))
    {
        isForcedPromotion = true;
    }
    else if (startsWith(cmd, "Illegal move"))
    {
        device->onPeripheralMoveRejected(getIllegalMove(cmd));
    }
#if defined(NIM_BLE_ARDUINO_LIB)
    else if (std::regex_match(cmd, uci))
#else
    else
#endif
    {
        if (isForcedPromotion)
            device->onPeripheralMovePromoted(cmd);
        else
            device->onCentralMove(cmd);

        if (not isForceMode)
            askPeripheralMakeMove();

        isForcedPromotion = false;
    }
}

void CecpProtocol::onPeripheralMove(const Ble::String& mv)
{
    send("move " + mv);
}

void CecpProtocol::telluser(const Ble::String& text)
{
    send("telluser " + text);
}

void CecpProtocol::send(Ble::String str)
{
    ArduinoBleChess.send(str);
}

Ble::String CecpProtocol::getCmdParams(const Ble::String& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}

Ble::String CecpProtocol::getIllegalMove(const Ble::String& cmd)
{
    return substring(cmd, indexOf(cmd, ": ") + 2);
}

void CecpProtocol::askPeripheralMakeMove()
{
    device->askPeripheralMakeMove();
}

void CecpProtocol::askPeripheralStopMove()
{
    device->askPeripheralStopMove();
}

CecpProtocol Protocol{};