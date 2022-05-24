#include <Arduino.h>
#include <ArduinoBleChess.h>
#include <iostream>

class MyChessDevice : public ChessDevice
{
  void onNewGame(const std::string& fen) {
    std::cout << "new game: " << fen << std::endl;
  };
  void askDeviceMakeMove() {
    std::cout << "please move:" << std::endl;
  };
  void askDeviceStopMove() {
    std::cout << "stop move: " << std::endl;
  };
  void onMove(const std::string& mv) {
    std::cout << "moved from phone: " << mv << std::endl;
  };
  void onDeviceMoveRejected(const std::string& mv) {
    std::cout << "move rejected: " << mv << std::endl;
  };
};
MyChessDevice device{};

void setup() {
  ArduinoBleChess.begin("ArduinoBleChess", device);
}

void loop() {
  delay(2000);
}