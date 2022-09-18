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
    Serial.print("online central connected, disconnect offline central");
    disconnect();
  }
  void onOnlineCentralDisconnected() {
    Serial.print("online central disconnected, connect offline central");
    connect();
  }
  void onPeripheralMove(const Ble::String& mv) {
    Serial.print("peripheral move accepted, asking for next move");
    peripheral().askPeripheralMakeMove();
  }
  void onTelluser(const Ble::String& text) {
    Serial.print(text);
  }
};