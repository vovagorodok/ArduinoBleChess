#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "MyOptionsPeripheral.h"

MyOptionsPeripheral peripheral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleChess.begin("Arduino Ble Chess", peripheral);
}

void loop() {
#ifdef BLE_CHESS_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  peripheral.checkPeripheralInput();
}