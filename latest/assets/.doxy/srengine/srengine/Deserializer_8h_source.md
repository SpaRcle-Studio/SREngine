

# File Deserializer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**Deserializer.h**](Deserializer_8h.md)

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


