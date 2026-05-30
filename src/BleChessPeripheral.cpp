#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

void BleChessPeripheral::handleCentralFeature(BleChessStringView feature) {
    sendPeripheralAck(false);
}

void BleChessPeripheral::handleCentralVariant(BleChessStringView variant) {
    sendPeripheralAck(variant == BleChessVariant::Standard);
}

void BleChessPeripheral::handleCentralSetVariant(BleChessStringView variant) {
}

void BleChessPeripheral::handleCentralBegin(BleChessStringView fen) {
}

void BleChessPeripheral::handleCentralMove(BleChessStringView mv) {
}

void BleChessPeripheral::handleCentralEnd(BleChessStringView reason) {
}

void BleChessPeripheral::handlePeripheralMoveAck(bool ack) {
}

void BleChessPeripheral::handlePeripheralMovePromoted(BleChessStringView prom) {
}

void BleChessPeripheral::handleCentralUnexpectedCommand(BleChessStringView cmd) {
}

void BleChessPeripheral::handleCentralUnexpectedCommand(BleChessStringView cmd, BleChessStringView params) {
    handleCentralUnexpectedCommand(cmd);
}

void BleChessPeripheral::handleCentralUnexpectedAck(bool ack) {
}

void BleChessPeripheral::handleCentralGetState() {
    handleCentralUnexpectedCommand(BleChessCommand::GetState);
}

void BleChessPeripheral::handleCentralSetState() {
    handleCentralUnexpectedCommand(BleChessCommand::SetState);
}

void BleChessPeripheral::handleCentralState(BleChessStringView fen) {
    handleCentralUnexpectedCommand(BleChessCommand::State, fen);
}

void BleChessPeripheral::handleCentralLastMove(BleChessStringView mv) {
    handleCentralUnexpectedCommand(BleChessCommand::LastMove, mv);
}

void BleChessPeripheral::handleCentralCheck(BleChessStringView kingPos) {
    handleCentralUnexpectedCommand(BleChessCommand::Check, kingPos);
}

void BleChessPeripheral::handleCentralMsg(BleChessStringView msg) {
    handleCentralUnexpectedCommand(BleChessCommand::Msg, msg);
}

void BleChessPeripheral::handleCentralUndo(BleChessStringView fen) {
    handleCentralUnexpectedCommand(BleChessCommand::Undo, fen);
}

void BleChessPeripheral::handleCentralRedo(BleChessStringView fen) {
    handleCentralUnexpectedCommand(BleChessCommand::Redo, fen);
}

void BleChessPeripheral::handleCentralUndoOffer() {
    handleCentralUnexpectedCommand(BleChessCommand::UndoOffer);
}

void BleChessPeripheral::handlePeripheralUndoOfferAck(bool ack) {
    handleCentralUnexpectedAck(ack);
}

void BleChessPeripheral::handleCentralDrawOffer() {
    handleCentralUnexpectedCommand(BleChessCommand::DrawOffer);
}

void BleChessPeripheral::handlePeripheralDrawOfferAck(bool ack) {
    handleCentralUnexpectedAck(ack);
}

void BleChessPeripheral::handleCentralSide(BleChessStringView side) {
    handleCentralUnexpectedCommand(BleChessCommand::Side, side);
}

void BleChessPeripheral::handleCentralTime(BleChessStringView time) {
    handleCentralUnexpectedCommand(BleChessCommand::Time, time);
}

void BleChessPeripheral::handleCentralScore(BleChessStringView score) {
    handleCentralUnexpectedCommand(BleChessCommand::Score, score);
}

void BleChessPeripheral::handleCentralOptionsBegin() {
    handleCentralUnexpectedCommand(BleChessCommand::OptionsBegin);
}

void BleChessPeripheral::handleCentralOptionsReset() {
    handleCentralUnexpectedCommand(BleChessCommand::OptionsReset);
}

void BleChessPeripheral::handleCentralSetOption(BleChessStringView option) {
    handleCentralUnexpectedCommand(BleChessCommand::SetOption, option);
}

void BleChessPeripheral::sendPeripheralState(const BleChessString& fen) {
    bleChessConnection.sendPeripheralState(fen);
}

void BleChessPeripheral::sendPeripheralSync(const BleChessString& fen) {
    bleChessConnection.sendPeripheralSync(fen);
}

void BleChessPeripheral::sendPeripheralUnsync(const BleChessString& fen) {
    bleChessConnection.sendPeripheralUnsync(fen);
}

void BleChessPeripheral::sendPeripheralMove(const BleChessString& mv) {
    bleChessConnection.sendPeripheralMove(mv);
}

void BleChessPeripheral::sendPeripheralAck(bool ack) {
    bleChessConnection.sendPeripheralAck(ack);
}

void BleChessPeripheral::sendPeripheralErr(const BleChessString& err) {
    bleChessConnection.sendPeripheralErr(err);
}

void BleChessPeripheral::sendPeripheralUnsyncSettable(const BleChessString& fen) {
    bleChessConnection.sendPeripheralUnsyncSettable(fen);
}

void BleChessPeripheral::sendPeripheralMoved() {
    bleChessConnection.sendPeripheralMoved();
}

void BleChessPeripheral::sendPeripheralMsg(const BleChessString& msg) {
    bleChessConnection.sendPeripheralMsg(msg);
}

void BleChessPeripheral::sendPeripheralResign() {
    bleChessConnection.sendPeripheralResign();
}

void BleChessPeripheral::sendPeripheralUndoOffer() {
    bleChessConnection.sendPeripheralUndoOffer();
}

void BleChessPeripheral::sendPeripheralDrawOffer() {
    bleChessConnection.sendPeripheralDrawOffer();
}

void BleChessPeripheral::sendPeripheralOptionsEnd() {
    bleChessConnection.sendPeripheralOptionsEnd();
}

void BleChessPeripheral::sendPeripheralOptionsReset() {
    bleChessConnection.sendPeripheralOptionsReset();
}

void BleChessPeripheral::sendPeripheralOption(const BleChessString& option) {
    bleChessConnection.sendPeripheralOption(option);
}

void BleChessPeripheral::sendPeripheralSetOption(const BleChessString& option) {
    bleChessConnection.sendPeripheralSetOption(option);
}

void BleChessPeripheral::handleOnlineCentralConnected() {
}

void BleChessPeripheral::handleOnlineCentralDisconnected() {
}

void BleChessPeripheral::handleOfflineCentralConnected() {
}

void BleChessPeripheral::handleOfflineCentralDisconnected() {
}
