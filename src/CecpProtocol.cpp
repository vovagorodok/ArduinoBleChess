#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include <regex>
#endif

namespace
{
#if defined(NIM_BLE_ARDUINO_LIB)
static const std::regex uci("[a-h,A-H][1-8][a-h,A-H][1-8][nbrqNBRQ]{0,1}");
#endif
}

void CecpProtocol::onMessage(const BleChess::String& cmd)
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
        bleChessConnection.peripheralForOnline().onNewRound(fen);
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
        bleChessConnection.peripheralForOnline().onPeripheralMoveRejected(getIllegalMove(cmd));
    }
#if defined(NIM_BLE_ARDUINO_LIB)
    else if (std::regex_match(cmd, uci))
#else
    else
#endif
    {
        if (isForcedPromotion)
            bleChessConnection.peripheralForOnline().onPeripheralMovePromoted(cmd);
        else
            bleChessConnection.peripheralForOnline().onCentralMove(cmd);

        if (not isForceMode)
            askPeripheralMakeMove();

        isForcedPromotion = false;
    }
}

void CecpProtocol::onPeripheralMove(const BleChess::String& mv)
{
    send("move " + mv);
}

void CecpProtocol::telluser(const BleChess::String& text)
{
    send("telluser " + text);
}

void CecpProtocol::send(BleChess::String str)
{
    ArduinoBleChess.send(str);
}

BleChess::String CecpProtocol::getCmdParams(const BleChess::String& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}

BleChess::String CecpProtocol::getIllegalMove(const BleChess::String& cmd)
{
    return substring(cmd, indexOf(cmd, ": ") + 2);
}

void CecpProtocol::askPeripheralMakeMove()
{
    bleChessConnection.peripheralForOnline().askPeripheralMakeMove();
}

void CecpProtocol::askPeripheralStopMove()
{
    bleChessConnection.peripheralForOnline().askPeripheralStopMove();
}

CecpProtocol chessProtocol{};