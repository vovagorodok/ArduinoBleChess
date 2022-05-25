#pragma once
#include "StringDecl.h"

class ChessDevice;

class CecpProtocol
{
public:
    void begin(ChessDevice&);
    void onDeviceMove(const StringDecl& mv);
    void onMessage(const StringDecl& str);

private:
    void send(StringDecl str);
    static StringDecl getCmdParams(const StringDecl& cmd);
    static StringDecl getIllegalMove(const StringDecl& cmd);

    bool isForceMode;
    bool isForcedPromotion;
    ChessDevice* device;
};

extern CecpProtocol Protocol;