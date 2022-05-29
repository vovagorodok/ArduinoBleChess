#pragma once
#include "BleString.h"

class BleChessDevice;

class CecpProtocol
{
public:
    void begin(BleChessDevice&);
    void onDeviceMove(const BleString& mv);
    void telluser(const BleString& text);
    void onMessage(const BleString& str);

private:
    void send(BleString str);
    static BleString getCmdParams(const BleString& cmd);
    static BleString getIllegalMove(const BleString& cmd);
    void askDeviceMakeMove();
    void askDeviceStopMove();

    bool isForceMode;
    bool isForcedPromotion;
    bool isDeviceMove;
    BleChessDevice* device;
};

extern CecpProtocol Protocol;