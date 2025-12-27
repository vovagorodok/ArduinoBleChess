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
    // Feature submove_state
    virtual void handleCentralState(BleChessStringView fen);
    // Feature last_move
    virtual void handleCentralLastMove(BleChessStringView mv);
    // Feature check
    virtual void handleCentralCheck(BleChessStringView kingPos);
    // Feature msg
    virtual void handleCentralMsg(BleChessStringView msg);
    // Feature undo_redo
    virtual void handleCentralUndo(BleChessStringView fen);
    virtual void handleCentralRedo(BleChessStringView fen);
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
    BLE_CHESS_VIRTUAL void sendPeripheralState(const BleChessString& fen);
    BLE_CHESS_VIRTUAL void sendPeripheralSync(const BleChessString& fen);
    BLE_CHESS_VIRTUAL void sendPeripheralUnsync(const BleChessString& fen);
    BLE_CHESS_VIRTUAL void sendPeripheralMove(const BleChessString& mv);
    BLE_CHESS_VIRTUAL void sendPeripheralAck(bool ack);

    BLE_CHESS_VIRTUAL void sendPeripheralErr(const BleChessString& err);

    // Feature set_state
    BLE_CHESS_VIRTUAL void sendPeripheralUnsyncSettable(const BleChessString& fen);
    // Feature moved
    BLE_CHESS_VIRTUAL void sendPeripheralMoved();
    // Feature msg
    BLE_CHESS_VIRTUAL void sendPeripheralMsg(const BleChessString& msg);
    // Feature resign
    BLE_CHESS_VIRTUAL void sendPeripheralResign();
    // Feature undo_offer
    BLE_CHESS_VIRTUAL void sendPeripheralUndoOffer();
    // Feature draw_offer
    BLE_CHESS_VIRTUAL void sendPeripheralDrawOffer();
    // Feature option
    BLE_CHESS_VIRTUAL void sendPeripheralOptionsEnd();
    BLE_CHESS_VIRTUAL void sendPeripheralOptionsReset();
    BLE_CHESS_VIRTUAL void sendPeripheralOption(const BleChessString& option);
    BLE_CHESS_VIRTUAL void sendPeripheralSetOption(const BleChessString& option);
};