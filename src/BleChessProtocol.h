#pragma once
#include "BleChessString.h"

class BleChessPeripheral;

class BleChessProtocol
{
public:
    BleChessProtocol();

    void onCentralCommand(const BleChessString& cmd);

    void sendPeripheralFen(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);
    void sendPeripheralMsg(const BleChessString& msg);

private:
    void send(BleChessString str);

    typedef void(BleChessPeripheral::*AckMethod)(bool);
    AckMethod onAckMethod;
};

extern BleChessProtocol chessProtocol;