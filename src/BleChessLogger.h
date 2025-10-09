#pragma once
#include <Arduino.h>

#ifdef BLE_CHESS_LOGS
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
        #define BLE_CHESS_PRINTF Serial.printf
    #else
        #define BLE_CHESS_PRINTF printf
    #endif

    #define BLE_CHESS_LOG(tag, fmt, ...) \
        BLE_CHESS_PRINTF("DBG: BleChess: " tag ": " fmt "\n", ##__VA_ARGS__)
#else
    #define BLE_CHESS_LOG(fmt, ...) \
        do {} while (0)
#endif