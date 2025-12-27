#include "BleChessLibFake.h"
#ifdef BLE_CHESS_BLE_LIB_FAKE

bool BleChessLib::begin(const char* deviceName,
                        BleChessPeripheral& peripheral)
{
    return false;
}

bool BleChessLib::begin(BleChessPeripheral& peripheral)
{
    return false;
}

bool BleChessLib::begin(const char* deviceName,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    return false;
}

bool BleChessLib::begin(BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    return false;
}

bool BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral)
{
    return false;
}

bool BleChessLib::begin(BleChessServerFake* server,
                        BleChessPeripheral& peripheral)
{
    return false;
}

bool BleChessLib::begin(const std::string& deviceName,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    return false;
}

bool BleChessLib::begin(BleChessServerFake* server,
                        BleChessPeripheral& peripheral,
                        BleChessOfflineCentral& offlineCentral)
{
    return false;
}

void BleChessLib::send(const BleChessString& str)
{}

void BleChessLib::onConnect()
{}

void BleChessLib::onDisconnect()
{}

BleChessLib ArduinoBleChess{};
#endif