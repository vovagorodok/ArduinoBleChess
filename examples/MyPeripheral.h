#pragma once
#include <ArduinoBleChess.h>

class MyPeripheral : public BleChessPeripheral
{
public:
  void handleCentralBegin(const BleChessString& fen) override {
    Serial.print("begin: ");
    Serial.println(fen.c_str());
    sendPeripheralSync(fen);
  }
  void handleCentralMove(const BleChessString& mv) override {
    Serial.print("move: ");
    Serial.println(mv.c_str());
  }
  void handlePeripheralMoveAck(bool ack) override {
    Serial.print("move ");
    Serial.println(ack ? "accepted" : "rejected");
  }
  void handlePeripheralMovePromoted(const BleChessString& prom) override {
    Serial.print("promote: ");
    Serial.println(prom.c_str());
  }
  void handleCentralEnd(const BleChessString& reason) override {
    Serial.print("end: ");
    Serial.println(reason.c_str());
  }
  void checkPeripheralMove() {
    if (Serial.available()) {
      BleChessString move(Serial.readString().c_str());
      Serial.print("send move: ");
      Serial.println(move.c_str());
      sendPeripheralMove(move);
    }
  }
};