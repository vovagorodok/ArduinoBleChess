#include "BleChessProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

namespace
{
BleChessString getCmdParams(const BleChessString& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}
}

BleChessProtocol::BleChessProtocol() :
    onAckMethod(&BleChessPeripheral::onFenAck)
{}

void BleChessProtocol::onCommand(const BleChessString& cmd)
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

void BleChessProtocol::sendFen(const BleChessString& fen)
{
    onAckMethod = &BleChessPeripheral::onFenAck;
    send("fen " + fen);
}

void BleChessProtocol::sendMove(const BleChessString& mv)
{
    onAckMethod = &BleChessPeripheral::onMoveAck;
    send("move " + mv);
}

void BleChessProtocol::sendAck(bool ack)
{
    send(ack ? "ok" : "nok");
}

void BleChessProtocol::sendMsg(const BleChessString& msg)
{
    send("msg " + msg);
}

void BleChessProtocol::send(BleChessString str)
{
    ArduinoBleChess.send(str);
}

BleChessProtocol chessProtocol{};