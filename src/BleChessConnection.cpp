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
    offlineCentral->onPeripheralMove(mv);
}

void BleChessConnection::sendPeripheralAck(bool ack)
{
    chessProtocol.sendPeripheralAck(ack);
    offlineCentral->onPeripheralAck(ack);
}

void BleChessConnection::sendPeripheralErr(const BleChessString& err)
{
    chessProtocol.sendPeripheralErr(err);
}

void BleChessConnection::sendPeripheralUnsyncSetible(const BleChessString& fen)
{
    chessProtocol.sendPeripheralUnsyncSetible(fen);
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
    offlineCentral->onPeripheralUndoOffer();
}

void BleChessConnection::sendPeripheralDrawOffer()
{
    chessProtocol.sendPeripheralDrawOffer();
    offlineCentral->onPeripheralDrawOffer();
}

void BleChessConnection::sendPeripheralOptionsEnd()
{
    chessProtocol.sendPeripheralOptionsEnd();
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