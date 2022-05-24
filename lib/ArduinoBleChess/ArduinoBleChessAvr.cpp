#if !defined(ESP32)
#include "ArduinoBleChessAvr.h"
#include "CecpProtocol.h"

namespace
{
#define SERVICE_UUID           "f5351050-b2c9-11ec-a0c0-b3bc53b08d33"
#define CHARACTERISTIC_UUID_RX "f53513ca-b2c9-11ec-a0c1-639b8957db99"
#define CHARACTERISTIC_UUID_TX "f535147e-b2c9-11ec-a0c2-8bbd706ec4e6"

BLEService service(SERVICE_UUID);
BLEStringCharacteristic rxCharacteristic(CHARACTERISTIC_UUID_RX, BLEWrite, 100);
BLEStringCharacteristic txCharacteristic(CHARACTERISTIC_UUID_TX, BLERead | BLENotify, 100);

void onWrite(BLEDevice central, BLECharacteristic characteristic)
{
    auto rxValue = rxCharacteristic.value();
    Protocol.onMessage(rxValue.c_str());
}
}

void ArduinoBleChessClass::begin(const std::string &deviceName, ChessDevice& device)
{
    if (!BLE.begin())
        while (true);
    BLE.setLocalName(deviceName.c_str());

    begin(device);

    BLE.advertise();
}

void ArduinoBleChessClass::begin(ChessDevice& device)
{
    Protocol.begin(device);
    BLE.setAdvertisedService(service);
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    BLE.addService(service);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);
}

void ArduinoBleChessClass::send(const std::string& str)
{
    txCharacteristic.setValue(str.c_str());
}

ArduinoBleChessClass ArduinoBleChess{};
#endif