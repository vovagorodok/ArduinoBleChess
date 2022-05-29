#pragma once

#include "Defines.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include <string>
#else
#include <Arduino.h>
#endif

#if defined(NIM_BLE_ARDUINO_LIB)
using BleString = std::string;
#else
using BleString = String;
#endif

#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#endif

inline bool startsWith(const BleString& str, const BleString& start)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
#else
    return str.startsWith(start);
#endif
}

inline BleString substring(const BleString& str, unsigned int beginIndex)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex);
#else
    return str.substring(beginIndex);
#endif
}

inline BleString substring(const BleString& str, unsigned int beginIndex, unsigned int endIndex)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex, endIndex);
#else
    return str.substring(beginIndex, endIndex);
#endif
}

inline int indexOf(const BleString& str, char match)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}

inline int indexOf(const BleString& str, const BleString& match)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}