#pragma once
#include <ArduinoBleChess.h>

class MyPeripheral : public BleChessPeripheral
{
public:
  void onFen(const BleChessString& fen) override {
    Serial.print("fen: ");
    Serial.println(fen.c_str());
    sendAck(true);
  }
  void onMove(const BleChessString& mv) override {
    Serial.print("move: ");
    Serial.println(mv.c_str());
    sendAck(true);
  }
  void onMoveAck(bool ack) override {
    Serial.print("move ");
    Serial.println(ack ? "accepted" : "rejected");
  }
  void onPromote(const BleChessString& prom) override {
    Serial.print("promote: ");
    Serial.println(prom.c_str());
    sendAck(true);
  }
  void checkPeripheralMove() {
    if (Serial.available()) {
      BleChessString move(Serial.readString().c_str());
      Serial.print("send move: ");
      Serial.println(move.c_str());
      sendMove(move);
    }
  }
};