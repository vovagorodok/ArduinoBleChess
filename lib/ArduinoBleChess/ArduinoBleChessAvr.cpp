#if !defined(ESP32)
#include "ArduinoBleChessAvr.h"
#include "CecpProtocol.h"

namespace
{
#define SERVICE_UUID           "f5351050-b2c9-11ec-a0c0-b3bc53b08d33"
#define CHARACTERISTIC_UUID_RX "f53513ca-b2c9-11ec-a0c1-639b8957db99"
#define CHARACTERISTIC_UUID_TX "f535147e-b2c9-11ec-a0c2-8bbd706ec4e6"

// https://chess.stackexchange.com/questions/30004/longest-possible-fen
#define MAX_STR_SIZE 100

BLEService service(SERVICE_UUID);
BLEStringCharacteristic rxCharacteristic(CHARACTERISTIC_UUID_RX, BLEWrite, MAX_STR_SIZE);
BLEStringCharacteristic txCharacteristic(CHARACTERISTIC_UUID_TX, BLERead | BLENotify, MAX_STR_SIZE);

void onWrite(BLEDevice central, BLECharacteristic characteristic)
{
    auto rxValue = rxCharacteristic.value();
    Protocol.onMessage(rxValue);
}
}

void ArduinoBleChessClass::begin(const StringDecl& deviceName, ChessDevice& device)
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

void ArduinoBleChessClass::send(const StringDecl& str)
{
    txCharacteristic.setValue(str);
}

ArduinoBleChessClass ArduinoBleChess{};
#endif