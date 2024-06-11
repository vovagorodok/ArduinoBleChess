#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void onCentralFeature(const BleChessString& feature);
    virtual void onCentralVariant(const BleChessString& variant);

    virtual void onCentralFen(const BleChessString& fen);
    virtual void onCentralMove(const BleChessString& mv);
    virtual void onCentralAck(bool ack);
    virtual void onPeripheralFenAck(bool ack);
    virtual void onPeripheralMoveAck(bool ack);
    virtual void onPeripheralMovePromoted(const BleChessString& prom);

    virtual void onCentralLastMove(const BleChessString& mv);

    virtual ~BleChessPeripheral() = default;

protected:
    void sendPeripheralFen(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);

    void sendPeripheralMsg(const BleChessString& msg);
};