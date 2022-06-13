//
// Created by Monika on 30.03.2022.
//

#ifndef SRENGINE_MARSHALUTILS_H
#define SRENGINE_MARSHALUTILS_H

#include <Utils/StringFormat.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

namespace SR_UTILS_NS {
    enum class MARSHAL_TYPE : uint8_t {
        Node = 0,
        Bool = 1,
        Int8 = 2,
        UInt8 = 3,
        Int16 = 4,
        UInt16 = 5,
        Int32 = 6,
        UInt32 = 7,
        Int64 = 8,
        UInt64 = 9,
        Float = 10,
        Double = 11,
        String = 12,
    };

    namespace MarshalUtils {
        template<typename T> constexpr MARSHAL_TYPE TypeToMarshal() {
            if constexpr (std::is_same<T, bool>()) {
                return MARSHAL_TYPE::Bool;
            }
            else if constexpr (std::is_same<T, int8_t>() || std::is_same<T, char>()) {
                return MARSHAL_TYPE::Int8;
            }
            else if constexpr (std::is_same<T, uint8_t>() || std::is_same<T, unsigned char>()) {
                return MARSHAL_TYPE::UInt8;
            }
            else if constexpr (std::is_same<T, int16_t>() || std::is_same<T, short>()) {
                return MARSHAL_TYPE::Int16;
            }
            else if constexpr (std::is_same<T, uint16_t>() || std::is_same<T, unsigned short>()) {
                return MARSHAL_TYPE::UInt16;
            }
            else if constexpr (std::is_same<T, int32_t>() || std::is_same<T, int>()) {
                return MARSHAL_TYPE::Int32;
            }
            else if constexpr (std::is_same<T, uint32_t>() || std::is_same<T, unsigned int>()) {
                return MARSHAL_TYPE::UInt32;
            }
            else if constexpr (std::is_same<T, int64_t>() || std::is_same<T, long long>()) {
                return MARSHAL_TYPE::Int64;
            }
            else if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, unsigned long long>()) {
                return MARSHAL_TYPE::UInt64;
            }
            else if constexpr (std::is_same<T, float_t>() || std::is_same<T, float>()) {
                return MARSHAL_TYPE::Float;
            }
            else if constexpr (std::is_same<T, double_t>() || std::is_same<T, double>()) {
                return MARSHAL_TYPE::Double;
            }
            else
                return MARSHAL_TYPE::String;
        }

