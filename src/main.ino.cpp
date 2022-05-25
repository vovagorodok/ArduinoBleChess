# 1 "/tmp/tmpxeksvhy5"
#include <Arduino.h>
# 1 "/home/vova/projects/ArduinoBleChess/src/main.ino"
#include <Arduino.h>
#include <ArduinoBleChess.h>

class MyChessDevice : public ChessDevice
{
  void onNewGame(const StringDecl& fen) {
    Serial.write("new game: ");
    Serial.write(fen.c_str());
    Serial.write("\n");
  }
  void askDeviceMakeMove() {
    Serial.write("please move: \n");

  }
  void askDeviceStopMove() {
    Serial.write("stop move: \n");
  }
  void onMove(const StringDecl& mv) {
    Serial.write("moved from phone: ");
    Serial.write(mv.c_str());
    Serial.write("\n");
  }
  void onDeviceMoveRejected(const StringDecl& mv) {
    Serial.write("move rejected: ");
    Serial.write(mv.c_str());
    Serial.write("\n");
  }
};
MyChessDevice device{};
void setup();
void loop();
#line 31 "/home/vova/projects/ArduinoBleChess/src/main.ino"
void setup() {
  Serial.begin(19200);
  ArduinoBleChess.begin("ArduinoBleChess", device);
}

void loop() {
  delay(2000);
}