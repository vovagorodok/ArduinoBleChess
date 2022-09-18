#include "Defines.h"
#if defined(ARDUINO_BLE_LIB)
#include "ArduinoBleChessAtmel.h"
#include "CecpProtocol.h"
#include "BleConnection.h"

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

void onConnected(BLEDevice central)
{
    bleConnection.onConnected();
}

void onDisconnected(BLEDevice central)
{
    bleConnection.onDisconnected();
}
}

bool ArduinoBleChessClass::begin(const String& deviceName,
                                 BleChessPeripheral& device)
{
    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName.c_str());
    BLE.setDeviceName(deviceName.c_str());

    if (!begin(device))
        return false;

    return BLE.advertise();
}

bool ArduinoBleChessClass::begin(BleChessPeripheral& device)
{
    bleConnection.registerPeripheral(device);
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);
    BLE.setEventHandler(BLEConnected, onConnected);
    BLE.setEventHandler(BLEDisconnected, onDisconnected);
    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

bool ArduinoBleChessClass::begin(const String& deviceName,
                                 BleChessPeripheral& device,
                                 BleChessOfflineCentral& offlineCentral)
{
    bleConnection.registerOfflineCentral(offlineCentral);
    return begin(deviceName, device);
}

bool ArduinoBleChessClass::begin(BleChessPeripheral& device,
                                 BleChessOfflineCentral& offlineCentral)
{
    bleConnection.registerOfflineCentral(offlineCentral);
    return begin(device);
}

void ArduinoBleChessClass::send(const String& str)
{
    txCharacteristic.setValue(str);
}

ArduinoBleChessClass ArduinoBleChess{};
#endif