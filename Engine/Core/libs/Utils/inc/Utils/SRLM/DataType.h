//
// Created by Monika on 25.08.2023.
//

#ifndef SRENGINE_DATATYPE_H
#define SRENGINE_DATATYPE_H

#include <Utils/SRLM/Utils.h>

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
        friend class SR_UTILS_NS::Singleton<DataTypeAllocator>;
        using Hash = uint64_t;
        using Allocator = SR_HTYPES_NS::Function<DataType*()>;
        static constexpr uint32_t EnumMax = static_cast<int>(DataTypeClass::DataTypeClassMAX);
    public:
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

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeNone : public DataType {
        SR_LM_REGISTER_TYPE(DataTypeNone, None);
    public:
        SR_NODISCARD DataType* Copy() const override { return new DataTypeNone(); }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeFlow : public DataType {
        SR_LM_REGISTER_TYPE(DataTypeFlow, Flow);
    public:
        SR_NODISCARD DataType* Copy() const override { return new DataTypeFlow(); }

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
        SR_LM_REGISTER_TYPE(DataTypeEnum, Enum)
    public:
        DataTypeEnum() = default;

        explicit DataTypeEnum(int64_t value, EnumReflector* pReflector)
            : DataTypeInt64(value)
            , m_reflector(pReflector)
        { }

    public:
        SR_NODISCARD DataType* Copy() const override {
            return new DataTypeEnum(m_value, m_reflector);
        }

    private:
        EnumReflector* m_reflector = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeArray : public DataType {
        SR_LM_REGISTER_TYPE_NO_META(DataTypeArray, Array)
    public:
        DataTypeArray();
        ~DataTypeArray() override;

    public:
        void SetType(DataType* pData);

        SR_NODISCARD DataType* Copy() const override;
        SR_NODISCARD Meta GetMeta() const noexcept override;
        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::Array; }

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
        { }

        ~DataTypeStruct() override;

    public:
        SR_NODISCARD DataType* Copy() const override;
        SR_NODISCARD std::vector<DataType*> GetMetaData() const override;
        void AddVariable(Hash name, DataType* pData);

    private:
        Hash m_name = SR_UINT64_MAX;
        std::map<Hash, DataType*> m_variables;

    };
}

#endif //SRENGINE_DATATYPE_H
