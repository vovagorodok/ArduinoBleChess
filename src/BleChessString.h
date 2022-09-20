#pragma once

#include "BleChessDefines.h"
#if defined(NIM_BLE_ARDUINO_LIB)
#include <string>
#else
#include <Arduino.h>
#endif

namespace BleChess
{
#if defined(NIM_BLE_ARDUINO_LIB)
using String = std::string;
#else
using String = String;
#endif
}

#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#endif

inline bool startsWith(const BleChess::String& str, const BleChess::String& start)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
#else
    return str.startsWith(start);
#endif
}

inline BleChess::String substring(const BleChess::String& str, unsigned int beginIndex)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex);
#else
    return str.substring(beginIndex);
#endif
}

inline BleChess::String substring(const BleChess::String& str, unsigned int beginIndex, unsigned int endIndex)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.substr(beginIndex, endIndex);
#else
    return str.substring(beginIndex, endIndex);
#endif
}

inline int indexOf(const BleChess::String& str, char match)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}

inline int indexOf(const BleChess::String& str, const BleChess::String& match)
{
#if defined(NIM_BLE_ARDUINO_LIB)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}