#pragma once
#include "BleChessString.h"

class CecpProtocol
{
public:
    void onPeripheralMove(const BleChess::String& mv);
    void telluser(const BleChess::String& text);
    void onMessage(const BleChess::String& str);

private:
    void send(BleChess::String str);
    static BleChess::String getCmdParams(const BleChess::String& cmd);
    static BleChess::String getIllegalMove(const BleChess::String& cmd);
    void askPeripheralMakeMove();
    void askPeripheralStopMove();

    bool isForceMode;
    bool isForcedPromotion;
};

extern CecpProtocol chessProtocol;