#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void onOnlineCentralConnected() {}
    virtual void onOnlineCentralDisconnected() {}
    virtual void onPeripheralFen(const BleChessString& fen) {}
    virtual void onPeripheralMove(const BleChessString& mv) {}
    virtual void onPeripheralAck(bool ack) {}
    virtual void onPeripheralMsg(const BleChessString& msg) {}
    virtual ~BleChessOfflineCentral() = default;

protected:
    void connect();
    void disconnect();
    bool isConnected() const;
    BleChessPeripheral& peripheral();

private:
    bool connected = false;
};