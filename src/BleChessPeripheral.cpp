#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

void BleChessPeripheral::handleCentralFeature(const BleChessString& feature)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::handleCentralVariant(const BleChessString& variant)
{
    sendPeripheralAck(variant == BleChessVariant::Standard);
}

void BleChessPeripheral::handleCentralSetVariant(const BleChessString& variant)
{}

void BleChessPeripheral::handleCentralBegin(const BleChessString& fen)
{}

void BleChessPeripheral::handleCentralMove(const BleChessString& mv)
{}

void BleChessPeripheral::handleCentralEnd(const BleChessString& reason)
{}

void BleChessPeripheral::handlePeripheralMoveAck(bool ack)
{}

void BleChessPeripheral::handlePeripheralMovePromoted(const BleChessString& prom)
{}

void BleChessPeripheral::handleCentralUnexpectdCommand(const BleChessString& cmd)
{}

void BleChessPeripheral::handleCentralUnexpectdAck(bool ack)
{}

void BleChessPeripheral::handleCentralGetState()
{
    handleCentralUnexpectdCommand(BleChessCommand::GetState);
}

void BleChessPeripheral::handleCentralSetState()
{
    handleCentralUnexpectdCommand(BleChessCommand::SetState);
}

void BleChessPeripheral::handleCentralState(const BleChessString& fen)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::State, fen));
}

void BleChessPeripheral::handleCentralLastMove(const BleChessString& mv)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::LastMove, mv));
}

void BleChessPeripheral::handleCentralCheck(const BleChessString& kingPos)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Check, kingPos));
}

void BleChessPeripheral::handleCentralMsg(const BleChessString& msg)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Msg, msg));
}

void BleChessPeripheral::handleCentralUndo(const BleChessString& fen)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Undo, fen));
}

void BleChessPeripheral::handleCentralUndoOffer()
{
    handleCentralUnexpectdCommand(BleChessCommand::UndoOffer);
}

void BleChessPeripheral::handlePeripheralUndoOfferAck(bool ack)
{
    handleCentralUnexpectdAck(ack);
}

void BleChessPeripheral::handleCentralDrawOffer()
{
    handleCentralUnexpectdCommand(BleChessCommand::DrawOffer);
}

void BleChessPeripheral::handlePeripheralDrawOfferAck(bool ack)
{
    handleCentralUnexpectdAck(ack);
}

void BleChessPeripheral::handleCentralSide(const BleChessString& side)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Side, side));
}

void BleChessPeripheral::handleCentralTime(const BleChessString& time)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Time, time));
}

void BleChessPeripheral::handleCentralScore(const BleChessString& score)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::Score, score));
}

void BleChessPeripheral::handleCentralOptionsBegin()
{
    handleCentralUnexpectdCommand(BleChessCommand::OptionsBegin);
}

void BleChessPeripheral::handleCentralOptionsReset()
{
    handleCentralUnexpectdCommand(BleChessCommand::OptionsReset);
}

void BleChessPeripheral::handleCentralSetOption(const BleChessString& option)
{
    handleCentralUnexpectdCommand(join(BleChessCommand::SetOption, option));
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

void BleChessPeripheral::sendPeripheralUnsyncSettable(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralUnsyncSettable(fen);
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

void BleChessPeripheral::sendPeripheralUndoOffer()
{
    bleChessConnection.sendPeripheralUndoOffer();
}

void BleChessPeripheral::sendPeripheralDrawOffer()
{
    bleChessConnection.sendPeripheralDrawOffer();
}

void BleChessPeripheral::sendPeripheralOptionsEnd()
{
    bleChessConnection.sendPeripheralOptionsEnd();
}

void BleChessPeripheral::sendPeripheralOptionsReset()
{
    bleChessConnection.sendPeripheralOptionsReset();
}

void BleChessPeripheral::sendPeripheralOption(const BleChessString& option)
{
    bleChessConnection.sendPeripheralOption(option);
}

void BleChessPeripheral::sendPeripheralSetOption(const BleChessString& option)
{
    bleChessConnection.sendPeripheralSetOption(option);
}

void BleChessPeripheral::handleOnlineCentralConnected()
{}

void BleChessPeripheral::handleOnlineCentralDisconnected()
{}

void BleChessPeripheral::handleOfflineCentralConnected()
{}

void BleChessPeripheral::handleOfflineCentralDisconnected()
{}