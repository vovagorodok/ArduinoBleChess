#include <Arduino.h>
#include <ArduinoBleChess.h>

class MyBleChessDevice : public BleChessDevice
{
  void onNewGame(const BleString& fen) {
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
  void onMove(const BleString& mv) {
    Serial.print("moved from phone: ");
    Serial.println(mv.c_str());
  }
  void onDeviceMoveRejected(const BleString& mv) {
    Serial.print("move rejected: ");
    Serial.println(mv.c_str());
  }
  void onDeviceMovePromoted(const BleString& mv) {
    Serial.print("promoted on phone screen: ");
    Serial.println(mv.c_str());
  }
};
MyBleChessDevice device{};

void setup() {
  Serial.begin(19200);
  while (!Serial);

  ArduinoBleChess.begin("Arduino Ble Chess", device);
}

void loop() {
  delay(2000);
}