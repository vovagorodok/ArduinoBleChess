#pragma once
#include "BleString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void onOnlineCentralConnected() {}
    virtual void onOnlineCentralDisconnected() {}
    virtual void onPeripheralMove(const Ble::String& mv) {}
    virtual void onTelluser(const Ble::String& text) {}
    virtual ~BleChessOfflineCentral() = default;

protected:
    BleChessPeripheral& peripheral();
    void connect();
    void disconnect();
};