#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessPeripheral::onCentralFeature(const BleChessString& feature)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::onCentralVariant(const BleChessString& variant)
{
    sendPeripheralAck(variant == "standard");
}

void BleChessPeripheral::onCentralSetVariant(const BleChessString& variant)
{}

void BleChessPeripheral::onCentralBegin(const BleChessString& fen)
{}

void BleChessPeripheral::onCentralMove(const BleChessString& mv)
{}

void BleChessPeripheral::onCentralCheck(const BleChessString& kingPos)
{}

void BleChessPeripheral::onCentralEnd(const BleChessString& reason)
{}

void BleChessPeripheral::onPeripheralMoveAck(bool ack)
{}

void BleChessPeripheral::onPeripheralMovePromoted(const BleChessString& prom)
{}

void BleChessPeripheral::onCentralUnexpectdCommand(const BleChessString& cmd)
{}

void BleChessPeripheral::onCentralUnexpectdAck(bool ack)
{}

void BleChessPeripheral::onCentralGetState()
{
    onCentralUnexpectdCommand("get_state");
}

void BleChessPeripheral::onCentralSetState()
{
    onCentralUnexpectdCommand("set_state");
}

void BleChessPeripheral::onCentralState(const BleChessString& fen)
{
    onCentralUnexpectdCommand(join("state", fen));
}

void BleChessPeripheral::onCentralLastMove(const BleChessString& mv)
{
    onCentralUnexpectdCommand(join("last_move", mv));
}

void BleChessPeripheral::onCentralUndo(const BleChessString& mv)
{
    onCentralUnexpectdCommand(join("undo", mv));
}

void BleChessPeripheral::onPeripheralUndoAck(bool ack)
{
    onCentralUnexpectdAck(ack);
}

void BleChessPeripheral::onPeripheralUndoPromoted(const BleChessString& prom)
{
    onCentralUnexpectdCommand(join("promote", prom));
}

void BleChessPeripheral::onCentralMsg(const BleChessString& msg)
{
    onCentralUnexpectdCommand(join("msg", msg));
}

void BleChessPeripheral::onCentralResign()
{
    onCentralUnexpectdCommand("resign");
}

void BleChessPeripheral::onCentralDrawOffer()
{
    onCentralUnexpectdCommand("draw_offer");
}

void BleChessPeripheral::onPeripheralDrawOfferAck(bool ack)
{
    onCentralUnexpectdAck(ack);
}

void BleChessPeripheral::onCentralSide(const BleChessString& side)
{
    onCentralUnexpectdCommand(join("side", side));
}

void BleChessPeripheral::onCentralTime(const BleChessString& time)
{
    onCentralUnexpectdCommand(join("time", time));
}

void BleChessPeripheral::onCentralScore(const BleChessString& score)
{
    onCentralUnexpectdCommand(join("score", score));
}

void BleChessPeripheral::onCentralOptionsBegin()
{
    onCentralUnexpectdCommand("options_begin");
}

void BleChessPeripheral::onCentralOptionsReset()
{
    onCentralUnexpectdCommand("options_reset");
}

void BleChessPeripheral::onCentralSetOption(const BleChessString& option)
{
    onCentralUnexpectdCommand(join("set_option", option));
}

void BleChessPeripheral::sendPeripheralState(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralState(fen);
}

void BleChessPeripheral::sendPeripheralSync(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralSync(fen);
}

void BleChessPeripheral::sendPeripheralUnsync(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralUnsync(fen);
}

void BleChessPeripheral::sendPeripheralMove(const BleChessString& mv)
{
    bleChessConnection.sendPeripheralMove(mv);
}

void BleChessPeripheral::sendPeripheralAck(bool ack)
{
    bleChessConnection.sendPeripheralAck(ack);
}

void BleChessPeripheral::sendPeripheralErr(const BleChessString& err)
{
    bleChessConnection.sendPeripheralErr(err);
}

void BleChessPeripheral::sendPeripheralUnsyncSetible(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralUnsyncSetible(fen);
}

void BleChessPeripheral::sendPeripheralUndo(const BleChessString& mv)
{
    bleChessConnection.sendPeripheralUndo(mv);
}

void BleChessPeripheral::sendPeripheralMoved()
{
    bleChessConnection.sendPeripheralMoved();
}

void BleChessPeripheral::sendPeripheralMsg(const BleChessString& msg)
{
    bleChessConnection.sendPeripheralMsg(msg);
}

void BleChessPeripheral::sendPeripheralResign()
{
    bleChessConnection.sendPeripheralResign();
}

void BleChessPeripheral::sendPeripheralDrawOffer()
{
    bleChessConnection.sendPeripheralDrawOffer();
}

void BleChessPeripheral::sendPeripheralOptionsEnd()
{
    bleChessConnection.sendPeripheralOptionsEnd();
}

void BleChessPeripheral::sendPeripheralOption(const BleChessString& option)
{
    bleChessConnection.sendPeripheralOption(option);
}

void BleChessPeripheral::sendPeripheralSetOption(const BleChessString& option)
{
    bleChessConnection.sendPeripheralSetOption(option);
}