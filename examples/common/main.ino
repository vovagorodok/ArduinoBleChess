#include <Arduino.h>
#include <ArduinoBleChess.h>

class MyBleChessDevice : public BleChessDevice
{
public:
  void onNewGame(const BleString& fen) {
    Serial.print("new game: ");
    Serial.println(fen.c_str());
  }
  void askDeviceMakeMove() {
    Serial.println("please move: ");
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
  void checkDviceMove() {
    if (Serial.available()) {
      BleString move;
      while (Serial.available())
        move += Serial.read();
      deviceMove(move);
    }
  }
};
MyBleChessDevice device{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!ArduinoBleChess.begin("Arduino Ble Chess", device))
    Serial.println("ble initialization error");
}

void loop() {
#if defined(BLE_PULL_REQUIRED)
  BLE.poll();
#endif
  device.checkDviceMove();
}