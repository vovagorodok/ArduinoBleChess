#include "BleChessDefines.h"
#if defined(ARDUINO_BLE_LIB)
#include "ArduinoBleChessCommon.h"
#include "BleChessUuids.h"
#include "CecpProtocol.h"
#include "BleChessConnection.h"

namespace
{
// https://chess.stackexchange.com/questions/30004/longest-possible-fen
#define MAX_STR_SIZE 100

BLEService service(BLE_CHESS_SERVICE_UUID);
BLEStringCharacteristic rxCharacteristic(BLE_CHESS_CHARACTERISTIC_UUID_RX, BLEWrite, MAX_STR_SIZE);
BLEStringCharacteristic txCharacteristic(BLE_CHESS_CHARACTERISTIC_UUID_TX, BLERead | BLENotify, MAX_STR_SIZE);

void onWrite(BLEDevice central, BLECharacteristic characteristic)
{
    auto rxValue = rxCharacteristic.value();
    chessProtocol.onMessage(rxValue);
}

void onConnected(BLEDevice central)
{
    bleChessConnection.onConnected();
}

void onDisconnected(BLEDevice central)
{
    bleChessConnection.onDisconnected();
}
}

bool ArduinoBleChessClass::begin(const String& deviceName,
                                 BleChessPeripheral& peripheral)
{
    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName.c_str());
    BLE.setDeviceName(deviceName.c_str());

    if (!begin(peripheral))
        return false;

    return BLE.advertise();
}

bool ArduinoBleChessClass::begin(BleChessPeripheral& peripheral)
{
    bleChessConnection.registerPeripheral(peripheral);
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);
    BLE.setEventHandler(BLEConnected, onConnected);
    BLE.setEventHandler(BLEDisconnected, onDisconnected);
    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

bool ArduinoBleChessClass::begin(const String& deviceName,
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

void ArduinoBleChessClass::send(const String& str)
{
    txCharacteristic.setValue(str);
}

ArduinoBleChessClass ArduinoBleChess{};
#endif