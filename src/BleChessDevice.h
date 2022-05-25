#pragma once
#include "BleString.h"

class BleChessDevice
{
public:
    virtual void onNewGame(const BleString& fen) {}
    virtual void askDeviceMakeMove() {}
    virtual void askDeviceStopMove() {}
    virtual void onMove(const BleString& mv) {}
    virtual void onDeviceMoveRejected(const BleString& mv) {}
    virtual void onDeviceMovePromoted(const BleString& mv) {}
    virtual ~BleChessDevice() = default;

protected:
    void deviceMove(const BleString& mv);
    void telluser(const BleString& text);
};