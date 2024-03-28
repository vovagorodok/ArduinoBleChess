#include "BleChessPeripheral.h"
#include "BleChessConnection.h"

void BleChessPeripheral::onFeature(const BleChessString& feature)
{
    sendAck(false);
}

void BleChessPeripheral::onVariant(const BleChessString& variant)
{
    sendAck(startsWith(variant, "standard"));
}

void BleChessPeripheral::onFen(const BleChessString& fen)
{
    sendAck(false);
}

void BleChessPeripheral::onFenAck(bool ack)
{}

void BleChessPeripheral::onMove(const BleChessString& mv)
{
    sendAck(false);
}

void BleChessPeripheral::onMoveAck(bool ack)
{}

void BleChessPeripheral::onPromote(const BleChessString& prom)
{
    sendAck(false);
}

void BleChessPeripheral::sendFen(const BleChessString& fen)
{
    bleChessConnection.sendFen(fen);
}

void BleChessPeripheral::sendMove(const BleChessString& mv)
{
    bleChessConnection.sendMove(mv);
}

void BleChessPeripheral::sendAck(bool ack)
{
    bleChessConnection.sendAck(ack);
}

void BleChessPeripheral::sendMsg(const BleChessString& msg)
{
    bleChessConnection.sendMsg(msg);
}