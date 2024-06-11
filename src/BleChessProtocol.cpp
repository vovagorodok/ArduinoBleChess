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
    onAckMethod(&BleChessPeripheral::onCentralAck)
{}

void BleChessProtocol::onCentralCommand(const BleChessString& cmd)
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
        bleChessConnection.peripheralForOnline().onCentralMove(mv);
    }
    else if (startsWith(cmd, "fen"))
    {
        auto fen = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onCentralFen(fen);
    }
    else if (startsWith(cmd, "promote"))
    {
        auto prom = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onPeripheralMovePromoted(prom);
    }
    else if (startsWith(cmd, "feature"))
    {
        auto feature = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onCentralFeature(feature);
    }
    else if (startsWith(cmd, "variant"))
    {
        auto variant = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onCentralVariant(variant);
    }
    else if (startsWith(cmd, "last_move"))
    {
        auto lastMove = getCmdParams(cmd);
        bleChessConnection.peripheralForOnline().onCentralLastMove(lastMove);
    }
    else
    {
        sendPeripheralAck(false);
    }
}

void BleChessProtocol::sendPeripheralFen(const BleChessString& fen)
{
    onAckMethod = &BleChessPeripheral::onPeripheralFenAck;
    send("fen " + fen);
}

void BleChessProtocol::sendPeripheralMove(const BleChessString& mv)
{
    onAckMethod = &BleChessPeripheral::onPeripheralMoveAck;
    send("move " + mv);
}

void BleChessProtocol::sendPeripheralAck(bool ack)
{
    onAckMethod = &BleChessPeripheral::onCentralAck;
    send(ack ? "ok" : "nok");
}

void BleChessProtocol::sendPeripheralMsg(const BleChessString& msg)
{
    onAckMethod = &BleChessPeripheral::onCentralAck;
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