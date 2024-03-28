#pragma once
#include "BleChessString.h"

class BleChessPeripheral;

class CecpProtocol
{
public:
    CecpProtocol();

    void sendFen(const BleChessString& fen);
    void sendMove(const BleChessString& mv);
    void sendAck(bool ack);
    void sendMsg(const BleChessString& msg);
    void onCommand(const BleChessString& cmd);

private:
    void send(BleChessString str);
    static BleChessString getCmdParams(const BleChessString& cmd);

    typedef void(BleChessPeripheral::*AckMethod)(bool);
    AckMethod onAckMethod;
};

extern CecpProtocol chessProtocol;