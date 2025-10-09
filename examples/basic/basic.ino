#include <Arduino.h>
#include <ArduinoBleChess.h>
#include "../MyPeripheral.h"

#ifdef BLE_OTA_LOGS
#ifndef ARDUINO_ARCH_ESP32
extern "C" {
int _write(int fd, char *ptr, int len) {
  (void) fd;
  return Serial.write(ptr, len);
}
}
#endif
#endif

MyPeripheral peripheral{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleChess.begin("Arduino Ble Chess", peripheral);
}

void loop() {
#ifdef BLE_CHESS_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}