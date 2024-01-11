//
// Created by Monika on 25.08.2023.
//

#ifndef SR_ENGINE_DATATYPE_H
#define SR_ENGINE_DATATYPE_H

#include <Utils/SRLM/Utils.h>
#include <Utils/Xml.h>

namespace SR_UTILS_NS {
    class EnumReflector;
}

namespace SR_SRLM_NS {
    SR_ENUM_NS_CLASS_T(DataTypeClass, uint8_t,
        None, Flow, Enum, Struct, Array, Map, Set,
        Bool, Float, Double, String,
        Int8, Int16, Int32, Int64,
        UInt8, UInt16, UInt32, UInt64
    );

    /// ----------------------------------------------------------------------------------------------------------------

    class DataType;

    class DataTypeAllocator : public SR_UTILS_NS::Singleton<DataTypeAllocator> {
        SR_REGISTER_SINGLETON(DataTypeAllocator)
        using Hash = uint64_t;
        using Allocator = SR_HTYPES_NS::Function<DataType*()>;
        static constexpr uint32_t EnumMax = static_cast<int>(DataTypeClass::DataTypeClassMAX);
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }

        bool Register(DataTypeClass dataTypeClass, Hash hashName, Allocator allocator);

        DataType* Allocate(DataTypeClass dataTypeClass);
        DataType* Allocate(Hash hashName);

    private:
        Hash m_hashes[EnumMax];
        Allocator m_allocators[EnumMax];

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataType : SR_UTILS_NS::NonCopyable {
    public:
        using Meta = uint64_t;
        using Hash = uint64_t;

    public:
        virtual void Reset() = 0;
        virtual void CopyTo(DataType* pData) const = 0;

        void SaveXml(SR_XML_NS::Node& xmlNode);

        static DataType* LoadXml(const SR_XML_NS::Node& xmlNode);

        SR_NODISCARD virtual std::vector<DataType*> GetMetaData() const { return std::vector<DataType*>(); }
        SR_NODISCARD virtual DataType* Copy() const = 0;
        SR_NODISCARD virtual Meta GetMeta() const noexcept = 0;
        SR_NODISCARD virtual std::string GetName() const noexcept = 0;
        SR_NODISCARD virtual Hash GetHashName() const noexcept = 0;
        SR_NODISCARD virtual DataTypeClass GetClass() const noexcept = 0;
        SR_NODISCARD virtual void* GetRawValue() const noexcept { return nullptr; }

        SR_NODISCARD bool* GetBool() const { return (bool*)GetRawValue(); }
        SR_NODISCARD float_t* GetFloat() const { return (float_t*)GetRawValue(); }
        SR_NODISCARD double_t* GetDouble() const { return (double_t*)GetRawValue(); }
        SR_NODISCARD std::string* GetString() const { return (std::string*)GetRawValue(); }

        SR_NODISCARD int8_t* GetInt8() const { return (int8_t*)GetRawValue(); }
        SR_NODISCARD int16_t* GetInt16() const { return (int16_t*)GetRawValue(); }
        SR_NODISCARD int32_t* GetInt32() const { return (int32_t*)GetRawValue(); }
        SR_NODISCARD int64_t* GetInt64() const { return (int64_t*)GetRawValue(); }

        SR_NODISCARD uint8_t* GetUInt8() const { return (uint8_t*)GetRawValue(); }
        SR_NODISCARD uint16_t* GetUInt16() const { return (uint16_t*)GetRawValue(); }
        SR_NODISCARD uint32_t* GetUInt32() const { return (uint32_t*)GetRawValue(); }
        SR_NODISCARD uint64_t* GetUInt64() const { return (uint64_t*)GetRawValue(); }

        SR_NODISCARD int64_t* GetEnum() const { return (int64_t*)GetRawValue(); }

    public:
        virtual DataType* SetRawValue(void* pValue) { return this; }
        template<typename T> DataType* SetCustomValue(const T& value) { return SetRawValue((void*)&value); }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeNone : public DataType {
        SR_LM_REGISTER_TYPE(DataTypeNone, None);
    public:
        SR_NODISCARD DataType* Copy() const override { return new DataTypeNone(); }
        void CopyTo(DataType* pData) const override { }
        void Reset() override { }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeInt8 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeInt8, DataType, Int8, int8_t, 0)
    };

