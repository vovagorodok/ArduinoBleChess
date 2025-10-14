#include "BleChessLibESP32.h"
#ifdef BLE_CHESS_BLE_LIB_ESP32
#include "BleChessProtocol.h"
#include "BleChessConnection.h"

void BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    begin(server, peripheral);

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_CHESS_SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
    advertising->start();
}

void BleChessLib::begin(BLEServer* server,
                        BleChessPeripheral& peripheral)
{
    bleChessConnection.registerPeripheral(peripheral);
    server->setCallbacks(this);
    auto* service = server->createService(BLE_CHESS_SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        BLE_CHESS_CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        BLE_CHESS_CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _txCharacteristic = txCharacteristic;

    service->start();
}

void BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(deviceName, peripheral);
}

void BleChessLib::begin(BLEServer* server,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(server, peripheral);
}

void BleChessLib::onConnect()
{
    bleChessConnection.onConnected();
}

void BleChessLib::onDisconnect()
{
    bleChessConnection.onDisconnected();
}

void BleChessLib::onConnect(BLEServer* srv)
{
    onConnect();
}

void BleChessLib::onDisconnect(BLEServer* srv)
{
    onDisconnect();
}

void BleChessLib::onWrite(BLECharacteristic* characteristic)
{
    std::string rxValue = characteristic->getValue();
    chessProtocol.handleCentralCommand(rxValue);
}

void BleChessLib::send(const std::string& str)
{
    _txCharacteristic->setValue(str);
    _txCharacteristic->notify();
}

BleChessLib ArduinoBleChess{};
#endif