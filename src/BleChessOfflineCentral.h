#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void onOnlineCentralConnected() {}
    virtual void onOnlineCentralDisconnected() {}
    virtual void onPeripheralMove(const BleChess::String& mv) {}
    virtual void onTelluser(const BleChess::String& text) {}
    virtual ~BleChessOfflineCentral() = default;

protected:
    BleChessPeripheral& peripheral();
    void connect();
    void disconnect();
};