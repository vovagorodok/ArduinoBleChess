#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "../MyPeripheral.h"

MyPeripheral device{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  BLEDevice::init("Arduino Ble Chess");
  auto* server = BLEDevice::createServer();

  // add your ble services here

  if (!ArduinoBleChess.begin("Arduino Ble Chess", device))
    Serial.println("ble initialization error");
  server->startAdvertising();
}

void loop() {
  device.checkPeripheralMove();
}