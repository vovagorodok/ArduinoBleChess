#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void onNewRound(const BleChessString& fen) {}
    virtual void askPeripheralMakeMove() {}
    virtual void askPeripheralStopMove() {}
    virtual void onCentralMove(const BleChessString& mv) {}
    virtual void onPeripheralMoveRejected(const BleChessString& mv) {}
    virtual void onPeripheralMovePromoted(const BleChessString& mv) {}
    virtual ~BleChessPeripheral() = default;

protected:
    void peripheralMove(const BleChessString& mv);
    void telluser(const BleChessString& text);
};