//
// Created by Monika on 09.08.2022.
//

#ifndef SRENGINE_BASEMARSHAL_H
#define SRENGINE_BASEMARSHAL_H

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

        SR_MAYBE_UNUSED static void SR_FASTCALL SaveShortString(std::stringstream& stream, const std::string& str, uint64_t& bytesCount) {
            const int16_t size = str.size();
            stream.write((const char*)&size, sizeof(int16_t));
            stream.write((const char*)&str[0], size * sizeof(char));

            bytesCount += sizeof(int16_t) + size * sizeof(char);
        }

        SR_MAYBE_UNUSED static void SR_FASTCALL SaveString(std::stringstream& stream, const std::string& str, uint64_t& bytesCount) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));

            bytesCount += sizeof(size_t) + size * sizeof(char);
        }

        static void SR_FASTCALL SaveString(std::stringstream& stream, const std::string_view& str, uint64_t& bytesCount) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));

            bytesCount += sizeof(size_t) + size * sizeof(char);
        }

        template<typename T> static void SR_FASTCALL SaveVector(std::stringstream& stream, const std::vector<T>& vector, uint64_t& bytesCount) {
            const size_t size = vector.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)vector.data(), size * sizeof(T));

            bytesCount += sizeof(size_t) + size * sizeof(T);
        }

        template<typename Stream> static std::string SR_FASTCALL LoadShortStr(Stream& stream, uint64_t& readCount) {
            std::string str;
            uint16_t size;
            stream.read((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return std::string();
            }
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
            if (size >= SR_UINT16_MAX) {
                return std::string();
            }
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            readCount += sizeof(size_t) + (size * sizeof(char));
            return str;
        }

        template<typename Stream> static std::string SR_FASTCALL LoadStr(Stream& stream) {
            uint64_t readCount = 0;
            return LoadStr<Stream>(stream, readCount);
        }
    }
}

#endif //SRENGINE_BASEMARSHAL_H
