#pragma once
#include "BleChessString.h"

class BleChessPeripheral
{
public:
    virtual void onCentralFeature(const BleChessString& feature);
    virtual void onCentralVariant(const BleChessString& variant);

    virtual void onCentralSetVariant(const BleChessString& variant);
    virtual void onCentralBegin(const BleChessString& fen);
    virtual void onCentralMove(const BleChessString& mv);
    virtual void onCentralEnd(const BleChessString& reason);

    virtual void onPeripheralMoveAck(bool ack);
    virtual void onPeripheralMovePromoted(const BleChessString& prom);
    virtual void onCentralUnexpectdCommand(const BleChessString& cmd);
    virtual void onCentralUnexpectdAck(bool ack);

    // Feature get_state
    virtual void onCentralGetState();
    // Feature set_state
    virtual void onCentralSetState();
    // Feature state_stream
    virtual void onCentralState(const BleChessString& fen);
    // Feature last_move
    virtual void onCentralLastMove(const BleChessString& mv);
    // Feature check
    virtual void onCentralCheck(const BleChessString& kingPos);
    // Feature msg
    virtual void onCentralMsg(const BleChessString& msg);
    // Feature undo
    virtual void onCentralUndo(const BleChessString& fen);
    // Feature undo_offer
    virtual void onCentralUndoOffer();
    virtual void onPeripheralUndoOfferAck(bool ack);
    // Feature draw_offer
    virtual void onCentralDrawOffer();
    virtual void onPeripheralDrawOfferAck(bool ack);
    // Feature side
    virtual void onCentralSide(const BleChessString& side);
    // Feature time
    virtual void onCentralTime(const BleChessString& time);
    // Feature score
    virtual void onCentralScore(const BleChessString& score);
    // Feature option
    virtual void onCentralOptionsBegin();
    virtual void onCentralOptionsReset();
    virtual void onCentralSetOption(const BleChessString& option);

    virtual void onOnlineCentralConnected();
    virtual void onOnlineCentralDisconnected();
    virtual void onOfflineCentralConnected();
    virtual void onOfflineCentralDisconnected();

    virtual ~BleChessPeripheral() = default;

protected:
    void sendPeripheralState(const BleChessString& fen);
    void sendPeripheralSync(const BleChessString& fen);
    void sendPeripheralUnsync(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);

    void sendPeripheralErr(const BleChessString& err);

    // Feature set_state
    void sendPeripheralUnsyncSetible(const BleChessString& fen);
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
    void sendPeripheralOption(const BleChessString& option);
    void sendPeripheralSetOption(const BleChessString& option);
};