//
// Created by Monika on 22.09.2021.
//

#ifndef GAMEENGINE_STRINGFORMAT_H
#define GAMEENGINE_STRINGFORMAT_H

#include <Utils/Debug.h>
#include <Utils/Math/Mathematics.h>

namespace SR_UTILS_NS {
    template<typename T> std::string ToString(const T& value) {
        if constexpr (Math::IsNumber<T>() || Math::IsLogical<T>()) {
            return std::to_string(value);
        }
        else if constexpr (Math::IsString<T>()) {
            return value;
        }
        else if constexpr (false) {
            SR_STATIC_ASSERT("Unsupported type!");
        }
    }

    /// Warning: unsafe
    template<typename T> T LexicalCast(const std::string& str) {
        try {
            if constexpr (std::is_same<T, bool>()) {
                const char c = str.front();
                return c == 't' || c == 'T' || c == '1' || c == 'y' || c == 'Y' || c == '1';
            }
            else if constexpr (std::is_same<T, int8_t>()) {
                return static_cast<int8_t>(str.front());
            }
            else if constexpr (std::is_same<T, uint8_t>()) {
                return static_cast<uint8_t>(str.front());
            }
            else if constexpr (std::is_same<T, int16_t>()) {
                return std::stoi(str);
            }
            else if constexpr (std::is_same<T, uint16_t>()) {
                return static_cast<uint16_t>(std::stoi(str));
            }
            else if constexpr (std::is_same<T, int32_t>()) {
                return std::stoi(str);
            }
            else if constexpr (std::is_same<T, int64_t>()) {
                return std::stoll(str);
            }
            else  if constexpr (std::is_same<T, uint32_t>()) {
                return static_cast<uint32_t>(std::stoi(str));
            }
            else if constexpr (std::is_same<T, uint64_t>()) {
                return static_cast<uint64_t>(std::stoll(str));
            }
            else if constexpr (std::is_same<T, float_t>()) {
                return std::stof(str);
            }
            else if constexpr (std::is_same<T, double_t>() || std::is_same<T, Math::Unit>()) {
                return std::stod(str);
            }
            else
                SR_STATIC_ASSERT("Unsupported type!");
        }
        catch (...) {
            SRAssert(false);
            return T();
        }
    }

    static std::string Format(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        std::vector<char> v(1024);
        while (true) {
            va_list args2;
            va_copy(args2, args);
            int res = vsnprintf(v.data(), v.size(), fmt, args2);
            if ((res >= 0) && (res < static_cast<int>(v.size()))) {
                va_end(args);
                va_end(args2);
                return std::string(v.data());
            }
            size_t size;
            if (res < 0)
                size = v.size() * 2;
            else
                size = static_cast<size_t>(res) + 1;
            v.clear();
            v.resize(size);
            va_end(args2);
        }
    }
}

#define SR_FORMAT(fmt, ...) SR_UTILS_NS::Format(fmt, __VA_ARGS__)
#define SR_FORMAT_C(fmt, ...) SR_UTILS_NS::Format(fmt, __VA_ARGS__).c_str()

#endif //GAMEENGINE_STRINGFORMAT_H
