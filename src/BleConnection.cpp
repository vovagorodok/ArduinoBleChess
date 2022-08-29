#include "BleConnection.h"
#include "BleChessPeripheral.h"
#include "BleChessOfflineCentral.h"
#include "CecpProtocol.h"

namespace
{
static BleChessPeripheral dummyPeripheral{};
static BleChessOfflineCentral dummyOfflineCentral{};
}

BleConnection::BleConnection() :
    registeredPeripheral(&dummyPeripheral),
    registeredCentral(&dummyOfflineCentral),
    offlinePeripheral(&dummyPeripheral),
    offlineCentral(&dummyOfflineCentral)
{}

void BleConnection::onConnected()
{
    registeredCentral->onOnlineCentralConnected();
}

void BleConnection::onDisconnected()
{
    registeredCentral->onOnlineCentralDisconnected();
}

void BleConnection::peripheralMove(const Ble::String& mv)
{
    Protocol.onPeripheralMove(mv);
    offlineCentral->onPeripheralMove(mv);
}

void BleConnection::telluser(const Ble::String& text)
{
    Protocol.telluser(text);
    offlineCentral->onTelluser(text);
}

void BleConnection::connectOfflineCentral()
{
    offlineCentral = registeredCentral;
    offlinePeripheral = registeredPeripheral;
}

void BleConnection::disconnectOfflineCentral()
{
    offlineCentral = &dummyOfflineCentral;
    offlinePeripheral = &dummyPeripheral;
}

BleChessPeripheral& BleConnection::peripheralForOffline()
{
    return *offlinePeripheral;
}

BleChessPeripheral& BleConnection::peripheralForOnline()
{
    return *registeredPeripheral;
}

void BleConnection::registerPeripheral(BleChessPeripheral& peripheral)
{
    registeredPeripheral = &peripheral;
}

void BleConnection::registerOfflineCentral(BleChessOfflineCentral& central)
{
    registeredCentral = &central;
}

BleConnection bleConnection{};