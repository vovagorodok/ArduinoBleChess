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

void BleChessPeripheral::onCentralFen(const BleChessString& fen)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::onCentralMove(const BleChessString& mv)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::onCentralAck(bool ack)
{}

void BleChessPeripheral::onPeripheralFenAck(bool ack)
{}

void BleChessPeripheral::onPeripheralMoveAck(bool ack)
{}

void BleChessPeripheral::onPeripheralMovePromoted(const BleChessString& prom)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::onCentralLastMove(const BleChessString& mv)
{
    sendPeripheralAck(false);
}

void BleChessPeripheral::sendPeripheralFen(const BleChessString& fen)
{
    bleChessConnection.sendPeripheralFen(fen);
}

void BleChessPeripheral::sendPeripheralMove(const BleChessString& mv)
{
    bleChessConnection.sendPeripheralMove(mv);
}

void BleChessPeripheral::sendPeripheralAck(bool ack)
{
    bleChessConnection.sendPeripheralAck(ack);
}

void BleChessPeripheral::sendPeripheralMsg(const BleChessString& msg)
{
    bleChessConnection.sendPeripheralMsg(msg);
}