    class DataTypeInt16 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeInt16, DataType, Int16, int16_t, 0)

    };

    class DataTypeInt32 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeInt32, DataType, Int32, int32_t, 0)
    };

    class DataTypeInt64 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeInt64, DataType, Int64, int64_t, 0)
    };

    class DataTypeUInt8 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeUInt8, DataType, UInt8, uint8_t, 0)
    };

    class DataTypeUInt16 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeUInt16, DataType, UInt16, uint16_t, 0)
    };

    class DataTypeUInt32 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeUInt32, DataType, UInt32, uint32_t, 0)
    };

    class DataTypeUInt64 : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeUInt64, DataType, UInt64, uint64_t, 0)
    };

    class DataTypeBool : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeBool, DataType, Bool, bool, false)
    };

    class DataTypeFloat : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeFloat, DataType, Float, float_t, 0.f)
    };

    class DataTypeDouble : public DataType {
        SR_LM_REGISTER_TYPE_FULL(DataTypeDouble, DataType, Double, double_t, 0.0)
    };

    class DataTypeString : public DataType {
        SR_LM_REGISTER_TYPE_FULL_MOVE(DataTypeString, DataType, String, std::string, std::string())
    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeEnum : public DataTypeInt64 {
        SR_LM_REGISTER_BASE(DataTypeEnum, Enum)
    public:
        DataTypeEnum() = default;

        explicit DataTypeEnum(int64_t value, EnumReflector* pReflector)
            : DataTypeInt64(value)
            , m_reflector(pReflector)
        { }

        explicit DataTypeEnum(EnumReflector* pReflector)
            : DataTypeInt64()
            , m_reflector(pReflector)
        { }

    public:
        SR_NODISCARD Hash GetHashName() const noexcept override;
        SR_NODISCARD std::string GetName() const noexcept override;
        SR_NODISCARD EnumReflector* GetReflector() const { return m_reflector; }

        SR_NODISCARD DataType* Copy() const override {
            return new DataTypeEnum(m_value, m_reflector);
        }

        void SetReflector(EnumReflector* pReflector) { m_reflector = pReflector; }

    private:
        EnumReflector* m_reflector = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    SR_ENUM_NS_CLASS_T(FlowState, uint8_t,
        NotAvailable, Available, Executed
    );


    class DataTypeFlow : public DataTypeEnum {
        SR_LM_REGISTER_TYPE(DataTypeFlow, Flow)

        explicit DataTypeFlow(FlowState flowState)
            : DataTypeEnum(static_cast<int64_t>(flowState), SR_UTILS_NS::EnumReflector::GetReflector<FlowState>())
        { }

        DataTypeFlow()
            : DataTypeFlow(FlowState::NotAvailable)
        { }

        SR_NODISCARD DataType* Copy() const override {
            return new DataTypeFlow(static_cast<FlowState>(*GetEnum()));
        }
    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeArray : public DataType {
        SR_LM_REGISTER_TYPE_NO_META(DataTypeArray, Array)
    public:
        DataTypeArray();
        ~DataTypeArray() override;

    public:
        void CopyTo(DataType* pData) const override;
        void SetType(DataType* pData);
        void Reset() override;

        SR_NODISCARD DataType* Copy() const override;
        SR_NODISCARD Meta GetMeta() const noexcept override;

    private:
        std::vector<DataType*> m_value;
        DataType* m_type = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeStruct : public DataType {
        SR_LM_REGISTER_TYPE(DataTypeStruct, Struct)
    public:
        DataTypeStruct() = default;

        explicit DataTypeStruct(Hash name)
            : DataType()
            , m_name(name)
        { }

        ~DataTypeStruct() override;

    public:
        void CopyTo(DataType* pData) const override;
        void AddVariable(Hash name, DataType* pData);
        void AddVariable(const std::string& name, DataType* pData);
        void Reset() override;
        void SetStructHashName(Hash hashName) { m_name = hashName; }

        SR_NODISCARD DataType* Copy() const override;
        SR_NODISCARD std::vector<DataType*> GetMetaData() const override;
        SR_NODISCARD const std::map<Hash, DataType*>& GetVariables() const { return m_variables; };
        SR_NODISCARD Hash GetStructName() const { return m_name; };

    private:
        Hash m_name = SR_UINT64_MAX;
        std::map<Hash, DataType*> m_variables;

    };
}

#endif //SR_ENGINE_DATATYPE_H
