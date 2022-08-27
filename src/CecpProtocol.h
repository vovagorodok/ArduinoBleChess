#pragma once
#include "BleString.h"

class BleChessPeripheral;

class CecpProtocol
{
public:
    void begin(BleChessPeripheral&);
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
    BleChessPeripheral* device;
};

extern CecpProtocol Protocol;