        template<typename T> static void SR_FASTCALL SaveValue(std::stringstream& stream, const T& value) {
            if constexpr (std::is_same<T, Math::FColor>()) {
                stream.write((const char *) &value.r, sizeof(Math::Unit));
                stream.write((const char *) &value.g, sizeof(Math::Unit));
                stream.write((const char *) &value.b, sizeof(Math::Unit));
                stream.write((const char *) &value.a, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::FVector3>()) {
                stream.write((const char *) &value.x, sizeof(Math::Unit));
                stream.write((const char *) &value.y, sizeof(Math::Unit));
                stream.write((const char *) &value.z, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::FVector2>()) {
                stream.write((const char *) &value.x, sizeof(Math::Unit));
                stream.write((const char *) &value.y, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::IVector3>()) {
                stream.write((const char *) &value.x, sizeof(int32_t));
                stream.write((const char *) &value.y, sizeof(int32_t));
                stream.write((const char *) &value.z, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, Math::IVector2>()) {
                stream.write((const char *) &value.x, sizeof(int32_t));
                stream.write((const char *) &value.y, sizeof(int32_t));
            }
            else if constexpr (Math::IsNumber<T>() || Math::IsLogical<T>()) {
                stream.write((const char *) &value, sizeof(T));
            }
            else {
                static_assert(false, "Unsupported type!");
            }
        }

        template<typename Stream, typename T> static T SR_FASTCALL LoadValue(Stream& stream) {
            T value = T();

            if constexpr (std::is_same<T, Math::FColor>()) {
                stream.read((char*)&value.r, sizeof(Math::Unit));
                stream.read((char*)&value.g, sizeof(Math::Unit));
                stream.read((char*)&value.b, sizeof(Math::Unit));
                stream.read((char*)&value.a, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::FVector3>()) {
                stream.read((char*)&value.x, sizeof(Math::Unit));
                stream.read((char*)&value.y, sizeof(Math::Unit));
                stream.read((char*)&value.z, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::FVector2>()) {
                stream.read((char*)&value.x, sizeof(Math::Unit));
                stream.read((char*)&value.y, sizeof(Math::Unit));
            }
            else if constexpr (std::is_same<T, Math::IVector3>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
                stream.read((char*)&value.z, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, Math::IVector2>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
            }
            else if constexpr (Math::IsNumber<T>() || Math::IsLogical<T>()) {
                stream.read((char*)&value, sizeof(T));
            }
            else {
                static_assert(false, "Unsupported type!");
            }

            return value;
        }

        static void SR_FASTCALL SaveShortString(std::stringstream& stream, const std::string& str) {
            const int16_t size = str.size();
            stream.write((const char*)&size, sizeof(int16_t));
            stream.write((const char*)&str[0], size * sizeof(char));
        }

        static void SR_FASTCALL SaveString(std::stringstream& stream, const std::string& str) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));
        }

        template<typename Stream> static std::string SR_FASTCALL LoadShortStr(Stream& stream) {
            std::string str;
            uint16_t size;
            stream.read((char*)&size, sizeof(uint16_t));
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            return str;
        }

        template<typename Stream> static std::string SR_FASTCALL LoadStr(Stream& stream) {
            std::string str;
            size_t size;
            stream.read((char*)&size, sizeof(size_t));
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            return str;
        }

        static void Encode(std::stringstream& stream, const std::string& str, MARSHAL_TYPE type) {
            switch (type) {
                case MARSHAL_TYPE::Bool: SaveValue(stream, LexicalCast<bool>(str)); break;
                case MARSHAL_TYPE::Int8: SaveValue(stream, LexicalCast<int8_t>(str)); break;
                case MARSHAL_TYPE::UInt8: SaveValue(stream, LexicalCast<uint8_t>(str)); break;
                case MARSHAL_TYPE::Int16: SaveValue(stream, LexicalCast<int16_t>(str)); break;
                case MARSHAL_TYPE::UInt16: SaveValue(stream, LexicalCast<uint16_t>(str)); break;
                case MARSHAL_TYPE::Int32: SaveValue(stream, LexicalCast<int32_t>(str)); break;
                case MARSHAL_TYPE::UInt32: SaveValue(stream, LexicalCast<uint32_t>(str)); break;
                case MARSHAL_TYPE::Int64: SaveValue(stream, LexicalCast<int64_t>(str)); break;
                case MARSHAL_TYPE::UInt64: SaveValue(stream, LexicalCast<uint64_t>(str)); break;
                case MARSHAL_TYPE::Float: SaveValue(stream, LexicalCast<float_t>(str)); break;
                case MARSHAL_TYPE::Double: SaveValue(stream, LexicalCast<double_t>(str)); break;
                case MARSHAL_TYPE::String: SaveString(stream, str); break;
                case MARSHAL_TYPE::Node:
                    break;
            }
        }

        static bool IsNumber(const MARSHAL_TYPE& type) {
            switch (type) {
                case MARSHAL_TYPE::Int8:
                case MARSHAL_TYPE::UInt8:
                case MARSHAL_TYPE::Int16:
                case MARSHAL_TYPE::UInt16:
                case MARSHAL_TYPE::Int32:
                case MARSHAL_TYPE::UInt32:
                case MARSHAL_TYPE::Int64:
                case MARSHAL_TYPE::UInt64:
                case MARSHAL_TYPE::Float:
                case MARSHAL_TYPE::Double:
                    return true;
                default:
                    return false;
            }
        }
    }

    enum class MarshalSaveMode {
        Binary,
        Json
    };
}

#endif //SRENGINE_MARSHALUTILS_H
