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
    onAckMethod(&BleChessPeripheral::onAck)
{}

void BleChessProtocol::onCommand(const BleChessString& cmd)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess receive: ");
    Serial.println(cmd.c_str());
    #endif
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
    else if (startsWith(cmd, "last_move"))
    {
        auto lastMove = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onLastMove(lastMove);
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
    onAckMethod = &BleChessPeripheral::onAck;
    send(ack ? "ok" : "nok");
}

void BleChessProtocol::sendMsg(const BleChessString& msg)
{
    onAckMethod = &BleChessPeripheral::onAck;
    send("msg " + msg);
}

void BleChessProtocol::send(BleChessString str)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess send: ");
    Serial.println(str.c_str());
    #endif
    ArduinoBleChess.send(str);
}

BleChessProtocol chessProtocol{};