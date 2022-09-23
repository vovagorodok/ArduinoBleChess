#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void onOnlineCentralConnected() {}
    virtual void onOnlineCentralDisconnected() {}
    virtual void onPeripheralMove(const BleChessString& mv) {}
    virtual void onTelluser(const BleChessString& text) {}
    virtual ~BleChessOfflineCentral() = default;

protected:
    void connect();
    void disconnect();
    bool isConnected() const;
    BleChessPeripheral& peripheral();

private:
    bool connected = false;
};