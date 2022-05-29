#pragma once

#if defined(ESP32)
#define NIM_BLE_ARDUINO_LIB
#else
#define ARDUINO_BLE_LIB
#define BLE_PULL_REQUIRED
#endif