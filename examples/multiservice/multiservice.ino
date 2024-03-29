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

#ifndef USE_NIM_BLE_ARDUINO_LIB
  static BLEService service(MY_SECOND_SERVICE_UUID);
  BLE.addService(service);
#else
  auto* server = BLEDevice::createServer();
  auto* service = server->createService(MY_SECOND_SERVICE_UUID);
  service->start();
#endif

  if (!ArduinoBleChess.begin(peripheral))
    Serial.println("ble initialization error");
  advertiseBle(NAME, MY_SECOND_SERVICE_UUID);
}

void loop() {
#ifndef USE_NIM_BLE_ARDUINO_LIB
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}