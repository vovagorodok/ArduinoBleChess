#pragma once
#include <ArduinoBleChess.h>

class MyPeripheral : public BleChessPeripheral
{
public:
  void handleCentralBegin(BleChessStringView fen) override {
    Serial.print("begin: ");
    Serial.println(fen.data());
    sendPeripheralSync(BleChessString(fen));
  }
  void handleCentralMove(BleChessStringView mv) override {
    Serial.print("move: ");
    Serial.println(mv.data());
  }
  void handlePeripheralMoveAck(bool ack) override {
    Serial.print("move ");
    Serial.println(ack ? "accepted" : "rejected");
  }
  void handlePeripheralMovePromoted(BleChessStringView prom) override {
    Serial.print("promote: ");
    Serial.println(prom.data());
  }
  void handleCentralEnd(BleChessStringView reason) override {
    Serial.print("end: ");
    Serial.println(reason.data());
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