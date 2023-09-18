//
// Created by Monika on 09.08.2022.
//

#ifndef SRENGINE_BASEMARSHAL_H
#define SRENGINE_BASEMARSHAL_H

#include <Utils/Common/StringFormat.h>
#include <Utils/Types/Stream.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Common/TypeInfo.h>
#include <Utils/Types/UnicodeString.h>

namespace SR_UTILS_NS {
    namespace MarshalUtils {
        template<typename T> static void SR_FASTCALL SaveValue(SR_HTYPES_NS::Stream& stream, const T& value) {
            if constexpr (std::is_same<T, SR_MATH_NS::FColor>()) {
                stream.write((const char *) &value.r, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.g, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.b, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.a, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::FVector3>()) {
                stream.write((const char *) &value.x, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.y, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.z, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<float>>()) {
                stream.write((const char *) &value.x, sizeof(float));
                stream.write((const char *) &value.y, sizeof(float));
                stream.write((const char *) &value.z, sizeof(float));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<double>>()) {
                stream.write((const char *) &value.x, sizeof(double));
                stream.write((const char *) &value.y, sizeof(double));
                stream.write((const char *) &value.z, sizeof(double));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<bool>>()) {
                stream.write((const char *) &value.x, sizeof(bool));
                stream.write((const char *) &value.y, sizeof(bool));
                stream.write((const char *) &value.z, sizeof(bool));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::FVector2>()) {
                stream.write((const char *) &value.x, sizeof(SR_MATH_NS::Unit));
                stream.write((const char *) &value.y, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::IVector3>()) {
                stream.write((const char *) &value.x, sizeof(int32_t));
                stream.write((const char *) &value.y, sizeof(int32_t));
                stream.write((const char *) &value.z, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::BVector3>()) {
                stream.write((const char *) &value.x, sizeof(bool));
                stream.write((const char *) &value.y, sizeof(bool));
                stream.write((const char *) &value.z, sizeof(bool));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::IVector2>()) {
                stream.write((const char *) &value.x, sizeof(int32_t));
                stream.write((const char *) &value.y, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::UVector2>()) {
                stream.write((const char *) &value.x, sizeof(uint32_t));
                stream.write((const char *) &value.y, sizeof(uint32_t));
            }
            else if constexpr (SR_MATH_NS::IsNumber<T>() || SR_MATH_NS::IsLogical<T>()) {
                stream.write((const char *) &value, sizeof(T));
            }
            else {
                SRHalt("Unsupported type!");
            }
        }

        template<typename T> static T SR_FASTCALL LoadValue(SR_HTYPES_NS::Stream& stream) {
            T value = T();

            if constexpr (std::is_same<T, SR_MATH_NS::FColor>()) {
                stream.read((char*)&value.r, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.g, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.b, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.a, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::FVector3>()) {
                stream.read((char*)&value.x, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.y, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.z, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<float>>()) {
                stream.read((char*)&value.x, sizeof(float));
                stream.read((char*)&value.y, sizeof(float));
                stream.read((char*)&value.z, sizeof(float));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<double>>()) {
                stream.read((char*)&value.x, sizeof(double));
                stream.read((char*)&value.y, sizeof(double));
                stream.read((char*)&value.z, sizeof(double));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::Vector3<bool>>()) {
                stream.read((char*)&value.x, sizeof(bool));
                stream.read((char*)&value.y, sizeof(bool));
                stream.read((char*)&value.z, sizeof(bool));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::FVector2>()) {
                stream.read((char*)&value.x, sizeof(SR_MATH_NS::Unit));
                stream.read((char*)&value.y, sizeof(SR_MATH_NS::Unit));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::IVector3>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
                stream.read((char*)&value.z, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::BVector3>()) {
                stream.read((char*)&value.x, sizeof(bool));
                stream.read((char*)&value.y, sizeof(bool));
                stream.read((char*)&value.z, sizeof(bool));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::IVector2>()) {
                stream.read((char*)&value.x, sizeof(int32_t));
                stream.read((char*)&value.y, sizeof(int32_t));
            }
            else if constexpr (std::is_same<T, SR_MATH_NS::UVector2>()) {
                stream.read((char*)&value.x, sizeof(uint32_t));
                stream.read((char*)&value.y, sizeof(uint32_t));
            }
            else if constexpr (SR_MATH_NS::IsNumber<T>() || SR_MATH_NS::IsLogical<T>()) {
                stream.read((char*)&value, sizeof(T));
            }
            else {
                SRHalt("Unsupported type!");
            }

            return value;
        }

        SR_MAYBE_UNUSED static void SR_FASTCALL SaveShortString(SR_HTYPES_NS::Stream& stream, const std::string& str) {
            const int16_t size = str.size();
            stream.write((const char*)&size, sizeof(int16_t));
            stream.write((const char*)&str[0], size * sizeof(char));
        }

        SR_MAYBE_UNUSED static void SR_FASTCALL SaveUnicodeString(SR_HTYPES_NS::Stream& stream, const SR_HTYPES_NS::UnicodeString& str) {
            const int16_t size = str.size();
            stream.write((const char*)&size, sizeof(int16_t));
            stream.write((const char*)&str[0], size * sizeof(SR_HTYPES_NS::UnicodeString::CharType));
        }

        SR_MAYBE_UNUSED static void SR_FASTCALL SaveString(SR_HTYPES_NS::Stream& stream, const std::string& str) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));
        }

        static void SR_FASTCALL SaveString(SR_HTYPES_NS::Stream& stream, const std::string_view& str) {
            const size_t size = str.size();
            stream.write((const char*)&size, sizeof(size_t));
            stream.write((const char*)&str[0], size * sizeof(char));
        }

        template<typename T> static void SR_FASTCALL SaveVector(SR_HTYPES_NS::Stream& stream, const std::vector<T>& vector) {
            const size_t size = vector.size();
            stream.write((const char*)&size, sizeof(size_t));
            if (size > 0) {
                stream.write((const char *) vector.data(), size * sizeof(T));
            }
        }

        template<typename Vector> static Vector SR_FASTCALL LoadVector(SR_HTYPES_NS::Stream& stream) {
            Vector vector;

            size_t size;
            stream.read((char*)&size, sizeof(size_t));

            using T = typename std::decay<decltype(*vector.begin())>::type;

            if (size > 0) {
                vector.resize(size);
                stream.read((char*)&vector[0], size * sizeof(T));
            }

            return std::move(vector);
        }

        static std::string SR_FASTCALL LoadShortStr(SR_HTYPES_NS::Stream& stream) {
            std::string str;
            uint16_t size;
            stream.read((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return str;
            }
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            return str;
        }

        static SR_HTYPES_NS::UnicodeString SR_FASTCALL LoadUnicodeString(SR_HTYPES_NS::Stream& stream) {
            SR_HTYPES_NS::UnicodeString str;
            uint16_t size;
            stream.read((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return str;
            }
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(SR_HTYPES_NS::UnicodeString::CharType));
            return str;
        }

        static std::string SR_FASTCALL LoadStr(SR_HTYPES_NS::Stream& stream) {
            std::string str;
            size_t size;
            stream.read((char*)&size, sizeof(size_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return std::string(); /// NOLINT
            }
            str.resize(size);
            stream.read((char*)&str[0], size * sizeof(char));
            return str;
        }

        static std::string SR_FASTCALL TryLoadShortStr(SR_HTYPES_NS::Stream& stream) {
            std::string str;
            uint16_t size;
            stream.TryRead((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return str;
            }
            str.resize(size);
            stream.TryRead((char*)&str[0], size * sizeof(char));
            return str;
        }

        static SR_HTYPES_NS::UnicodeString SR_FASTCALL TryLoadUnicodeString(SR_HTYPES_NS::Stream& stream) {
            SR_HTYPES_NS::UnicodeString str;
            uint16_t size;
            stream.TryRead((char*)&size, sizeof(uint16_t));
            SRAssert(size < SR_UINT16_MAX);
            if (size >= SR_UINT16_MAX) {
                return str;
            }
            str.resize(size);
            stream.TryRead((char*)&str[0], size * sizeof(SR_HTYPES_NS::UnicodeString::CharType));
            return str;
        }
    }
}

#endif //SRENGINE_BASEMARSHAL_H
