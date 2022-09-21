#include <Arduino.h>
#include <ArduinoBleChess.h>
#include <BleChessMultiservice.h>
#include "../MyPeripheral.h"

// max name size with 128 bit uuid is 11
#define NAME "MultiSrv"
#define MY_SECOND_SERVICE_UUID "<any uuid>"

MyPeripheral peripheral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  initBle(NAME);

  // add your ble services here

  if (!ArduinoBleChess.begin(peripheral))
    Serial.println("ble initialization error");
  advertizeBle(NAME, MY_SECOND_SERVICE_UUID);
}

void loop() {
#if defined(BLE_PULL_REQUIRED)
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}