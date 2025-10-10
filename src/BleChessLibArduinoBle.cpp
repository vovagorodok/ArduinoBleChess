#include "BleChessLibArduinoBle.h"
#ifdef BLE_CHESS_BLE_LIB_ARDUINO_BLE
#include "BleChessProtocol.h"
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
    chessProtocol.handleCentralCommand(rxValue);
}

void onConnectCallback(BLEDevice central)
{
    ArduinoBleChess.onConnect();
}

void onDisconnectCallback(BLEDevice central)
{
    ArduinoBleChess.onDisconnect();
}
}

bool BleChessLib::begin(const char* deviceName,
                        BleChessPeripheral& peripheral)
{
    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName);
    BLE.setDeviceName(deviceName);

    if (!begin(peripheral))
        return false;

    return BLE.advertise();
}

bool BleChessLib::begin(BleChessPeripheral& peripheral)
{
    bleChessConnection.registerPeripheral(peripheral);
    service.addCharacteristic(rxCharacteristic);
    service.addCharacteristic(txCharacteristic);
    rxCharacteristic.setEventHandler(BLEWritten, onWrite);
    BLE.setEventHandler(BLEConnected, onConnectCallback);
    BLE.setEventHandler(BLEDisconnected, onDisconnectCallback);
    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

bool BleChessLib::begin(const char* deviceName,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(deviceName, peripheral);
}

bool BleChessLib::begin(BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    bleChessConnection.registerOfflineCentral(offlineCentral);
    return begin(peripheral);
}

void BleChessLib::send(const String& str)
{
    txCharacteristic.setValue(str);
}

void BleChessLib::onConnect()
{
    bleChessConnection.onConnected();
}

void BleChessLib::onDisconnect()
{
    bleChessConnection.onDisconnected();
}

BleChessLib ArduinoBleChess{};
#endif