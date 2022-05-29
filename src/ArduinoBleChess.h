#pragma once

#include "Defines.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include "ArduinoBleChessNimBle.h"
#else
#include "ArduinoBleChessAtmel.h"
#endif