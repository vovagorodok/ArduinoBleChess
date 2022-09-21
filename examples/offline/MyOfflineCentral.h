#pragma once
#include <ArduinoBleChess.h>

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

class MyOfflineCentral : public BleChessOfflineCentral
{
public:
  void begin() {
    connect();
    peripheral().onNewRound(STARTING_FEN);
  }
  void onOnlineCentralConnected() {
    Serial.println("online central connected, disconnect offline central");
    disconnect();
  }
  void onOnlineCentralDisconnected() {
    Serial.println("online central disconnected, connect offline central");
    connect();
  }
  void onPeripheralMove(const BleChess::String& mv) {
    Serial.println("peripheral move accepted, asking for next move");
    peripheral().askPeripheralMakeMove();
  }
  void onTelluser(const BleChess::String& text) {
    Serial.println(text.c_str());
  }
};