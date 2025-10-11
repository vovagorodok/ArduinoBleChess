#pragma once

#if defined(BLE_CHESS_LIB_ARDUINO_BLE) || defined(BLE_CHESS_BLE_LIB_ARDUINO_BLE)
    #include <ArduinoBLE.h>
    #ifndef BLE_CHESS_BLE_LIB_ARDUINO_BLE
        #define BLE_CHESS_BLE_LIB_ARDUINO_BLE
    #endif
    #ifndef BLE_CHESS_LIB_ARDUINO_BLE
        #define BLE_CHESS_LIB_ARDUINO_BLE
    #endif
    #define BLE_CHESS_BLE_LIB_PREDEFINED
#elif defined(BLE_CHESS_LIB_NIM_BLE_ARDUINO) || defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO) || \
      defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1) || defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V2)
    #include <NimBLEDevice.h>
    #ifndef BLE_CHESS_LIB_NIM_BLE_ARDUINO
        #define BLE_CHESS_LIB_NIM_BLE_ARDUINO
    #endif
    #ifndef BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
        #define BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
    #endif
    #if !defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1) && !defined(BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V2)
        #define BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V2
    #endif
    #define BLE_CHESS_BLE_LIB_PREDEFINED
#elif defined(BLE_CHESS_LIB_ESP32) || defined(BLE_CHESS_BLE_LIB_ESP32)
    #include <BLEDevice.h>
    #ifndef BLE_CHESS_LIB_ESP32
        #define BLE_CHESS_LIB_ESP32
    #endif
    #ifndef BLE_CHESS_BLE_LIB_ESP32
        #define BLE_CHESS_BLE_LIB_ESP32
    #endif
    #define BLE_CHESS_BLE_LIB_PREDEFINED
#endif

#if !defined(PLATFORMIO) && !defined(BLE_CHESS_BLE_LIB_PREDEFINED)
    #include <ArduinoBLE.h>
    #define BLE_CHESS_BLE_LIB_ARDUINO_BLE
    #define BLE_CHESS_LIB_ARDUINO_BLE
    #define BLE_CHESS_BLE_LIB_PREDEFINED
#endif

#ifndef BLE_CHESS_BLE_LIB_PREDEFINED
    #if __has_include("ArduinoBLE.h")
        #include <ArduinoBLE.h>
        #define BLE_CHESS_BLE_LIB_ARDUINO_BLE
        #define BLE_CHESS_LIB_ARDUINO_BLE
    #elif __has_include("NimBLEDevice.h")
        #include <NimBLEDevice.h>
        #define BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO
        #define BLE_CHESS_LIB_NIM_BLE_ARDUINO
    #if !defined(CONFIG_NIMBLE_MAX_CONNECTIONS) && \
        !defined(CONFIG_NIMBLE_CPP_DEBUG_ASSERT_ENABLED)
        #define BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V1
    #else
        #define BLE_CHESS_BLE_LIB_NIM_BLE_ARDUINO_V2
    #endif
    #elif defined(ARDUINO_ARCH_ESP32)
        #include <BLEDevice.h>
        #define BLE_CHESS_BLE_LIB_ESP32
        #define BLE_CHESS_LIB_ESP32
    #else
        #error "Unsupported BLE library. Consider ArduinoBLE or NimBLE-Arduino."
    #endif
#endif