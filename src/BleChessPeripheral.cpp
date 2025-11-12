#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

void BleChessPeripheral::handleCentralFeature(BleChessStringView feature)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::handleCentralVariant(BleChessStringView variant)
{
    sendPeripheralAck(variant == BleChessVariant::Standard);
}

void BleChessPeripheral::handleCentralSetVariant(BleChessStringView variant)
{}

void BleChessPeripheral::handleCentralBegin(BleChessStringView fen)
{}

void BleChessPeripheral::handleCentralMove(BleChessStringView mv)
{}

void BleChessPeripheral::handleCentralEnd(BleChessStringView reason)
{}

void BleChessPeripheral::handlePeripheralMoveAck(bool ack)
{}

void BleChessPeripheral::handlePeripheralMovePromoted(BleChessStringView prom)
{}

void BleChessPeripheral::handleCentralUnexpectdCommand(BleChessStringView cmd)
{}

void BleChessPeripheral::handleCentralUnexpectdCommand(BleChessStringView cmd, BleChessStringView params)
{
    handleCentralUnexpectdCommand(cmd);
}

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

void BleChessPeripheral::handleCentralState(BleChessStringView fen)
{
    handleCentralUnexpectdCommand(BleChessCommand::State, fen);
}

void BleChessPeripheral::handleCentralLastMove(BleChessStringView mv)
{
    handleCentralUnexpectdCommand(BleChessCommand::LastMove, mv);
}

void BleChessPeripheral::handleCentralCheck(BleChessStringView kingPos)
{
    handleCentralUnexpectdCommand(BleChessCommand::Check, kingPos);
}

void BleChessPeripheral::handleCentralMsg(BleChessStringView msg)
{
    handleCentralUnexpectdCommand(BleChessCommand::Msg, msg);
}

void BleChessPeripheral::handleCentralUndo(BleChessStringView fen)
{
    handleCentralUnexpectdCommand(BleChessCommand::Undo, fen);
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

void BleChessPeripheral::handleCentralSide(BleChessStringView side)
{
    handleCentralUnexpectdCommand(BleChessCommand::Side, side);
}

void BleChessPeripheral::handleCentralTime(BleChessStringView time)
{
    handleCentralUnexpectdCommand(BleChessCommand::Time, time);
}

void BleChessPeripheral::handleCentralScore(BleChessStringView score)
{
    handleCentralUnexpectdCommand(BleChessCommand::Score, score);
}

void BleChessPeripheral::handleCentralOptionsBegin()
{
    handleCentralUnexpectdCommand(BleChessCommand::OptionsBegin);
}

void BleChessPeripheral::handleCentralOptionsReset()
{
    handleCentralUnexpectdCommand(BleChessCommand::OptionsReset);
}

void BleChessPeripheral::handleCentralSetOption(BleChessStringView option)
{
    handleCentralUnexpectdCommand(BleChessCommand::SetOption, option);
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