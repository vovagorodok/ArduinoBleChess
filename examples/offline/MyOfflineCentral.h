#pragma once
#include <ArduinoBleChess.h>

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

class MyOfflineCentral : public BleChessOfflineCentral
{
public:
  void begin() {
    connect();
    getPeripheral().handleCentralBegin(STARTING_FEN);
  }
  void handleOnlineCentralConnected() override {
    Serial.println("online central connected, disconnect offline central");
    disconnect();
  }
  void handleOnlineCentralDisconnected() override {
    Serial.println("online central disconnected, connect offline central");
    connect();
  }
  void handlePeripheralMove(BleChessStringView mv) override {
    Serial.println("peripheral move accepted");
    getPeripheral().handlePeripheralMoveAck(true);
  }
};