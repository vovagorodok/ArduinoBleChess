#pragma once
#include "BleString.h"

class ChessDevice
{
public:
    virtual void onNewGame(const BleString& fen) {}
    virtual void askDeviceMakeMove() {}
    virtual void askDeviceStopMove() {}
    virtual void onMove(const BleString& mv) {}
    virtual void onDeviceMoveRejected(const BleString& mv) {}
    virtual void onDeviceMovePromoted(const BleString& mv) {}
    virtual ~ChessDevice() = default;

protected:
    void deviceMove(const BleString& mv);
    void telluser(const BleString& text);
};