#pragma once
#include "BleChessString.h"

class BleChessPeripheral;

class BleChessProtocol
{
public:
    BleChessProtocol();

    void sendFen(const BleChessString& fen);
    void sendMove(const BleChessString& mv);
    void sendAck(bool ack);
    void sendMsg(const BleChessString& msg);
    void onCommand(const BleChessString& cmd);

private:
    void send(BleChessString str);

    typedef void(BleChessPeripheral::*AckMethod)(bool);
    AckMethod onAckMethod;
};

extern BleChessProtocol chessProtocol;