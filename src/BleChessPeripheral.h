#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void handleCentralFeature(const BleChessString& feature);
    virtual void handleCentralVariant(const BleChessString& variant);

    virtual void handleCentralSetVariant(const BleChessString& variant);
    virtual void handleCentralBegin(const BleChessString& fen);
    virtual void handleCentralMove(const BleChessString& mv);
    virtual void handleCentralEnd(const BleChessString& reason);

    virtual void handlePeripheralMoveAck(bool ack);
    virtual void handlePeripheralMovePromoted(const BleChessString& prom);
    virtual void handleCentralUnexpectdCommand(const BleChessString& cmd);
    virtual void handleCentralUnexpectdAck(bool ack);

    // Feature get_state
    virtual void handleCentralGetState();
    // Feature set_state
    virtual void handleCentralSetState();
    // Feature state_stream
    virtual void handleCentralState(const BleChessString& fen);
    // Feature last_move
    virtual void handleCentralLastMove(const BleChessString& mv);
    // Feature check
    virtual void handleCentralCheck(const BleChessString& kingPos);
    // Feature msg
    virtual void handleCentralMsg(const BleChessString& msg);
    // Feature undo
    virtual void handleCentralUndo(const BleChessString& fen);
    // Feature undo_offer
    virtual void handleCentralUndoOffer();
    virtual void handlePeripheralUndoOfferAck(bool ack);
    // Feature draw_offer
    virtual void handleCentralDrawOffer();
    virtual void handlePeripheralDrawOfferAck(bool ack);
    // Feature side
    virtual void handleCentralSide(const BleChessString& side);
    // Feature time
    virtual void handleCentralTime(const BleChessString& time);
    // Feature score
    virtual void handleCentralScore(const BleChessString& score);
    // Feature option
    virtual void handleCentralOptionsBegin();
    virtual void handleCentralOptionsReset();
    virtual void handleCentralSetOption(const BleChessString& option);

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