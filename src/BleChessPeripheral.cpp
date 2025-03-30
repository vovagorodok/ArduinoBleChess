#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

void BleChessPeripheral::onCentralFeature(const BleChessString& feature)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::onCentralVariant(const BleChessString& variant)
{
    sendPeripheralAck(variant == BleChessVariant::Standard);
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
    onCentralUnexpectdCommand(BleChessCommand::GetState);
}

void BleChessPeripheral::onCentralSetState()
{
    onCentralUnexpectdCommand(BleChessCommand::SetState);
}

void BleChessPeripheral::onCentralState(const BleChessString& fen)
{
    onCentralUnexpectdCommand(join(BleChessCommand::State, fen));
}

void BleChessPeripheral::onCentralLastMove(const BleChessString& mv)
{
    onCentralUnexpectdCommand(join(BleChessCommand::LastMove, mv));
}

void BleChessPeripheral::onCentralUndo(const BleChessString& mv)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Undo, mv));
}

void BleChessPeripheral::onPeripheralUndoAck(bool ack)
{
    onCentralUnexpectdAck(ack);
}

void BleChessPeripheral::onPeripheralUndoPromoted(const BleChessString& prom)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Promote, prom));
}

void BleChessPeripheral::onCentralMsg(const BleChessString& msg)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Msg, msg));
}

void BleChessPeripheral::onCentralDrawOffer()
{
    onCentralUnexpectdCommand(BleChessCommand::DrawOffer);
}

void BleChessPeripheral::onPeripheralDrawOfferAck(bool ack)
{
    onCentralUnexpectdAck(ack);
}

void BleChessPeripheral::onCentralSide(const BleChessString& side)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Side, side));
}

void BleChessPeripheral::onCentralTime(const BleChessString& time)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Time, time));
}

void BleChessPeripheral::onCentralScore(const BleChessString& score)
{
    onCentralUnexpectdCommand(join(BleChessCommand::Score, score));
}

void BleChessPeripheral::onCentralOptionsBegin()
{
    onCentralUnexpectdCommand(BleChessCommand::OptionsBegin);
}

void BleChessPeripheral::onCentralOptionsReset()
{
    onCentralUnexpectdCommand(BleChessCommand::OptionsReset);
}

void BleChessPeripheral::onCentralSetOption(const BleChessString& option)
{
    onCentralUnexpectdCommand(join(BleChessCommand::SetOption, option));
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