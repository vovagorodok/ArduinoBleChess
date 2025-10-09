#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void handleCentralFeature(BleChessStringView feature);
    virtual void handleCentralVariant(BleChessStringView variant);

    virtual void handleCentralSetVariant(BleChessStringView variant);
    virtual void handleCentralBegin(BleChessStringView fen);
    virtual void handleCentralMove(BleChessStringView mv);
    virtual void handleCentralEnd(BleChessStringView reason);

    virtual void handlePeripheralMoveAck(bool ack);
    virtual void handlePeripheralMovePromoted(BleChessStringView prom);

    virtual void handleCentralUnexpectdCommand(BleChessStringView cmd);
    virtual void handleCentralUnexpectdCommand(BleChessStringView cmd, BleChessStringView params);
    virtual void handleCentralUnexpectdAck(bool ack);

    // Feature get_state
    virtual void handleCentralGetState();
    // Feature set_state
    virtual void handleCentralSetState();
    // Feature state_stream
    virtual void handleCentralState(BleChessStringView fen);
    // Feature last_move
    virtual void handleCentralLastMove(BleChessStringView mv);
    // Feature check
    virtual void handleCentralCheck(BleChessStringView kingPos);
    // Feature msg
    virtual void handleCentralMsg(BleChessStringView msg);
    // Feature undo
    virtual void handleCentralUndo(BleChessStringView fen);
    // Feature undo_offer
    virtual void handleCentralUndoOffer();
    virtual void handlePeripheralUndoOfferAck(bool ack);
    // Feature draw_offer
    virtual void handleCentralDrawOffer();
    virtual void handlePeripheralDrawOfferAck(bool ack);
    // Feature side
    virtual void handleCentralSide(BleChessStringView side);
    // Feature time
    virtual void handleCentralTime(BleChessStringView time);
    // Feature score
    virtual void handleCentralScore(BleChessStringView score);
    // Feature option
    virtual void handleCentralOptionsBegin();
    virtual void handleCentralOptionsReset();
    virtual void handleCentralSetOption(BleChessStringView option);

    virtual void handleOnlineCentralConnected();
    virtual void handleOnlineCentralDisconnected();
    virtual void handleOfflineCentralConnected();
    virtual void handleOfflineCentralDisconnected();

    virtual ~BleChessPeripheral() = default;

protected:
    void sendPeripheralState(const BleChessString& fen);
    void sendPeripheralSync(const BleChessString& fen);
    void sendPeripheralUnsync(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);

    void sendPeripheralErr(const BleChessString& err);

    // Feature set_state
    void sendPeripheralUnsyncSettable(const BleChessString& fen);
    // Feature moved
    void sendPeripheralMoved();
    // Feature msg
    void sendPeripheralMsg(const BleChessString& msg);
    // Feature resign
    void sendPeripheralResign();
    // Feature undo_offer
    void sendPeripheralUndoOffer();
    // Feature draw_offer
    void sendPeripheralDrawOffer();
    // Feature option
    void sendPeripheralOptionsEnd();
    void sendPeripheralOptionsReset();
    void sendPeripheralOption(const BleChessString& option);
    void sendPeripheralSetOption(const BleChessString& option);
};