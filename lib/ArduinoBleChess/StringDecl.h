#pragma once

#if defined(ESP32)
#include <string>
#else
#include <Arduino.h>
#endif

#if defined(ESP32)
using StringDecl = std::string;
#else
using StringDecl = String;
#endif

#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#endif

inline bool startsWith(const StringDecl& str, const StringDecl& start)
{
#if defined(ESP32)
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
#else
    return str.startsWith(start);
#endif
}

inline StringDecl substring(const StringDecl& str, unsigned int beginIndex)
{
#if defined(ESP32)
    return str.substr(beginIndex);
#else
    return str.substring(beginIndex);
#endif
}

inline StringDecl substring(const StringDecl& str, unsigned int beginIndex, unsigned int endIndex)
{
#if defined(ESP32)
    return str.substr(beginIndex, endIndex);
#else
    return str.substring(beginIndex, endIndex);
#endif
}

inline int indexOf(const StringDecl& str, char match)
{
#if defined(ESP32)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}

inline int indexOf(const StringDecl& str, const StringDecl& match)
{
#if defined(ESP32)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}