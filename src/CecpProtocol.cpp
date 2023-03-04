#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#ifdef USE_NIM_BLE_ARDUINO_LIB
#include <regex>
#endif

namespace
{
#ifdef USE_NIM_BLE_ARDUINO_LIB
static const std::regex uci("[a-h,A-H][1-8][a-h,A-H][1-8][nbrqNBRQ]{0,1}");
#endif
}

void CecpProtocol::onMessage(const BleChessString& cmd)
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
#ifdef USE_NIM_BLE_ARDUINO_LIB
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

void CecpProtocol::onPeripheralMove(const BleChessString& mv)
{
    send("move " + mv);
}

void CecpProtocol::telluser(const BleChessString& text)
{
    send("telluser " + text);
}

void CecpProtocol::send(BleChessString str)
{
    ArduinoBleChess.send(str);
}

BleChessString CecpProtocol::getCmdParams(const BleChessString& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}

BleChessString CecpProtocol::getIllegalMove(const BleChessString& cmd)
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