#pragma once
#include "BleString.h"

class CecpProtocol
{
public:
    void onPeripheralMove(const Ble::String& mv);
    void telluser(const Ble::String& text);
    void onMessage(const Ble::String& str);

private:
    void send(Ble::String str);
    static Ble::String getCmdParams(const Ble::String& cmd);
    static Ble::String getIllegalMove(const Ble::String& cmd);
    void askPeripheralMakeMove();
    void askPeripheralStopMove();

    bool isForceMode;
    bool isForcedPromotion;
};

extern CecpProtocol Protocol;