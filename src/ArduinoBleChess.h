#pragma once

#if defined(USE_NIM_BLE_ARDUINO_LIB)
#include "ArduinoBleChessNimBle.h"
#else
#include "ArduinoBleChessCommon.h"
#ifndef BLE_PULL_REQUIRED
    #define BLE_PULL_REQUIRED
#endif
#endif