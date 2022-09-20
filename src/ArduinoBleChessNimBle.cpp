#include "BleChessDefines.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include "ArduinoBleChessNimBle.h"
#include "BleChessCharacteristics.h"
#include "CecpProtocol.h"
#include "BleChessConnection.h"

bool ArduinoBleChessClass::begin(const std::string& deviceName,
                                 BleChessPeripheral& peripheral)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    if(!begin(peripheral))
        return false;

    auto* advertising = server->getAdvertising();
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
    return advertising->start();
}

bool ArduinoBleChessClass::begin(BleChessPeripheral& peripheral)
{
    auto* server = BLEDevice::createServer();
    bleChessConnection.registerPeripheral(peripheral);
    server->setCallbacks(this);
    auto* service = server->createService(CHESS_SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        CHESS_CHARACTERISTIC_UUID_RX,
        NIMBLE_PROPERTY::WRITE
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        CHESS_CHARACTERISTIC_UUID_TX,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->txCharacteristic = txCharacteristic;

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(CHESS_SERVICE_UUID);
    return service->start();
}

bool ArduinoBleChessClass::begin(const std::string& deviceName,
                                 BleChessPeripheral& peripheral,
                                 BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(deviceName, peripheral);
}

bool ArduinoBleChessClass::begin(BleChessPeripheral& peripheral,
                                 BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(peripheral);
}

void ArduinoBleChessClass::onConnect(NimBLEServer* srv)
{
    bleChessConnection.onConnected();
}

void ArduinoBleChessClass::onDisconnect(NimBLEServer* srv)
{
    bleChessConnection.onDisconnected();
}

void ArduinoBleChessClass::onWrite(BLECharacteristic* characteristic)
{
    std::string rxValue = characteristic->getValue();
    Protocol.onMessage(rxValue);
}

void ArduinoBleChessClass::send(const std::string& str)
{
    txCharacteristic->setValue(str);
    txCharacteristic->notify();
}

ArduinoBleChessClass ArduinoBleChess{};
#endif