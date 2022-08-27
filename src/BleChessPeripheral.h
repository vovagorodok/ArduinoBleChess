#pragma once
#include "BleString.h"

class BleChessPeripheral
{
public:
    virtual void onNewRound(const Ble::String& fen) {}
    virtual void askPeripheralMakeMove() {}
    virtual void askPeripheralStopMove() {}
    virtual void onCentralMove(const Ble::String& mv) {}
    virtual void onPeripheralMoveRejected(const Ble::String& mv) {}
    virtual void onPeripheralMovePromoted(const Ble::String& mv) {}
    virtual ~BleChessPeripheral() = default;

protected:
    void peripheralMove(const Ble::String& mv);
    void telluser(const Ble::String& text);
};