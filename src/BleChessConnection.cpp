#include "BleChessConnection.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "CecpProtocol.h"

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

void BleChessConnection::peripheralMove(const Ble::String& mv)
{
    Protocol.onPeripheralMove(mv);
    offlineCentral->onPeripheralMove(mv);
}

void BleChessConnection::telluser(const Ble::String& text)
{
    Protocol.telluser(text);
    offlineCentral->onTelluser(text);
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