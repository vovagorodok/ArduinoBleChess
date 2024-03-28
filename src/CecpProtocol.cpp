#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

CecpProtocol::CecpProtocol() :
    onAckMethod(&BleChessPeripheral::onFenAck)
{}

void CecpProtocol::onCommand(const BleChessString& cmd)
{
    if (startsWith(cmd, "ok"))
    {
        (bleChessConnection.peripheralForOnline().*onAckMethod)(true);
    }
    else if (startsWith(cmd, "nok"))
    {
        (bleChessConnection.peripheralForOnline().*onAckMethod)(false);
    }
    else if (startsWith(cmd, "move"))
    {
        auto mv = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onMove(mv);
    }
    else if (startsWith(cmd, "fen"))
    {
        auto fen = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onFen(fen);
    }
    else if (startsWith(cmd, "promote"))
    {
        auto prom = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onPromote(prom);
    }
    else if (startsWith(cmd, "feature"))
    {
        auto feature = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onFeature(feature);
    }
    else if (startsWith(cmd, "variant"))
    {
        auto variant = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onVariant(variant);
    }
    else
    {
        sendAck(false);
    }
}

void CecpProtocol::sendFen(const BleChessString& fen)
{
    onAckMethod = &BleChessPeripheral::onFenAck;
    send("fen " + fen);
}

void CecpProtocol::sendMove(const BleChessString& mv)
{
    onAckMethod = &BleChessPeripheral::onMoveAck;
    send("move " + mv);
}

void CecpProtocol::sendAck(bool ack)
{
    send(ack ? "ok" : "nok");
}

void CecpProtocol::sendMsg(const BleChessString& msg)
{
    send("msg " + msg);
}

void CecpProtocol::send(BleChessString str)
{
    ArduinoBleChess.send(str);
}

BleChessString CecpProtocol::getCmdParams(const BleChessString& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}

CecpProtocol chessProtocol{};