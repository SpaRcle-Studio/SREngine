//
// Created by Monika on 22.09.2021.
//

#ifndef SR_ENGINE_UTILS_STRING_FORMAT_H
#define SR_ENGINE_UTILS_STRING_FORMAT_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Common/Breakpoint.h>

#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/color.h>

namespace SR_UTILS_NS {
    template<typename T> T LexicalCast(const std::string& str) {
        try {
            if constexpr (std::is_same<T, bool>()) {
                const char c = str.front();
                return c == 't' || c == 'T' || c == 'y' || c == 'Y' || c == '1'; /// NOLINT
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
            else if constexpr (std::is_same<T, uint32_t>()) {
                return static_cast<uint32_t>(std::stoi(str));
            }
            else if constexpr (std::is_same<T, uint64_t>()) {
                return static_cast<uint64_t>(std::stoll(str));
            }
            else if constexpr (std::is_same<T, float_t>() || std::is_same<T, float>()) {
                return std::stof(str);
            }
            else if constexpr (std::is_same<T, double_t>() || std::is_same<T, double>() || std::is_same<T, Math::Unit>()) {
                return std::stod(str);
            }
            else {
                std::cerr << "LexicalCast: unsupported type!" << std::endl;
                SR_MAKE_BREAKPOINT;
                return T();
            }
        }
        catch (...) {
            std::cerr << "LexicalCast: failed to cast!" << std::endl;
            SR_MAKE_BREAKPOINT;
            return T();
        }
    }

    template <class... Args> std::string Format(const char* fmt, Args&&... args) {
        try {
            return fmt::format(fmt::runtime(fmt), args...);
        }
        catch (std::exception& exception) {
            std::cerr << "Format: an exception has been occurred! Exception: " << exception.what() << std::endl;
            SR_MAKE_BREAKPOINT;
            return std::string(); /// NOLINT
        }
    }

    template <class... Args> std::string SPrintF(const char* fmt, Args&&... args) {
        try {
            return fmt::sprintf(fmt, args...);
        }
        catch (std::exception& exception) {
            std::cerr << "SPrintFFormat: an exception has been occurred! Exception: " << exception.what() << std::endl;
            SR_MAKE_BREAKPOINT;
            return std::string(); /// NOLINT
        }
    }

    template <class... Args> std::string Format(const std::string& fmt, Args&&... args) {
        return Format<Args...>(fmt.c_str(), args...);
    }
}

#define SR_FORMAT(...) SR_UTILS_NS::Format(__VA_ARGS__)
#define SR_SPRINTF(...) SR_UTILS_NS::SPrintF(__VA_ARGS__)
#define SR_FORMAT_C(...) SR_UTILS_NS::Format(__VA_ARGS__).c_str()

#endif //SR_ENGINE_UTILS_STRING_FORMAT_H
