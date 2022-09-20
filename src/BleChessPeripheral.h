#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void onNewRound(const BleChess::String& fen) {}
    virtual void askPeripheralMakeMove() {}
    virtual void askPeripheralStopMove() {}
    virtual void onCentralMove(const BleChess::String& mv) {}
    virtual void onPeripheralMoveRejected(const BleChess::String& mv) {}
    virtual void onPeripheralMovePromoted(const BleChess::String& mv) {}
    virtual ~BleChessPeripheral() = default;

protected:
    void peripheralMove(const BleChess::String& mv);
    void telluser(const BleChess::String& text);
};