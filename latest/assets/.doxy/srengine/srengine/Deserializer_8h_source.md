

# File Deserializer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**Deserializer.h**](Deserializer_8h.md)

[Go to the documentation of this file](Deserializer_8h.md)


```C++
//
// Created by Monika on 16.10.2024.
//

#ifndef SR_COMMON_SERIALIZATION_DESERIALIZER_H
#define SR_COMMON_SERIALIZATION_DESERIALIZER_H

#include <Utils/TypeTraits/TypeTraits.h>

namespace SR_UTILS_NS {
    class IDeserializer {
    public:
        using UniquePtr = std::unique_ptr<IDeserializer>;

    public:
        enum class ReAllocPointerReason : uint8_t {
            None,
            IsNull,
            HasDifferentType
        };

    public:
        virtual ~IDeserializer() = default;

        SR_NODISCARD virtual bool SaveToFile(const SR_UTILS_NS::Path& path) const = 0;
        SR_NODISCARD virtual bool LoadFromFile(const SR_UTILS_NS::Path& path) = 0;
        SR_NODISCARD virtual bool LoadFromString(const std::string& str) = 0;
        SR_NODISCARD virtual std::string ToString() const noexcept { return ""; }

        SR_NODISCARD virtual bool IsDefault(const SerializationId& name) const noexcept = 0;
        SR_NODISCARD virtual bool ShouldSetDefaults(const SerializationId& name) const noexcept = 0;
        SR_NODISCARD virtual bool ShouldSetDefaults() const noexcept = 0;
        SR_NODISCARD virtual bool AllowNewMapKeys() const noexcept = 0;
        SR_NODISCARD virtual bool IsPreserveMode() const noexcept = 0;
        SR_NODISCARD virtual bool AllowReAllocPointer(ReAllocPointerReason reason) const noexcept = 0;

        virtual void ResetWalker() = 0;

        virtual bool BeginItem(const SerializationId& id, uint32_t index) = 0;
        virtual void EndItem() = 0;

        virtual bool BeginObject(const SerializationId& id) = 0;
        virtual void EndObject() = 0;

        virtual uint64_t BeginArray(const SerializationId& id) = 0;
        virtual void EndArray() = 0;

        void ReadAny(std::any& value, const SerializationId& name);

        virtual void ReadString(std::string& value, const SerializationId& name) = 0;
        virtual void ReadString(SR_UTILS_NS::StringAtom& value, const SerializationId& name) = 0;
        virtual void ReadString(SR_HTYPES_NS::UnicodeString& value, const SerializationId& name) = 0;
        virtual void ReadString(SR_UTILS_NS::Path& value, const SerializationId& name) = 0;
        virtual void ReadBool(bool& value, const SerializationId& name) = 0;
        virtual void ReadInt(int8_t& value, const SerializationId& name) = 0;
        virtual void ReadInt(int16_t& value, const SerializationId& name) = 0;
        virtual void ReadInt(int32_t& value, const SerializationId& name) = 0;
        virtual void ReadInt(int64_t& value, const SerializationId& name) = 0;
        virtual void ReadUInt(uint8_t& value, const SerializationId& name) = 0;
        virtual void ReadUInt(uint16_t& value, const SerializationId& name) = 0;
        virtual void ReadUInt(uint32_t& value, const SerializationId& name) = 0;
        virtual void ReadUInt(uint64_t& value, const SerializationId& name) = 0;
        virtual void ReadFloat(float_t& value, const SerializationId& name) = 0;
        virtual void ReadDouble(double_t& value, const SerializationId& name) = 0;

        virtual void ReportError(const std::string& message) = 0;

    };
}

#endif //SR_COMMON_SERIALIZATION_DESERIALIZER_H
```


