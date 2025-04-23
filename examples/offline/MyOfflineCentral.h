#pragma once
#include <ArduinoBleChess.h>

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

class MyOfflineCentral : public BleChessOfflineCentral
{
public:
  void begin() {
    connect();
    peripheral().onCentralBegin(STARTING_FEN);
  }
  void onOnlineCentralConnected() override {
    Serial.println("online central connected, disconnect offline central");
    disconnect();
  }
  void onOnlineCentralDisconnected() override {
    Serial.println("online central disconnected, connect offline central");
    connect();
  }
  void onPeripheralMove(const BleChessString& mv) override {
    Serial.println("peripheral move accepted");
    peripheral().onPeripheralMoveAck(true);
  }
};