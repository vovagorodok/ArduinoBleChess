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

void BleChessConnection::sendFen(const BleChessString& fen)
{
    chessProtocol.sendFen(fen);
    offlineCentral->onFen(fen);
}

void BleChessConnection::sendMove(const BleChessString& mv)
{
    chessProtocol.sendMove(mv);
    offlineCentral->onMove(mv);
}

void BleChessConnection::sendAck(bool ack)
{
    chessProtocol.sendAck(ack);
    offlineCentral->onAck(ack);
}

void BleChessConnection::sendMsg(const BleChessString& msg)
{
    chessProtocol.sendMsg(msg);
    offlineCentral->onMsg(msg);
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