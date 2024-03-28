#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void onFeature(const BleChessString& feature);
    virtual void onVariant(const BleChessString& variant);

    virtual void onFen(const BleChessString& fen);
    virtual void onFenAck(bool ack);
    virtual void onMove(const BleChessString& mv);
    virtual void onMoveAck(bool ack);
    virtual void onPromote(const BleChessString& prom);

    virtual ~BleChessPeripheral() = default;

protected:
    void sendFen(const BleChessString& fen);
    void sendMove(const BleChessString& mv);
    void sendAck(bool ack);

    void sendMsg(const BleChessString& msg);
};