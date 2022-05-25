#pragma once
#include "StringDecl.h"

class ChessDevice
{
public:
    virtual void onNewGame(const StringDecl& fen) {}
    virtual void askDeviceMakeMove() {}
    virtual void askDeviceStopMove() {}
    virtual void onMove(const StringDecl& mv) {}
    virtual void onDeviceMoveRejected(const StringDecl& mv) {}
    virtual ~ChessDevice() = default;

protected:
    void deviceMove(const StringDecl& mv);
};