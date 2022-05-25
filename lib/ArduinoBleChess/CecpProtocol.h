#pragma once
#include "BleString.h"

class ChessDevice;

class CecpProtocol
{
public:
    void begin(ChessDevice&);
    void onDeviceMove(const BleString& mv);
    void onMessage(const BleString& str);

private:
    void send(BleString str);
    static BleString getCmdParams(const BleString& cmd);
    static BleString getIllegalMove(const BleString& cmd);

    bool isForceMode;
    bool isForcedPromotion;
    ChessDevice* device;
};

extern CecpProtocol Protocol;