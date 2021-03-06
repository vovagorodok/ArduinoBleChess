#include "Defines.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include "ArduinoBleChessNimBle.h"
#include "CecpProtocol.h"

namespace
{
#define SERVICE_UUID           "f5351050-b2c9-11ec-a0c0-b3bc53b08d33"
#define CHARACTERISTIC_UUID_RX "f53513ca-b2c9-11ec-a0c1-639b8957db99"
#define CHARACTERISTIC_UUID_TX "f535147e-b2c9-11ec-a0c2-8bbd706ec4e6"
}

bool ArduinoBleChessClass::begin(const std::string &deviceName, BleChessDevice& device)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    if(!begin(server, device))
        return false;

    auto* advertising = server->getAdvertising();
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
    return advertising->start();
}

bool ArduinoBleChessClass::begin(NimBLEServer* server, BleChessDevice& device)
{
    Protocol.begin(device);
    auto* service = server->createService(SERVICE_UUID);

    auto* rxCharacteristic = service->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        NIMBLE_PROPERTY::WRITE
    );
    rxCharacteristic->setCallbacks(this);

    auto* txCharacteristic = service->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->txCharacteristic = txCharacteristic;

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    return service->start();
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