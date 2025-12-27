#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void handleOnlineCentralConnected() {}
    virtual void handleOnlineCentralDisconnected() {}
    virtual void handlePeripheralMove(BleChessStringView mv) {}
    virtual void handlePeripheralAck(bool ack) {}

    virtual void handlePeripheralUndoOffer() {}
    virtual void handlePeripheralDrawOffer() {}

    virtual ~BleChessOfflineCentral() = default;

protected:
    BLE_CHESS_VIRTUAL void connect();
    BLE_CHESS_VIRTUAL void disconnect();
    BLE_CHESS_VIRTUAL bool isConnected() const;
    BLE_CHESS_VIRTUAL BleChessPeripheral& peripheral();

private:
    bool connected = false;
};