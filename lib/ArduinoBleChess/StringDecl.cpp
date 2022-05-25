#include "StringDecl.h"

#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#endif

bool startsWith(const StringDecl& str, const StringDecl& start)
{
#if defined(ESP32)
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
#else
    return str.startsWith(start);
#endif
}

StringDecl substring(const StringDecl& str, unsigned int beginIndex)
{
#if defined(ESP32)
    return str.substr(beginIndex);
#else
    return str.substring(beginIndex);
#endif
}

StringDecl substring(const StringDecl& str, unsigned int beginIndex, unsigned int endIndex)
{
#if defined(ESP32)
    return str.substr(beginIndex, endIndex);
#else
    return str.substring(beginIndex, endIndex);
#endif
}

int indexOf(const StringDecl& str, char match)
{
#if defined(ESP32)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}

int indexOf(const StringDecl& str, const StringDecl& match)
{
#if defined(ESP32)
    return str.find(match);
#else
    return str.indexOf(match);
#endif
}