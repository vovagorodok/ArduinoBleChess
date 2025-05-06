#pragma once
#include "BleChessString.h"

class BleChessPeripheral;

class BleChessProtocol
{
public:
    BleChessProtocol();

    void onCentralCommand(const BleChessString& cmd);

    void sendPeripheralState(const BleChessString& fen);
    void sendPeripheralSync(const BleChessString& fen);
    void sendPeripheralUnsync(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);
    void sendPeripheralErr(const BleChessString& err);
    void sendPeripheralUnsyncSetible(const BleChessString& fen);
    void sendPeripheralMoved();
    void sendPeripheralMsg(const BleChessString& msg);
    void sendPeripheralResign();
    void sendPeripheralUndoOffer();
    void sendPeripheralDrawOffer();
    void sendPeripheralOptionsEnd();
    void sendPeripheralOption(const BleChessString& option);
    void sendPeripheralSetOption(const BleChessString& option);

private:
    void send(BleChessString str);

    typedef void(BleChessPeripheral::*AckMethod)(bool);
    typedef void(BleChessPeripheral::*PromotedMethod)(const BleChessString&);
    AckMethod onAckMethod;
    PromotedMethod onPromotedMethod;
};

extern BleChessProtocol chessProtocol;