#pragma once
#include "BleChessDefines.h"
#if defined(BLE_CHESS_BLE_LIB_ARDUINO_BLE)
#include "BleChessLibArduinoBle.h"
#elif defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO)
#include "BleChessLibNimBleArduino.h"
#elif defined(BLE_CHESS_BLE_LIB_ESP32)
#include "BleChessLibESP32.h"
#else
#error "Unsupported BLE library."
#endif