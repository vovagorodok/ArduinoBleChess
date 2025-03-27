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
    onAckMethod(&BleChessPeripheral::onCentralUnexpectdAck),
    onPromotedMethod(&BleChessPeripheral::onCentralUnexpectdCommand)
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
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, "nok"))
    {
        (bleChessConnection.peripheralForOnline().*onAckMethod)(false);
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, "move"))
    {
        bleChessConnection.peripheralForOnline().onCentralMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "begin"))
    {
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
        bleChessConnection.peripheralForOnline().onCentralBegin(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "set_variant"))
    {
        bleChessConnection.peripheralForOnline().onCentralSetVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "check"))
    {
        bleChessConnection.peripheralForOnline().onCentralCheck(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "end"))
    {
        bleChessConnection.peripheralForOnline().onCentralEnd(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "promote"))
    {
        (bleChessConnection.peripheralForOnline().*onPromotedMethod)(getCmdParams(cmd));
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, "feature"))
    {
        bleChessConnection.peripheralForOnline().onCentralFeature(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "variant"))
    {
        bleChessConnection.peripheralForOnline().onCentralVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "get_state"))
    {
        bleChessConnection.peripheralForOnline().onCentralGetState();
    }
    else if (startsWith(cmd, "set_state"))
    {
        bleChessConnection.peripheralForOnline().onCentralSetState();
    }
    else if (startsWith(cmd, "state"))
    {
        bleChessConnection.peripheralForOnline().onCentralState(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "last_move"))
    {
        bleChessConnection.peripheralForOnline().onCentralLastMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "undo"))
    {
        bleChessConnection.peripheralForOnline().onCentralUndo(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "msg"))
    {
        bleChessConnection.peripheralForOnline().onCentralMsg(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "resign"))
    {
        bleChessConnection.peripheralForOnline().onCentralResign();
    }
    else if (startsWith(cmd, "draw_offer"))
    {
        bleChessConnection.peripheralForOnline().onCentralDrawOffer();
    }
    else if (startsWith(cmd, "side"))
    {
        bleChessConnection.peripheralForOnline().onCentralSide(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "time"))
    {
        bleChessConnection.peripheralForOnline().onCentralTime(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "score"))
    {
        bleChessConnection.peripheralForOnline().onCentralScore(getCmdParams(cmd));
    }
    else if (startsWith(cmd, "options_begin"))
    {
        bleChessConnection.peripheralForOnline().onCentralOptionsBegin();
    }
    else if (startsWith(cmd, "options_reset"))
    {
        bleChessConnection.peripheralForOnline().onCentralOptionsReset();
    }
    else if (startsWith(cmd, "option"))
    {
        bleChessConnection.peripheralForOnline().onCentralSetOption(getCmdParams(cmd));
    }
    else
    {
        bleChessConnection.peripheralForOnline().onCentralUnexpectdCommand(cmd);
    }
}

void BleChessProtocol::sendPeripheralState(const BleChessString& fen)
{
    send(join("state", fen));
}

void BleChessProtocol::sendPeripheralSync(const BleChessString& fen)
{
    send(join("sync", fen));
}

void BleChessProtocol::sendPeripheralUnsync(const BleChessString& fen)
{
    send(join("unsync", fen));
}

void BleChessProtocol::sendPeripheralMove(const BleChessString& mv)
{
    onAckMethod = &BleChessPeripheral::onPeripheralMoveAck;
    onPromotedMethod = &BleChessPeripheral::onPeripheralMovePromoted;
    send(join("move", mv));
}

void BleChessProtocol::sendPeripheralAck(bool ack)
{
    send(ack ? "ok" : "nok");
}

void BleChessProtocol::sendPeripheralErr(const BleChessString& err)
{
    send(join("err", err));
}

void BleChessProtocol::sendPeripheralUnsyncSetible(const BleChessString& fen)
{
    send(join("unsync_setible", fen));
}

void BleChessProtocol::sendPeripheralUndo(const BleChessString& mv)
{
    onAckMethod = &BleChessPeripheral::onPeripheralUndoAck;
    onPromotedMethod = &BleChessPeripheral::onPeripheralUndoPromoted;
    send(join("undo", mv));
}

void BleChessProtocol::sendPeripheralMoved()
{
    send("moved");
}

void BleChessProtocol::sendPeripheralMsg(const BleChessString& msg)
{
    send(join("msg", msg));
}

void BleChessProtocol::sendPeripheralResign()
{
    send("resign");
}

void BleChessProtocol::sendPeripheralDrawOffer()
{
    onAckMethod = &BleChessPeripheral::onPeripheralDrawOfferAck;
    send("draw_offer");
}

void BleChessProtocol::sendPeripheralOptionsEnd()
{
    send("options_end");
}

void BleChessProtocol::sendPeripheralOption(const BleChessString& option)
{
    send(join("option", option));
}

void BleChessProtocol::sendPeripheralSetOption(const BleChessString& option)
{
    send(join("set_option", option));
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