

# File Serializer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**Serializer.h**](Serializer_8h.md)

[Go to the documentation of this file](Serializer_8h.md)


```C++
//
// Created by Monika on 16.10.2024.
//

#ifndef SR_COMMON_SERIALIZATION_SERIALIZER_H
#define SR_COMMON_SERIALIZATION_SERIALIZER_H

#include <Utils/TypeTraits/TypeTraits.h>

namespace SR_UTILS_NS {
    class IDeserializer;

    class ISerializer {
    public:
        using UniquePtr = std::unique_ptr<ISerializer>;

    public:
        virtual ~ISerializer() = default;

        SR_NODISCARD virtual std::unique_ptr<IDeserializer> CreateDeserializer() const = 0;

        SR_NODISCARD virtual bool IsWriteDefaults() const noexcept { return m_isNeedWriteDefaults; }
        SR_NODISCARD virtual bool IsEditorAllowed() const noexcept { return m_isEditorAllowed; }
        SR_NODISCARD virtual bool IsAllowEmptyElementsInArray() const noexcept { return m_isAllowEmptyElementsInArray; }
        SR_NODISCARD virtual bool IsWriteVersion() const noexcept { return m_isNeedWriteVersion; }
        SR_NODISCARD virtual std::string ToString() const noexcept { return ""; }

        void SetWriteDefaults(const bool value) noexcept { m_isNeedWriteDefaults = value; }
        void SetEditorAllowed(const bool value) noexcept { m_isEditorAllowed = value; }
        void SetAllowEmptyElementsInArray(const bool value) noexcept { m_isAllowEmptyElementsInArray = value; }
        void SetWriteVersion(const bool value) noexcept { m_isNeedWriteVersion = value; }

        void WriteAny(const std::any& value, const SerializationId& name);

        virtual void WriteString(std::string_view value, const SerializationId& name) = 0;
        virtual void WriteString(std::u32string_view value, const SerializationId& name) = 0;
        virtual void WriteBool(bool value, const SerializationId& name) = 0;
        virtual void WriteInt(int8_t value, const SerializationId& name) = 0;
        virtual void WriteInt(int16_t value, const SerializationId& name) = 0;
        virtual void WriteInt(int32_t value, const SerializationId& name) = 0;
        virtual void WriteInt(int64_t value, const SerializationId& name) = 0;
        virtual void WriteUInt(uint8_t value, const SerializationId& name) = 0;
        virtual void WriteUInt(uint16_t value, const SerializationId& name) = 0;
        virtual void WriteUInt(uint32_t value, const SerializationId& name) = 0;
        virtual void WriteUInt(uint64_t value, const SerializationId& name) = 0;
        virtual void WriteFloat(float_t value, const SerializationId& name) = 0;
        virtual void WriteDouble(double_t value, const SerializationId& name) = 0;

        virtual void BeginItem(const SerializationId& id) = 0;
        virtual void EndItem() = 0;

        virtual void BeginObject(const SerializationId& id) = 0;
        virtual void EndObject() = 0;

        virtual void BeginArray(uint64_t size, const SerializationId& id) = 0;
        virtual void EndArray() = 0;

        SR_NODISCARD virtual bool SaveToFile(const SR_UTILS_NS::Path& path) const { return false; }

    private:
        bool m_isAllowEmptyElementsInArray = true;
        bool m_isNeedWriteDefaults = false;
        bool m_isEditorAllowed = false;
        bool m_isNeedWriteVersion = true;

    };
}

#endif //SR_COMMON_SERIALIZATION_SERIALIZER_H
```


