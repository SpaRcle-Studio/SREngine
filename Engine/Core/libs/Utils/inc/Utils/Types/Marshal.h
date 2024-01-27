//
// Created by Monika on 12.03.2022.
//

#ifndef SR_ENGINE_MARSHAL_H
#define SR_ENGINE_MARSHAL_H

#include <Utils/Common/MarshalUtils.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Stream.h>
#include <Utils/Common/StringFormat.h>

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT Marshal : public Stream {
    public:
        using Super = Stream;
        using Ptr = Marshal*;

    public:
        Marshal() = default;
        Marshal(std::ifstream& ifs); /** NOLINT */
        Marshal(const std::string& str); /** NOLINT */
        Marshal(const char* pData, uint64_t size);

    public:
        bool Save(const Path& path) const; /** NOLINT */
        SR_NODISCARD Marshal Copy() const;
        SR_NODISCARD Marshal::Ptr CopyPtr() const;

        SR_NODISCARD Marshal FullCopy() const;

        static Marshal Load(const Path& path);
        static Marshal::Ptr LoadPtr(const Path& path);
        static Marshal LoadFromMemory(const std::string& data);
        static Marshal LoadFromBase64(const std::string& base64);

        void Append(Marshal&& marshal);
        void Append(std::unique_ptr<Marshal>&& pMarshal);
        void Append(Marshal::Ptr& pMarshal);

        SR_NODISCARD Marshal ReadBytes(uint64_t count) noexcept;
        SR_NODISCARD Marshal::Ptr ReadBytesPtr(uint64_t count) noexcept;

        void WriteBlock(void* pData, uint64_t size) {
            Write<uint64_t>(size);

            if (size == 0) {
                return;
            }

            write(pData, size);
        }

        void ReadBlock(void* pDestination) {
            const auto size = Read<uint64_t>();

            if (size == 0) {
                return;
            }

            read(pDestination, size);
        }

        template<typename T> void Write(const T& value) {
            if constexpr (std::is_same_v<T, std::any>) {
                MarshalUtils::SaveAny<std::any>(*this, value);
            }
            else if constexpr (std::is_same_v<T, SR_UTILS_NS::StringAtom>) {
                MarshalUtils::SaveShortString(*this, value.ToStringRef());
            }
            else if constexpr (IsString<T>()) {
                MarshalUtils::SaveShortString(*this, value);  //нужно вызывать Write<std::string>()
            }
            else if constexpr (std::is_same_v<T, SR_HTYPES_NS::UnicodeString>) {
                MarshalUtils::SaveUnicodeString(*this, value);
            }
            else if constexpr (IsSTLVector<T>()) {
                MarshalUtils::SaveVector(*this, value);
            }
            else {
                MarshalUtils::SaveValue(*this, value);
            }
        }

        template<typename T> void Write(const T& value, const T& def) {
            if (value == def) {
                Write<bool>(true);
            }
            else {
                Write<bool>(false);
                Write<T>(value);
            }
        }

        template<typename T> T View(uint64_t offset) const {
            T value = T();

            memcpy(&value, Super::View() + offset, sizeof(T));

            return value;
        }

        template<typename T> T TryRead() {
            if constexpr (IsString<T>()) {
                return MarshalUtils::TryLoadShortStr(*this);
            }
            else if constexpr (std::is_same_v<T, SR_HTYPES_NS::UnicodeString>) {
                return MarshalUtils::TryLoadUnicodeString(*this);
            }
        }

        template<typename T> T Read() {
            if constexpr (std::is_same_v<T, std::any>) {
                return MarshalUtils::LoadAny<std::any>(*this);
            }
            else if constexpr (std::is_same_v<T, SR_HTYPES_NS::UnicodeString>) {
                return MarshalUtils::LoadUnicodeString(*this);
            }
            else if constexpr (IsString<T>()) {
                return MarshalUtils::LoadShortStr(*this);
            }
            else if constexpr (IsSTLVector<T>()) {
                return MarshalUtils::LoadVector<T>(*this);
            }
            else {
                return MarshalUtils::LoadValue<T>(*this);
            }
        }

        template<typename T> T Read(const T& def) {
            if (Read<bool>()) {
                return def;
            }

            return Read<T>();
        }
    };
}

#endif //SR_ENGINE_MARSHAL_H
