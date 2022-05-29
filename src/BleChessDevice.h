#pragma once
#include "BleString.h"

class BleChessDevice
{
public:
    virtual void onNewGame(const Ble::String& fen) {}
    virtual void askDeviceMakeMove() {}
    virtual void askDeviceStopMove() {}
    virtual void onMove(const Ble::String& mv) {}
    virtual void onDeviceMoveRejected(const Ble::String& mv) {}
    virtual void onDeviceMovePromoted(const Ble::String& mv) {}
    virtual ~BleChessDevice() = default;

protected:
    void deviceMove(const Ble::String& mv);
    void telluser(const Ble::String& text);
};