#include "BleChessConnection.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "BleChessProtocol.h"

namespace
{
static BleChessPeripheral dummyPeripheral{};
static BleChessOfflineCentral dummyOfflineCentral{};
}

BleChessConnection::BleChessConnection():
    _registeredPeripheral(&dummyPeripheral),
    _registeredCentral(&dummyOfflineCentral),
    _offlinePeripheral(&dummyPeripheral),
    _offlineCentral(&dummyOfflineCentral)
{}

void BleChessConnection::onConnected()
{
    _registeredPeripheral->handleOnlineCentralConnected();
    _registeredCentral->handleOnlineCentralConnected();
}

void BleChessConnection::onDisconnected()
{
    _registeredPeripheral->handleOnlineCentralDisconnected();
    _registeredCentral->handleOnlineCentralDisconnected();
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
    _offlineCentral->handlePeripheralMove(mv);
}

void BleChessConnection::sendPeripheralAck(bool ack)
{
    chessProtocol.sendPeripheralAck(ack);
    _offlineCentral->handlePeripheralAck(ack);
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
    _offlineCentral->handlePeripheralUndoOffer();
}

void BleChessConnection::sendPeripheralDrawOffer()
{
    chessProtocol.sendPeripheralDrawOffer();
    _offlineCentral->handlePeripheralDrawOffer();
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
    _offlineCentral = _registeredCentral;
    _offlinePeripheral = _registeredPeripheral;
    _registeredPeripheral->handleOfflineCentralConnected();
}

void BleChessConnection::disconnectOfflineCentral()
{
    _offlineCentral = &dummyOfflineCentral;
    _offlinePeripheral = &dummyPeripheral;
    _registeredPeripheral->handleOfflineCentralDisconnected();
}

BleChessPeripheral& BleChessConnection::getPeripheralForOffline()
{
    return *_offlinePeripheral;
}

BleChessPeripheral& BleChessConnection::getPeripheralForOnline()
{
    return *_registeredPeripheral;
}

void BleChessConnection::registerPeripheral(BleChessPeripheral& peripheral)
{
    _registeredPeripheral = &peripheral;
}

void BleChessConnection::registerOfflineCentral(BleChessOfflineCentral& central)
{
    _registeredCentral = &central;
}

BleChessConnection bleChessConnection{};