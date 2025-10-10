#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "MyOfflineCentral.h"
#include "../MyPeripheral.h"

MyPeripheral peripheral{};
MyOfflineCentral offlineCentral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleChess.begin("Arduino Ble Chess", peripheral, offlineCentral);
  offlineCentral.begin();
}

void loop() {
#ifdef BLE_CHESS_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}