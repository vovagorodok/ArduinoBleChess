#include <Arduino.h>
#include <ArduinoBleChess.h>

class MyChessDevice : public ChessDevice
{
  void onNewGame(const StringDecl& fen) {
    Serial.print("new game: ");
    Serial.println(fen.c_str());
  }
  void askDeviceMakeMove() {
    Serial.println("please move: ");
    // deviceMove("a1a2");
  }
  void askDeviceStopMove() {
    Serial.println("stop move: ");
  }
  void onMove(const StringDecl& mv) {
    Serial.print("moved from phone: ");
    Serial.println(mv.c_str());
  }
  void onDeviceMoveRejected(const StringDecl& mv) {
    Serial.print("move rejected: ");
    Serial.println(mv.c_str());
  }
};
MyChessDevice device{};

void setup() {
  Serial.begin(19200);
  while (!Serial);

  ArduinoBleChess.begin("Arduino Ble Chess", device);
}

void loop() {
  delay(2000);
}