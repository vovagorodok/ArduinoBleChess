#pragma once
#include "BleChessString.h"
#include "BleChessPeripheral.h"

class BleChessOfflineCentral
{
public:
    virtual void handleOnlineCentralConnected() {}
    virtual void handleOnlineCentralDisconnected() {}
    virtual void handlePeripheralMove(const BleChessString& mv) {}
    virtual void handlePeripheralAck(bool ack) {}

    virtual void handlePeripheralUndoOffer() {}
    virtual void handlePeripheralDrawOffer() {}

    virtual ~BleChessOfflineCentral() = default;

protected:
    void connect();
    void disconnect();
    bool isConnected() const;
    BleChessPeripheral& peripheral();

private:
    bool connected = false;
};