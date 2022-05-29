#pragma once
#include "BleString.h"

class BleChessDevice;

class CecpProtocol
{
public:
    void begin(BleChessDevice&);
    void onDeviceMove(const Ble::String& mv);
    void telluser(const Ble::String& text);
    void onMessage(const Ble::String& str);

private:
    void send(Ble::String str);
    static Ble::String getCmdParams(const Ble::String& cmd);
    static Ble::String getIllegalMove(const Ble::String& cmd);
    void askDeviceMakeMove();
    void askDeviceStopMove();

    bool isForceMode;
    bool isForcedPromotion;
    bool isDeviceMove;
    BleChessDevice* device;
};

extern CecpProtocol Protocol;