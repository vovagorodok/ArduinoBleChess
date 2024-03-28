#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void onOnlineCentralConnected() {}
    virtual void onOnlineCentralDisconnected() {}
    virtual void onFen(const BleChessString& fen) {}
    virtual void onMove(const BleChessString& mv) {}
    virtual void onAck(bool ack) {}
    virtual void onMsg(const BleChessString& msg) {}
    virtual ~BleChessOfflineCentral() = default;

protected:
    void connect();
    void disconnect();
    bool isConnected() const;
    BleChessPeripheral& peripheral();

private:
    bool connected = false;
};