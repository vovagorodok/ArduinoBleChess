#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "MyOfflineCentral.h"
#include "../MyPeripheral.h"

MyPeripheral peripheral{};
MyOfflineCentral offlineCentral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!ArduinoBleChess.begin("Arduino Ble Chess", peripheral, offlineCentral))
    Serial.println("ble initialization error");

  offlineCentral.begin();
}

void loop() {
#ifndef USE_NIM_BLE_ARDUINO_LIB
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}