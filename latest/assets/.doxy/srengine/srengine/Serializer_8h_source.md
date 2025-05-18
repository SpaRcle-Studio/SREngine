

# File Serializer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**Serializer.h**](Serializer_8h.md)

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

        SR_NODISCARD const std::set<StringAtom>& GetDontSaveTags() const noexcept { return m_dontSaveTags; }

        void AddDontSaveTag(const StringAtom& tag) {
            m_dontSaveTags.insert(tag);
        }

        SR_NODISCARD bool CanSaveByTags(const std::set<StringAtom>& tags) const {
            for (const auto& tag : m_dontSaveTags) {
                if (tags.find(tag) != tags.end()) {
                    return false;
                }
            }
            return true;
        }

        SR_NODISCARD virtual bool SaveToFile(const SR_UTILS_NS::Path& path) const { return false; }

    private:
        std::set<StringAtom> m_dontSaveTags;
        bool m_isAllowEmptyElementsInArray = true;
        bool m_isNeedWriteDefaults = false;
        bool m_isEditorAllowed = false;
        bool m_isNeedWriteVersion = true;

    };
}

#endif //SR_COMMON_SERIALIZATION_SERIALIZER_H
```


