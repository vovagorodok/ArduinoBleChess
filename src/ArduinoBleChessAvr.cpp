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
BLEStringCharacteristic rxCharacteristic(CHARACTERISTIC_UUID_RX, BLEWrite | BLERead | BLENotify, MAX_STR_SIZE);
BLEStringCharacteristic txCharacteristic(CHARACTERISTIC_UUID_TX, BLEWrite | BLERead | BLENotify, MAX_STR_SIZE);

void onWrite(BLEDevice central, BLECharacteristic characteristic)
{
    Serial.print("onWrite: BLE: ");
    Serial.println((uint32_t)&BLE, HEX);

    auto rxValue = rxCharacteristic.value();
    Protocol.onMessage(rxValue);
}

void connected(BLEDevice device) {
    Serial.println("connected");
}
void disconnected(BLEDevice device) {
    Serial.println("disconnected");
}
void discovered(BLEDevice device) {
    Serial.println("discovered");
}
}

bool ArduinoBleChessClass::begin(const BleString& deviceName, BleChessDevice& device)
{
    Serial.print("begin: BLE: ");
    Serial.println((uint32_t)&BLE, HEX);
    Serial.print("begin: ArduinoBleChessClass: ");
    Serial.println((uint32_t)this, HEX);
    Serial.print("begin: Protocol: ");
    Serial.println((uint32_t)&Protocol, HEX);

    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName.c_str());
    // BLE.setDeviceName(deviceName.c_str());
    BLE.setEventHandler(BLEConnected, connected);
    BLE.setEventHandler(BLEDisconnected, disconnected);
    BLE.setEventHandler(BLEDiscovered, discovered);

    if (!begin(device))
        return false;

    return BLE.advertise();
}

bool ArduinoBleChessClass::begin(BleChessDevice& device)
{
    Protocol.begin(device);
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);
    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

void ArduinoBleChessClass::send(const BleString& str)
{
    Serial.print("send: BLE: ");
    Serial.println((uint32_t)&BLE, HEX);
    Serial.print("send: ArduinoBleChessClass: ");
    Serial.println((uint32_t)this, HEX);
    Serial.print("send: Protocol: ");
    Serial.println((uint32_t)&Protocol, HEX);
    txCharacteristic.setValue(str);
}
void ArduinoBleChessClass::checkIfValueRecived()
{
    if (rxCharacteristic.valueUpdated())
        Serial.println("value available");
}

ArduinoBleChessClass ArduinoBleChess{};
#endif