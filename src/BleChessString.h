#pragma once

#if defined(USE_NIM_BLE_ARDUINO_LIB)
#include <string>
#else
#include <Arduino.h>
#endif

#if defined(USE_NIM_BLE_ARDUINO_LIB)
using BleChessString = std::string;
#else
using BleChessString = String;
#endif

#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#endif

inline bool startsWith(const BleChessString& str, const BleChessString& start)
{
#if defined(USE_NIM_BLE_ARDUINO_LIB)
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
#else
    return str.startsWith(start);
#endif
}

inline BleChessString substring(const BleChessString& str, unsigned int beginIndex)
{
#if defined(USE_NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex);
#else
    return str.substring(beginIndex);
#endif
}

inline BleChessString substring(const BleChessString& str, unsigned int beginIndex, unsigned int endIndex)
{
#if defined(USE_NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex, endIndex);
#else
    return str.substring(beginIndex, endIndex);
#endif
}

inline int indexOf(const BleChessString& str, char match)
{
#if defined(USE_NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}

inline int indexOf(const BleChessString& str, const BleChessString& match)
{
#if defined(USE_NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}