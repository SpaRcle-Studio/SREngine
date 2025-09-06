

# File Marshal.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Marshal.h**](Marshal_8h.md)

[Go to the documentation of this file](Marshal_8h.md)


```C++
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
    class SR_COMMON_DLL_API Marshal : public Stream {
    public:
        using Super = Stream;
        using Ptr = Marshal*;

    public:
        Marshal();
        Marshal(std::ifstream& ifs); 
        Marshal(const std::string& str); 
        Marshal(const char* pData, uint64_t size, bool copy = true);
        ~Marshal();

    public:
        bool Save(const Path& path) const; 
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

        void WriteBlock(void* pData, uint64_t size);
        void ReadBlock(void* pDestination);

        template<typename T> void Write(const T& value);
        template<typename T> void Write(const T& value, const T& def);
        template<typename T> T View(uint64_t offset) const;
        template<typename T> T TryRead();
        template<typename T> T Read();
        template<typename T> T Read(const T& def);
    };

    template<typename T> void Marshal::Write(const T& value, const T& def) {
        if (value == def) {
            Write<bool>(true);
        }
        else {
            Write<bool>(false);
            Write<T>(value);
        }
    }

    template<typename T> T Marshal::View(uint64_t offset) const {
        T value = T();

        memcpy(&value, Super::View() + offset, sizeof(T));

        return value;
    }

    template<typename T> T Marshal::TryRead() {
        if constexpr (IsString<T>()) {
            return MarshalUtils::TryLoadShortStr(*this);
        }
        else if constexpr (std::is_same_v<T, SR_HTYPES_NS::UnicodeString>) {
            return MarshalUtils::TryLoadUnicodeString(*this);
        }
    }

    template<typename T> T Marshal::Read() {
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

    template<typename T> void Marshal::Write(const T &value) {
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

    template<typename T> T Marshal::Read(const T &def) {
        if (Read<bool>()) {
            return def;
        }

        return Read<T>();
    }
}

#endif //SR_ENGINE_MARSHAL_H
```


