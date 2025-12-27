#pragma once
#include "BleChessDefines.h"
#include "BleChessDefinesArduino.h"
#include <string>
#include <ostream>

#if __cplusplus >= 201703L
#define BLE_CHESS_CONSTEXPR constexpr
#else
#define BLE_CHESS_CONSTEXPR inline
#endif

class BleChessStringViewImpl {
public:
    constexpr BleChessStringViewImpl():
        _data(), _size() {}
    constexpr BleChessStringViewImpl(const BleChessStringViewImpl& sw):
        _data(sw._data), _size(sw._size) {}
    constexpr BleChessStringViewImpl(const char* str, size_t size):
        _data(str), _size(size) {}
    BLE_CHESS_CONSTEXPR BleChessStringViewImpl(const char* str):
        _data(str), _size(_strlen(str)) {}
#if __cpp_lib_string_view
    constexpr BleChessStringViewImpl(std::string_view sv):
        _data(sv.data()), _size(sv.size()) {}
#endif
    inline BleChessStringViewImpl(const std::string& str):
        _data(str.data()), _size(str.size()) {}
#ifdef ARDUINO
    inline BleChessStringViewImpl(const String& str):
        _data(str.c_str()), _size(str.length()) {}
#endif

#if __cpp_lib_string_view
    constexpr operator std::string_view() const {
        return std::string_view(_data, _size);
    }
#endif
    inline operator std::string() const {
        return std::string(_data, _size);
    }
#ifdef ARDUINO
    inline operator String() const {
        return String(_data, _size);
    }
#endif

    constexpr const char* data() const { return _data; }
    constexpr size_t size() const { return _size; }
    constexpr bool empty() const { return !_size; }

    constexpr BleChessStringViewImpl substr(size_t pos) const {
        return (pos > _size) ?
            BleChessStringViewImpl() :
            BleChessStringViewImpl(_data + pos, _size - pos);
    }
    constexpr BleChessStringViewImpl substr(size_t pos, size_t count) const {
        return (pos > _size) ?
            BleChessStringViewImpl() :
            BleChessStringViewImpl(_data + pos, _remaining_size(pos, count));
    }

    BLE_CHESS_CONSTEXPR bool starts_with(BleChessStringViewImpl sw) const {
        return _size >= sw._size and _compare(_data, sw._data, sw._size);
    }
    BLE_CHESS_CONSTEXPR bool ends_with(BleChessStringViewImpl sw) const {
        return _size >= sw._size and _compare(_data + _size - sw._size, sw._data, sw._size);
    }
    BLE_CHESS_CONSTEXPR bool operator==(BleChessStringViewImpl sw) const {
        return _size == sw._size and _compare(_data, sw._data, sw._size);
    }
    BLE_CHESS_CONSTEXPR bool operator==(const char* str) const {
        return operator==(BleChessStringViewImpl(str));
    }
    inline bool operator==(const std::string& str) const {
        return operator==(BleChessStringViewImpl(str));
    }
#ifdef ARDUINO
    inline bool operator==(const String& str) const {
        return operator==(BleChessStringViewImpl(str));
    }
#endif

    BLE_CHESS_CONSTEXPR size_t find(char ch) const {
        auto found = _find(_data, _size, ch);
        return found ? static_cast<size_t>(found - _data) : npos;
    }
    BLE_CHESS_CONSTEXPR size_t find(char ch, size_t pos) const {
        if (pos >= _size)
            return npos;
        auto found = _find(_data + pos, _size - pos, ch);
        return found ? static_cast<size_t>(found - _data) : npos;
    }
    BLE_CHESS_CONSTEXPR size_t find(BleChessStringViewImpl sv) const {
        if (sv._size == 0)
            return npos;
        if (sv._size > _size)
            return npos;
        for (size_t pos = 0; pos <= _size - sv._size; pos++) {
            if (_compare(_data + pos, sv._data, sv._size))
                return pos;
        }
        return npos;
    }

    static constexpr size_t npos = static_cast<size_t>(-1);

private:
    static BLE_CHESS_CONSTEXPR size_t _strlen(const char* str) {
        return str ? std::char_traits<char>::length(str): 0;
    }
    static BLE_CHESS_CONSTEXPR bool _compare(const char* str1, const char* str2, size_t count) {
        return std::char_traits<char>::compare(str1, str2, count) == 0;
    }
    static BLE_CHESS_CONSTEXPR const char* _find(const char* str, size_t count, char ch) {
        return std::char_traits<char>::find(str, count, ch);
    }
    constexpr size_t _remaining_size(size_t pos, size_t count) const {
        return count == npos or pos + count > _size ? _size - pos : count;
    }

    const char* _data;
    size_t _size;
};

inline std::ostream& operator<<(std::ostream& os, BleChessStringViewImpl sv) {
    return os.write(sv.data(), sv.size());
}

#if defined(BLE_CHESS_BLE_LIB_ARDUINO_BLE) || !defined(__cpp_lib_string_view) || !defined(__cpp_lib_starts_ends_with)
using BleChessStringViewInternal = BleChessStringViewImpl;
#else
using BleChessStringViewInternal = std::string_view;
#endif

#if defined(BLE_CHESS_BLE_LIB_ARDUINO_BLE) || !defined(__cpp_lib_string_view)
using BleChessStringView = BleChessStringViewImpl;
#else
using BleChessStringView = std::string_view;
#endif

#ifdef BLE_CHESS_BLE_LIB_ARDUINO_BLE
using BleChessString = String;
#else
using BleChessString = std::string;
#endif