#include "BleChessConnection.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "BleChessProtocol.h"

namespace
{
static BleChessPeripheral dummyPeripheral{};
static BleChessOfflineCentral dummyOfflineCentral{};
}

BleChessConnection::BleChessConnection() :
    registeredPeripheral(&dummyPeripheral),
    registeredCentral(&dummyOfflineCentral),
    offlinePeripheral(&dummyPeripheral),
    offlineCentral(&dummyOfflineCentral)
{}

void BleChessConnection::onConnected()
{
    registeredCentral->onOnlineCentralConnected();
}

void BleChessConnection::onDisconnected()
{
    registeredCentral->onOnlineCentralDisconnected();
}

void BleChessConnection::sendPeripheralFen(const BleChessString& fen)
{
    chessProtocol.sendPeripheralFen(fen);
    offlineCentral->onPeripheralFen(fen);
}

void BleChessConnection::sendPeripheralMove(const BleChessString& mv)
{
    chessProtocol.sendPeripheralMove(mv);
    offlineCentral->onPeripheralMove(mv);
}

void BleChessConnection::sendPeripheralAck(bool ack)
{
    chessProtocol.sendPeripheralAck(ack);
    offlineCentral->onPeripheralAck(ack);
}

void BleChessConnection::sendPeripheralMsg(const BleChessString& msg)
{
    chessProtocol.sendPeripheralMsg(msg);
    offlineCentral->onPeripheralMsg(msg);
}

void BleChessConnection::connectOfflineCentral()
{
    offlineCentral = registeredCentral;
    offlinePeripheral = registeredPeripheral;
}

void BleChessConnection::disconnectOfflineCentral()
{
    offlineCentral = &dummyOfflineCentral;
    offlinePeripheral = &dummyPeripheral;
}

BleChessPeripheral& BleChessConnection::peripheralForOffline()
{
    return *offlinePeripheral;
}

BleChessPeripheral& BleChessConnection::peripheralForOnline()
{
    return *registeredPeripheral;
}

void BleChessConnection::registerPeripheral(BleChessPeripheral& peripheral)
{
    registeredPeripheral = &peripheral;
}

void BleChessConnection::registerOfflineCentral(BleChessOfflineCentral& central)
{
    registeredCentral = &central;
}

BleChessConnection bleChessConnection{};