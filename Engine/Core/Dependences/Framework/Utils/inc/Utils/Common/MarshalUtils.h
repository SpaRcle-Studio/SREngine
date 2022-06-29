//
// Created by Monika on 30.03.2022.
//

#ifndef SRENGINE_MARSHALUTILS_H
#define SRENGINE_MARSHALUTILS_H

#include <Utils/Common/StringFormat.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Common/TypeInfo.h>

namespace SR_UTILS_NS {
    namespace MarshalUtils {
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
                SR_STATIC_ASSERT("Unsupported type!");
            }
        }

        template<typename Stream, typename T> static T SR_FASTCALL LoadValue(Stream& stream, uint64_t& readCount) {
            T value = T();

            if constexpr (std::is_same<T, Math::FColor>()) {
                stream.read((char*)&value.r, sizeof(Math::Unit));
                stream.read((char*)&value.g, sizeof(Math::Unit));
                stream.read((char*)&value.b, sizeof(Math::Unit));
                stream.read((char*)&value.a, sizeof(Math::Unit));
                readCount += sizeof(Math::Unit) * 4;
            }
            else if constexpr (std::is_same<T, Math::FVector3>()) {
                stream.read((char*)&value.x, sizeof(Math::Unit));
                stream.read((char*)&value.y, sizeof(Math::Unit));
                stream.read((char*)&value.z, sizeof(Math::Unit));
                readCount += sizeof(Math::Unit) * 3;
            }
            else if constexpr (std::is_same<T, Math::FVector2>()) {
                stream.read((char*)&value.x, sizeof(Math::Unit));
                stream.read((char*)&value.y, sizeof(Math::Unit));
                readCount += sizeof(Math::Unit) * 2;
            }
            else if constexpr (std::is_same<T, Math::IVector3>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
                stream.read((char*)&value.z, sizeof(int32_t));
                readCount += sizeof(int32_t) * 3;
            }
            else if constexpr (std::is_same<T, Math::IVector2>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
                readCount += sizeof(int32_t) * 2;
            }
            else if constexpr (Math::IsNumber<T>() || Math::IsLogical<T>()) {
                stream.read((char*)&value, sizeof(T));
                readCount += sizeof(T);
            }
            else {
                SR_STATIC_ASSERT("Unsupported type!");
            }

            return value;
        }

        template<typename Stream, typename T> static T SR_FASTCALL LoadValue(Stream& stream) {
            uint64_t readCount = 0;
            return LoadValue<Stream, T>(stream, readCount);
        }

        static void SR_FASTCALL SaveShortString(std::stringstream& stream, const std::string& str, uint64_t& bytesCount) {
            const int16_t size = str.size();
            stream.write((const char*)&size, sizeof(int16_t));
            stream.write((const char*)&str[0], size * sizeof(char));

            bytesCount += sizeof(int16_t) + size * sizeof(char);
        }

        static void SR_FASTCALL SaveString(std::stringstream& stream, const std::string& str, uint64_t& bytesCount) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));

            bytesCount += sizeof(size_t) + size * sizeof(char);
        }

        template<typename Stream> static std::string SR_FASTCALL LoadShortStr(Stream& stream, uint64_t& readCount) {
            std::string str;
            uint16_t size;
            stream.read((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            readCount += sizeof(uint16_t) + (size * sizeof(char));
            return str;
        }

        template<typename Stream> static std::string SR_FASTCALL LoadShortStr(Stream& stream) {
            uint64_t readCount = 0;
            return LoadShortStr<Stream>(stream, readCount);
        }

        template<typename Stream> static std::string SR_FASTCALL LoadStr(Stream& stream, uint64_t& readCount) {
            std::string str;
            size_t size;
            stream.read((char*)&size, sizeof(size_t));
            SRAssert(size < SR_UINT16_MAX);
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            readCount += sizeof(size_t) + (size * sizeof(char));
            return str;
        }

        template<typename Stream> static std::string SR_FASTCALL LoadStr(Stream& stream) {
            uint64_t readCount = 0;
            return LoadStr<Stream>(stream, readCount);
        }

        template<typename Stream> static std::any SR_FASTCALL LoadAny(Stream& stream, uint64_t& readCount) {
            auto&& type = static_cast<StandardType>(LoadValue<Stream, uint16_t>(stream, readCount));

            switch (type) {
                case StandardType::Bool: return LoadValue<Stream, bool>(stream, readCount);
                case StandardType::Int8: return LoadValue<Stream, int8_t>(stream, readCount);
                case StandardType::UInt8: return LoadValue<Stream, uint8_t>(stream, readCount);
                case StandardType::Int16: return LoadValue<Stream, int16_t>(stream, readCount);
                case StandardType::UInt16: return LoadValue<Stream, uint16_t>(stream, readCount);
                case StandardType::Int32: return LoadValue<Stream, int32_t>(stream, readCount);
                case StandardType::UInt32: return LoadValue<Stream, uint32_t>(stream, readCount);
                case StandardType::Int64: return LoadValue<Stream, int64_t>(stream, readCount);
                case StandardType::UInt64: return LoadValue<Stream, uint64_t>(stream, readCount);
                case StandardType::Float: return LoadValue<Stream, float_t>(stream, readCount);
                case StandardType::Double: return LoadValue<Stream, double_t>(stream, readCount);
                case StandardType::String: return LoadStr<Stream>(stream, readCount);
                default:
                    SRHalt0();
                    return std::any();
            }
        }

        template<typename Stream> static void SR_FASTCALL SaveAny(Stream& stream, const std::any& any, uint64_t& bytesCount) {
            try {
                auto&& type = GetStandardType(any);

                SaveValue(stream, static_cast<uint16_t>(type));

                bytesCount += sizeof(StandardType);

                /// string ignored
                bytesCount += GetTypeSize(type);

                switch (type) {
                    case StandardType::Bool: SaveValue(stream, std::any_cast<bool>(any)); break;
                    case StandardType::Int8: SaveValue(stream, std::any_cast<int8_t>(any)); break;
                    case StandardType::UInt8: SaveValue(stream, std::any_cast<uint8_t>(any)); break;
                    case StandardType::Int16: SaveValue(stream, std::any_cast<int16_t>(any)); break;
                    case StandardType::UInt16: SaveValue(stream, std::any_cast<uint16_t>(any)); break;
                    case StandardType::Int32: SaveValue(stream, std::any_cast<int32_t>(any)); break;
                    case StandardType::UInt32: SaveValue(stream, std::any_cast<uint32_t>(any)); break;
                    case StandardType::Int64: SaveValue(stream, std::any_cast<int64_t>(any)); break;
                    case StandardType::UInt64: SaveValue(stream, std::any_cast<uint64_t>(any)); break;
                    case StandardType::Float: SaveValue(stream, std::any_cast<float_t>(any)); break;
                    case StandardType::Double: SaveValue(stream, std::any_cast<double_t>(any)); break;
                    case StandardType::String: SaveString(stream, std::any_cast<std::string>(any), bytesCount); break;
                    default:
                        SRHalt0();
                        break;
                }
            }
            catch(const std::bad_any_cast& e) {
                SRHalt0();
            }
        }

        static void Encode(std::stringstream& stream, const std::string& str, StandardType type) {
            uint64_t bytesCount = 0;
            switch (type) {
                case StandardType::Bool: SaveValue(stream, LexicalCast<bool>(str)); break;
                case StandardType::Int8: SaveValue(stream, LexicalCast<int8_t>(str)); break;
                case StandardType::UInt8: SaveValue(stream, LexicalCast<uint8_t>(str)); break;
                case StandardType::Int16: SaveValue(stream, LexicalCast<int16_t>(str)); break;
                case StandardType::UInt16: SaveValue(stream, LexicalCast<uint16_t>(str)); break;
                case StandardType::Int32: SaveValue(stream, LexicalCast<int32_t>(str)); break;
                case StandardType::UInt32: SaveValue(stream, LexicalCast<uint32_t>(str)); break;
                case StandardType::Int64: SaveValue(stream, LexicalCast<int64_t>(str)); break;
                case StandardType::UInt64: SaveValue(stream, LexicalCast<uint64_t>(str)); break;
                case StandardType::Float: SaveValue(stream, LexicalCast<float_t>(str)); break;
                case StandardType::Double: SaveValue(stream, LexicalCast<double_t>(str)); break;
                case StandardType::String: SaveString(stream, str, bytesCount); break;
            }
        }
    }

    enum class MarshalSaveMode {
        Binary,
        Json
    };
}

#endif //SRENGINE_MARSHALUTILS_H
