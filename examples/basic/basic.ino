#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "../MyPeripheral.h"

MyPeripheral peripheral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!ArduinoBleChess.begin("Arduino Ble Chess", peripheral))
    Serial.println("ble initialization error");
}

void loop() {
#ifndef USE_NIM_BLE_ARDUINO_LIB
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}