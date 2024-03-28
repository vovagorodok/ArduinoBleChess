#pragma once
#include <ArduinoBleChess.h>

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

class MyOfflineCentral : public BleChessOfflineCentral
{
public:
  void begin() {
    connect();
    peripheral().onFen(STARTING_FEN);
  }
  void onOnlineCentralConnected() override {
    Serial.println("online central connected, disconnect offline central");
    disconnect();
  }
  void onOnlineCentralDisconnected() override {
    Serial.println("online central disconnected, connect offline central");
    connect();
  }
  void onMove(const BleChessString& mv) override {
    Serial.println("peripheral move accepted");
    peripheral().onMoveAck(true);
  }
  void onMsg(const BleChessString& msg) override {
    Serial.println(msg.c_str());
  }
};