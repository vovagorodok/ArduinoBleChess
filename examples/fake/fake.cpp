#ifndef ARDUINO
#include <ArduinoBleChess.h>

BleChessPeripheral peripheral{};

int main() {
  ArduinoBleChess.begin("Arduino Ble Chess", peripheral);
  return 0;
}
#endif