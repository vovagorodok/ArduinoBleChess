#pragma once
#include <string>

class ChessDevice
{
public:
    virtual void onNewGame(const std::string& fen) {};
    virtual void askDeviceMakeMove() {};
    virtual void askDeviceStopMove() {};
    virtual void onMove(const std::string& mv) {};
    virtual void onDeviceMoveRejected(const std::string& mv) {};
    virtual ~ChessDevice() = default;

protected:
    void deviceMove(const std::string& mv);
};