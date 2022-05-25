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

bool startsWith(const StringDecl& str, const StringDecl& start);
StringDecl substring(const StringDecl& str, unsigned int beginIndex);
StringDecl substring(const StringDecl& str, unsigned int beginIndex, unsigned int endIndex);
int indexOf(const StringDecl& str, char match);
int indexOf(const StringDecl& str, const StringDecl& match);