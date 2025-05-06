#pragma once
#include "BleChessString.h"

class BleChessPeripheral;
class BleChessOfflineCentral;

class BleChessConnection
{
public:
    BleChessConnection();

    void onConnected();
    void onDisconnected();

    void sendPeripheralState(const BleChessString& fen);
    void sendPeripheralSync(const BleChessString& fen);
    void sendPeripheralUnsync(const BleChessString& fen);
    void sendPeripheralMove(const BleChessString& mv);
    void sendPeripheralAck(bool ack);
    void sendPeripheralErr(const BleChessString& err);
    void sendPeripheralUnsyncSetible(const BleChessString& fen);
    void sendPeripheralMoved();
    void sendPeripheralMsg(const BleChessString& msg);
    void sendPeripheralResign();
    void sendPeripheralUndoOffer();
    void sendPeripheralDrawOffer();
    void sendPeripheralOptionsEnd();
    void sendPeripheralOption(const BleChessString& option);
    void sendPeripheralSetOption(const BleChessString& option);

    void connectOfflineCentral();
    void disconnectOfflineCentral();
    BleChessPeripheral& peripheralForOffline();
    BleChessPeripheral& peripheralForOnline();

    void registerPeripheral(BleChessPeripheral& peripheral);
    void registerOfflineCentral(BleChessOfflineCentral& central);

private:
    BleChessPeripheral* registeredPeripheral;
    BleChessOfflineCentral* registeredCentral;
    BleChessPeripheral* offlinePeripheral;
    BleChessOfflineCentral* offlineCentral;
};

extern BleChessConnection bleChessConnection;