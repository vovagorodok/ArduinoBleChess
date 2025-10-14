#include "BleChessLibNimBleArduino.h"
#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
#include "BleChessProtocol.h"
#include "BleChessConnection.h"

bool BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    if(!begin(server, peripheral))
        return false;

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_CHESS_SERVICE_UUID);
#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
#endif
    return advertising->start();
}

bool BleChessLib::begin(BLEServer* server,
                        BleChessPeripheral& peripheral)
{
    bleChessConnection.registerPeripheral(peripheral);
    server->setCallbacks(this);
    auto* service = server->createService(BLE_CHESS_SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        BLE_CHESS_CHARACTERISTIC_UUID_RX,
        NIMBLE_PROPERTY::WRITE
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        BLE_CHESS_CHARACTERISTIC_UUID_TX,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    _txCharacteristic = txCharacteristic;

    return service->start();
}

bool BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(deviceName, peripheral);
}

bool BleChessLib::begin(BLEServer* server,
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

#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
void BleChessLib::onConnect(BLEServer* srv)
#else
void BleChessLib::onConnect(BLEServer* srv, BLEConnInfo& connInfo)
#endif
{
    onConnect();
}

#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
void BleChessLib::onDisconnect(BLEServer* srv)
#else
void BleChessLib::onDisconnect(BLEServer* srv, BLEConnInfo& connInfo, int reason)
#endif
{
    onDisconnect();
}

#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
void BleChessLib::onWrite(BLECharacteristic* characteristic)
#else
void BleChessLib::onWrite(BLECharacteristic* characteristic, BLEConnInfo& connInfo)
#endif
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