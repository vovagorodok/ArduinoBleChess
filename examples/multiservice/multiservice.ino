#include <ArduinoBleChess.h>
#include <ArduinoBleChessMultiservice.h>
#include "../MyPeripheral.h"

// max name size with 128 bit uuid is 11
#define NAME "MultiSrv"
#define LED_SERVICE_UUID "19B10000-E8F2-537E-4F6C-D104768A1214"
#define LED_CHARACTERISTIC_UUID "19B10001-E8F2-537E-4F6C-D104768A1214"

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

#ifdef BLE_CHESS_LIB_ARDUINO_BLE
BLEService ledService(LED_SERVICE_UUID);
BLEBooleanCharacteristic ledCharacteristic(LED_CHARACTERISTIC_UUID, BLERead | BLEWrite);
void onWrite(BLEDevice central, BLECharacteristic characteristic) {
  digitalWrite(LED_BUILTIN, ledCharacteristic.value());
}
#endif

#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
class LedCharacteristicCallbacks: public BLECharacteristicCallbacks {
public:
#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
  void onWrite(BLECharacteristic* characteristic) override {
#else
  void onWrite(BLECharacteristic* characteristic, BLEConnInfo& connInfo) override {
#endif
    digitalWrite(LED_BUILTIN, characteristic->getValue<bool>());
  }
};
LedCharacteristicCallbacks ledCallbacks;
#endif

MyPeripheral peripheral{};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  initBle(NAME);

#ifdef BLE_CHESS_LIB_ARDUINO_BLE
  initBle(NAME);
  ledService.addCharacteristic(ledCharacteristic);
  BLE.addService(ledService);
  ledCharacteristic.setEventHandler(BLEWritten, onWrite);
  ledCharacteristic.writeValue(0);
  ArduinoBleChess.begin(peripheral);
  advertiseBle(NAME, BLE_CHESS_SERVICE_UUID, LED_SERVICE_UUID);
#endif

#ifdef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
  auto server = initBle(NAME);
  auto ledService = server->createService(LED_SERVICE_UUID);
  auto ledCharacteristic = ledService->createCharacteristic(
    LED_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
  );
  ledCharacteristic->setValue(false);
  ledCharacteristic->setCallbacks(&ledCallbacks);
  ledService->start();
  ArduinoBleChess.begin(server, peripheral);
  advertiseBle(server, NAME, BLE_CHESS_SERVICE_UUID, LED_SERVICE_UUID);
#endif
}

void loop() {
#ifdef BLE_CHESS_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  peripheral.checkPeripheralMove();
}