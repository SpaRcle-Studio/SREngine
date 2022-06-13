//
// Created by Monika on 01.10.2021.
//

#ifndef GAMEENGINE_ENUMERATIONS_H
#define GAMEENGINE_ENUMERATIONS_H

#include <Utils/StringUtils.h>

#define SR_ENUM_TO_STRING(enumName)                                                              \
    static std::string Enum##enumName##ToString(enumName value) {                                \
        const std::lock_guard<std::mutex> lock(SR_CODEGEN_ENUM::g_##enumName##_mutex);           \
        auto& _map = SR_CODEGEN_ENUM::codegen_get_##enumName##_mapValue();                       \
        if (_map.empty())                                                                        \
            SR_CODEGEN_ENUM::procedure##enumName##_enum_parse();                                 \
        if (auto v = _map.find(value); v != _map.end())                                          \
            return _map[value];                                                                  \
        else                                                                                     \
            return std::string();                                                                \
    }                                                                                            \

#define SR_ENUM_FROM_STRING(enumName)                                                            \
    static enumName StringToEnum##enumName(const std::string& value) {                           \
        const std::lock_guard<std::mutex> lock(SR_CODEGEN_ENUM::g_##enumName##_mutex);           \
        auto& _map = SR_CODEGEN_ENUM::codegen_get_##enumName##_mapKey();                         \
        if (_map.empty())                                                                        \
            SR_CODEGEN_ENUM::procedure##enumName##_enum_parse();                                 \
        if (auto v = _map.find(value); v != _map.end())                                          \
            return _map[value];                                                                  \
        else                                                                                     \
            return (enumName)0;                                                                  \
    }

#define SR_ENUM_CODEGEN(enumName, ...)                                                           \
    namespace SR_CODEGEN_ENUM {                                                                  \
        typedef std::unordered_map<std::string, enumName> enumName##_mapKey;                     \
        typedef std::unordered_map<enumName, std::string> enumName##_mapValue;                   \
        static std::mutex g_##enumName##_mutex;                                                  \
        static enumName##_mapKey& codegen_get_##enumName##_mapKey() {                            \
            static enumName##_mapKey _map = {};                                                  \
            return _map;                                                                         \
        }                                                                                        \
        static enumName##_mapValue& codegen_get_##enumName##_mapValue() {                        \
            static enumName##_mapValue _map = {};                                                \
            return _map;                                                                         \
        }                                                                                        \
        static void procedure##enumName##_enum_parse() {                                         \
            auto tokens = Framework::Helper::StringUtils::Split(#__VA_ARGS__, ",");              \
            int64_t last = 0;                                                                    \
            auto& _mapKey = codegen_get_##enumName##_mapKey();                                   \
            auto& _mapValue = codegen_get_##enumName##_mapValue();                               \
            for (std::string& token : tokens) {                                                  \
                token = Framework::Helper::StringUtils::RemoveCharsFromString(token, " ");       \
                if (token.find('=') != std::string::npos) {                                      \
                    auto[name, value] = Framework::Helper::StringUtils::SplitTwo(token, "=");    \
                    last = std::stoi(value);                                                     \
                    token = name;                                                                \
                }                                                                                \
                if (auto v = _mapValue.find((enumName)last); v != _mapValue.end()) {             \
                    SR_WARN(std::string("SR_CODEGEN_ENUM::enum_parse() : "           \
                        "conflict enums! \n\tEnum name: ").append(#enumName)                     \
                        .append("\n\tValues: ").append(v->second).append(" and ").append(token)); \
                    continue;                                                                    \
                }                                                                                \
                _mapKey[token] = (enumName)last;                                                 \
                _mapValue[(enumName)last++] = token;                                             \
            }                                                                                    \
        }                                                                                        \
    }                                                                                            \
    SR_ENUM_TO_STRING(enumName)                                                                  \
    SR_ENUM_FROM_STRING(enumName)                                                                \


#define SR_ENUM_CLASS_T(enumName, type, ...)                                                     \
    enum class enumName : type {                                                                 \
        __VA_ARGS__                                                                              \
    };                                                                                           \
    SR_ENUM_CODEGEN(enumName, __VA_ARGS__)                                                       \

#define SR_ENUM_T(enumName, type, ...)                                                           \
    enum enumName : type {                                                                       \
        __VA_ARGS__                                                                              \
    };                                                                                           \
    SR_ENUM_CODEGEN(enumName, __VA_ARGS__)                                                       \

#define SR_ENUM_CLASS(enumName, ...) SR_ENUM_CLASS_T(enumName, int32_t, __VA_ARGS__)
#define SR_ENUM(enumName, ...) SR_ENUM_T(enumName, int32_t, __VA_ARGS__)

/// --------------------------------------------------------------------------------------------------------------------

namespace SR_UTILS_NS {
    SR_ENUM_CLASS_T(BoolExt, int8_t,
          None  = -1,
          False = 0,
          True  = 1
    );
}

#endif //GAMEENGINE_ENUMERATIONS_H
