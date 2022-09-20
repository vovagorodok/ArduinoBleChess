#pragma once
#include <ArduinoBleChess.h>

class MyPeripheral : public BleChessPeripheral
{
public:
  void onNewRound(const BleChess::String& fen) {
    Serial.print("new round: ");
    Serial.println(fen.c_str());
  }
  void askPeripheralMakeMove() {
    Serial.println("please move: ");
  }
  void askPeripheralStopMove() {
    Serial.println("stop move: ");
  }
  void onCentralMove(const BleChess::String& mv) {
    Serial.print("moved from phone: ");
    Serial.println(mv.c_str());
  }
  void onPeripheralMoveRejected(const BleChess::String& mv) {
    Serial.print("move rejected: ");
    Serial.println(mv.c_str());
  }
  void onPeripheralMovePromoted(const BleChess::String& mv) {
    Serial.print("promoted on phone screen: ");
    Serial.println(mv.c_str());
  }
  void checkPeripheralMove() {
    if (Serial.available()) {
      BleChess::String move(Serial.readString().c_str());
      Serial.print("peripheral move: ");
      Serial.println(move.c_str());
      peripheralMove(move);
    }
  }
};