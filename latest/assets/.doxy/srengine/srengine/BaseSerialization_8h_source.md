

# File BaseSerialization.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**BaseSerialization.h**](BaseSerialization_8h.md)

[Go to the documentation of this file](BaseSerialization_8h.md)


```C++
//
// Created by Monika on 09.03.2025.
//

#include <Utils/Serialization/Serializer.h>
#include <Utils/Serialization/Deserializer.h>
#include <Utils/Localization/Encoding.h>
#include <Utils/Types/FastMemoryArray.h>

#ifndef SR_ENGINE_BASE_SERIALIZATION_H
#define SR_ENGINE_BASE_SERIALIZATION_H

namespace SR_UTILS_NS {
    union SerializationTrivialDataType {
        bool boolean;
        int64_t integer;
        double_t floating;
    };

    enum class SerializationDataType : uint8_t {
        Unknown,
        Root,
        String,
        Boolean,
        Integer,
        Floating,
        Object,
        Item,
        Array
    };

    struct SerializationNode {
        SerializationNode() = default;
        SerializationNode(const SerializationId& id, SerializationDataType type)
            : id(id)
            , type(type)
        { }

        SerializationNode(SerializationNode&& other) noexcept
            : id(other.id)
            , type(other.type)
            , string(std::move(other.string))
            , data(other.data)
            , children(std::move(other.children))
        { }

        SerializationNode(const SerializationNode& other)
            : id(other.id)
            , type(other.type)
            , string(other.string)
            , data(other.data)
            , children(other.children)
        { }

        SerializationNode& operator=(SerializationNode&& other) noexcept {
            id = other.id;
            type = other.type;
            string = std::move(other.string);
            data = other.data;
            children = std::move(other.children);
            return *this;
        }

        SerializationNode& operator=(const SerializationNode& other) {
            id = other.id;
            type = other.type;
            string = other.string;
            data = other.data;
            children = other.children;
            return *this;
        }

        SerializationId id;
        SerializationDataType type = SerializationDataType::Unknown;
        std::string string;
        SerializationTrivialDataType data = {};
        std::vector<SerializationNode> children;
    };

    class IBaseSerializer;
    class IBaseDeserializer;

    class IBaseSerialization {
        friend IBaseSerializer;
        friend IBaseDeserializer;
    public:
        IBaseSerialization();

        SR_NODISCARD virtual std::string ToStringBase() const noexcept = 0;

        SR_NODISCARD SerializationNode& GetCurrentNode() noexcept { return *m_stack.back(); }
        SR_NODISCARD const SerializationNode& GetCurrentNode() const noexcept { return *m_stack.back(); }
        SR_NODISCARD SerializationNode& GetWalkNode() noexcept { return *m_walker.back(); }
        SR_NODISCARD const SerializationNode& GetWalkNode() const noexcept { return *m_walker.back(); }

        void WriteNode(const SerializationNode& node) noexcept;

    protected:
        SR_NODISCARD virtual bool IsAllowEmptyElementsInArrayImpl() const noexcept { return true; }
        SR_NODISCARD bool SaveToFileImpl(const SR_UTILS_NS::Path& path) const;

    protected:
        SR_HTYPES_NS::FastMemoryArray<SerializationNode*> m_stack;
        SR_HTYPES_NS::FastMemoryArray<SerializationNode*> m_walker;
        SerializationNode m_root;

    };

    class IBaseSerializer : public ISerializer {
    public:
        SR_NODISCARD bool SaveToFile(const SR_UTILS_NS::Path& path) const override { return GetImpl().SaveToFileImpl(path); }
        SR_NODISCARD std::string ToString() const noexcept override { return GetImpl().ToStringBase(); }

        void WriteString(std::string_view value, const SerializationId& name) override;
        void WriteString(std::u32string_view value, const SerializationId& name) override;
        void WriteBool(bool value, const SerializationId& name) override;
        void WriteInt(int8_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteInt(int16_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteInt(int32_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteInt(int64_t value, const SerializationId& name) override;
        void WriteUInt(uint8_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteUInt(uint16_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteUInt(uint32_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteUInt(uint64_t value, const SerializationId& name) override { WriteInt(static_cast<int64_t>(value), name); }
        void WriteFloat(float_t value, const SerializationId& name) override { WriteDouble(static_cast<double_t>(value), name); }
        void WriteDouble(double_t value, const SerializationId& name) override;

        void BeginItem(const SerializationId& id) override;
        void EndItem() override;

        void BeginObject(const SerializationId& id) override;
        void EndObject() override;

        void BeginArray(uint64_t size, const SerializationId& id) override;
        void EndArray() override;

    private:
        SR_NODISCARD IBaseSerialization& GetImpl() const noexcept {
            if (!m_pBaseSerialization) SR_UNLIKELY_ATTRIBUTE {
                m_pBaseSerialization = dynamic_cast<IBaseSerialization*>(const_cast<IBaseSerializer*>(this));
                SRAssert2(m_pBaseSerialization, "Failed to cast IBaseSerializer to IBaseSerialization");
            }
            return *m_pBaseSerialization;
        }

    private:
        mutable IBaseSerialization* m_pBaseSerialization = nullptr;

    };

    class IBaseDeserializer : public IDeserializer {
        using Super = IDeserializer;
    public:
        IBaseDeserializer();

        SR_NODISCARD bool SaveToFile(const SR_UTILS_NS::Path& path) const override { return GetImpl().SaveToFileImpl(path); }

        SR_NODISCARD bool IsDefault(const SerializationId& name) const noexcept override;

        void ResetWalker() override { GetImpl().m_walker.resize(1); }

        bool BeginItem(const SerializationId& id, uint32_t index) override;
        void EndItem() override;

        bool BeginObject(const SerializationId& id) override;
        void EndObject() override;

        uint64_t BeginArray(const SerializationId& id) override;
        void EndArray() override;

        void ReadString(std::string& value, const SerializationId& name) override { return ReadStringImpl(value, name); }
        void ReadString(SR_UTILS_NS::StringAtom& value, const SerializationId& name) override { return ReadStringImpl(value, name); }
        void ReadString(SR_UTILS_NS::Path& value, const SerializationId& name) override { return ReadStringImpl(value, name); }

        void ReadString(SR_HTYPES_NS::UnicodeString& value, const SerializationId& name) override {
            std::string temp;
            ReadStringImpl(temp, name);
            value = SR_UTILS_NS::Localization::UtfToUtf<char32_t, char>(temp);
        }

        void ReadBool(bool& value, const SerializationId& name) override {
            auto&& node = GetImpl().GetWalkNode();
            for (auto&& child : node.children) {
                if (child.id.GetHash() == name.GetHash()) {
                    if (child.type == SerializationDataType::Boolean) {
                        value = child.data.boolean;
                    }
                    break;
                }
            }
        }

        void ReadInt(int8_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadInt(int16_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadInt(int32_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadInt(int64_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadUInt(uint8_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadUInt(uint16_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadUInt(uint32_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }
        void ReadUInt(uint64_t& value, const SerializationId& name) override { return ReadIntegerImpl(value, name); }

        void ReadFloat(float_t& value, const SerializationId& name) override { return ReadFloatingImpl(value, name); }
        void ReadDouble(double_t& value, const SerializationId& name) override { return ReadFloatingImpl(value, name); }

    private:
        template<typename T> void ReadIntegerImpl(T& value, const SerializationId& name) {
            auto&& node = GetImpl().GetWalkNode();
            for (auto&& child : node.children) {
                if (child.id.GetHash() == name.GetHash()) {
                    if (child.type == SerializationDataType::Integer) {
                        value = static_cast<T>(child.data.integer);
                    }
                    break;
                }
            }
        }

        template<typename T> void ReadFloatingImpl(T& value, const SerializationId& name) {
            auto&& node = GetImpl().GetWalkNode();
            for (auto&& child : node.children) {
                if (child.id.GetHash() == name.GetHash()) {
                    if (child.type == SerializationDataType::Floating) {
                        value = static_cast<T>(child.data.floating);
                    }
                    break;
                }
            }
        }

        template<typename T> void ReadStringImpl(T& value, const SerializationId& name) {
            auto&& node = GetImpl().GetWalkNode();
            for (auto&& child : node.children) {
                if (child.id.GetHash() == name.GetHash()) {
                    if (child.type == SerializationDataType::String) {
                        value = child.string;
                    }
                    break;
                }
            }
        }

    private:
        SR_NODISCARD IBaseSerialization& GetImpl() const noexcept {
            if (!m_pBaseSerialization) SR_UNLIKELY_ATTRIBUTE {
                m_pBaseSerialization = dynamic_cast<IBaseSerialization*>(const_cast<IBaseDeserializer*>(this));
                SRAssert2(m_pBaseSerialization, "Failed to cast IBaseDeserializer to IBaseSerialization");
            }
            return *m_pBaseSerialization;
        }

    private:
        mutable IBaseSerialization* m_pBaseSerialization = nullptr;

    };
}

#endif //SR_ENGINE_BASE_SERIALIZATION_H
```


