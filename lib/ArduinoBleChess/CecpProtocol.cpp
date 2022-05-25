#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "ChessDevice.h"
#if defined(ESP32)
#include <regex>
#endif

namespace
{
#if defined(ESP32)
static const std::regex uci("[a-h,A-H][1-8][a-h,A-H][1-8][nbrqNBRQ]{0,1}");
#endif
}

void CecpProtocol::begin(ChessDevice& device)
{
    this->device = &device;
}

void CecpProtocol::onMessage(const BleString& cmd)
{
    if (startsWith(cmd, "protover"))
    {
        send("feature setboard=1");
    }
    else if (startsWith(cmd, "new"))
    {
        isForceMode = false;
        device->askDeviceStopMove();
    }
    else if (startsWith(cmd, "setboard"))
    {
        auto fen = getCmdParams(cmd);
        device->onNewGame(fen);
    }
    else if (startsWith(cmd, "go"))
    {
        isForceMode = false;
        device->askDeviceMakeMove();
    }
    else if (startsWith(cmd, "force"))
    {
        isForceMode = true;
        device->askDeviceStopMove();
    }
    else if (startsWith(cmd, "Illegal move (without promotion)"))
    {
        isForcedPromotion = true;
    }
    else if (startsWith(cmd, "Illegal move"))
    {
        device->onDeviceMoveRejected(getIllegalMove(cmd));
        device->askDeviceMakeMove();
    }
#if defined(ESP32)
    else if (std::regex_match(cmd, uci))
#else
    else
#endif
    {
        if (isForcedPromotion)
            device->onDeviceMovePromoted(cmd);
        else
            device->onMove(cmd);

        if (not isForceMode)
            device->askDeviceMakeMove();

        isForcedPromotion = false;
    }
}

void CecpProtocol::onDeviceMove(const BleString& mv)
{
    send("move " + mv);
}

void CecpProtocol::send(BleString str)
{
    ArduinoBleChess.send(str);
}

BleString CecpProtocol::getCmdParams(const BleString& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}

BleString CecpProtocol::getIllegalMove(const BleString& cmd)
{
    return substring(cmd, indexOf(cmd, ": ") + 2);
}

CecpProtocol Protocol{};