#pragma once
#include "BleChessString.h"

class CecpProtocol
{
public:
    void onPeripheralMove(const BleChessString& mv);
    void telluser(const BleChessString& text);
    void onMessage(const BleChessString& str);

private:
    void send(BleChessString str);
    static BleChessString getCmdParams(const BleChessString& cmd);
    static BleChessString getIllegalMove(const BleChessString& cmd);
    void askPeripheralMakeMove();
    void askPeripheralStopMove();

    bool isForceMode;
    bool isForcedPromotion;
};

extern CecpProtocol chessProtocol;