#pragma once
#include <ArduinoBleChess.h>

class MyPeripheral : public BleChessPeripheral
{
public:
  void onNewRound(const BleChessString& fen) override {
    Serial.print("new round: ");
    Serial.println(fen.c_str());
  }
  void askPeripheralMakeMove() override {
    Serial.println("please move: ");
  }
  void askPeripheralStopMove() override {
    Serial.println("stop move: ");
  }
  void onCentralMove(const BleChessString& mv) override {
    Serial.print("moved from phone: ");
    Serial.println(mv.c_str());
  }
  void onPeripheralMoveRejected(const BleChessString& mv) override {
    Serial.print("move rejected: ");
    Serial.println(mv.c_str());
  }
  void onPeripheralMovePromoted(const BleChessString& mv) override {
    Serial.print("promoted on phone screen: ");
    Serial.println(mv.c_str());
  }
  void checkPeripheralMove() {
    if (Serial.available()) {
      BleChessString move(Serial.readString().c_str());
      Serial.print("peripheral move: ");
      Serial.println(move.c_str());
      peripheralMove(move);
    }
  }
};