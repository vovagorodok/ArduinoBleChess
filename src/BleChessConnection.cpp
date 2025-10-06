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
    registeredPeripheral->handleOnlineCentralConnected();
    registeredCentral->handleOnlineCentralConnected();
}

void BleChessConnection::onDisconnected()
{
    registeredPeripheral->handleOnlineCentralDisconnected();
    registeredCentral->handleOnlineCentralDisconnected();
}

void BleChessConnection::sendPeripheralState(const BleChessString& fen)
{
    chessProtocol.sendPeripheralState(fen);
}

void BleChessConnection::sendPeripheralSync(const BleChessString& fen)
{
    chessProtocol.sendPeripheralSync(fen);
}

void BleChessConnection::sendPeripheralUnsync(const BleChessString& fen)
{
    chessProtocol.sendPeripheralUnsync(fen);
}

void BleChessConnection::sendPeripheralMove(const BleChessString& mv)
{
    chessProtocol.sendPeripheralMove(mv);
    offlineCentral->handlePeripheralMove(mv);
}

void BleChessConnection::sendPeripheralAck(bool ack)
{
    chessProtocol.sendPeripheralAck(ack);
    offlineCentral->handlePeripheralAck(ack);
}

void BleChessConnection::sendPeripheralErr(const BleChessString& err)
{
    chessProtocol.sendPeripheralErr(err);
}

void BleChessConnection::sendPeripheralUnsyncSettable(const BleChessString& fen)
{
    chessProtocol.sendPeripheralUnsyncSettable(fen);
}

void BleChessConnection::sendPeripheralMoved()
{
    chessProtocol.sendPeripheralMoved();
}

void BleChessConnection::sendPeripheralMsg(const BleChessString& msg)
{
    chessProtocol.sendPeripheralMsg(msg);
}

void BleChessConnection::sendPeripheralResign()
{
    chessProtocol.sendPeripheralResign();
}

void BleChessConnection::sendPeripheralUndoOffer()
{
    chessProtocol.sendPeripheralUndoOffer();
    offlineCentral->handlePeripheralUndoOffer();
}

void BleChessConnection::sendPeripheralDrawOffer()
{
    chessProtocol.sendPeripheralDrawOffer();
    offlineCentral->handlePeripheralDrawOffer();
}

void BleChessConnection::sendPeripheralOptionsEnd()
{
    chessProtocol.sendPeripheralOptionsEnd();
}

void BleChessConnection::sendPeripheralOptionsReset()
{
    chessProtocol.sendPeripheralOptionsReset();
}

void BleChessConnection::sendPeripheralOption(const BleChessString& option)
{
    chessProtocol.sendPeripheralOption(option);
}

void BleChessConnection::sendPeripheralSetOption(const BleChessString& option)
{
    chessProtocol.sendPeripheralSetOption(option);
}

void BleChessConnection::connectOfflineCentral()
{
    offlineCentral = registeredCentral;
    offlinePeripheral = registeredPeripheral;
    registeredPeripheral->handleOfflineCentralConnected();
}

void BleChessConnection::disconnectOfflineCentral()
{
    offlineCentral = &dummyOfflineCentral;
    offlinePeripheral = &dummyPeripheral;
    registeredPeripheral->handleOfflineCentralDisconnected();
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