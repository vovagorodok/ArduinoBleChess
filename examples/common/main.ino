#include <Arduino.h>
#include <ArduinoBleChess.h>

class MyBleChessDevice : public BleChessDevice
{
public:
  void onNewGame(const Ble::String& fen) {
    Serial.print("new game: ");
    Serial.println(fen.c_str());
  }
  void askDeviceMakeMove() {
    Serial.println("please move: ");
  }
  void askDeviceStopMove() {
    Serial.println("stop move: ");
  }
  void onMove(const Ble::String& mv) {
    Serial.print("moved from phone: ");
    Serial.println(mv.c_str());
  }
  void onDeviceMoveRejected(const Ble::String& mv) {
    Serial.print("move rejected: ");
    Serial.println(mv.c_str());
  }
  void onDeviceMovePromoted(const Ble::String& mv) {
    Serial.print("promoted on phone screen: ");
    Serial.println(mv.c_str());
  }
  void checkDviceMove() {
    if (Serial.available()) {
      Ble::String move;
      while (Serial.available())
        move += Serial.readString();
      Serial.print("my move input: ");
      Serial.println(move);
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
