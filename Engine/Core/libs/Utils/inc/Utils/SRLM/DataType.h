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
        None, Default, Enum, Struct, Array, Map, Set
    );

    class DataType : SR_UTILS_NS::NonCopyable {
    public:
        using Meta = uint64_t;
        using Hash = uint64_t;

    public:
        SR_NODISCARD virtual std::vector<DataType*> GetMetaData() const { std::vector<DataType*>(); }
        SR_NODISCARD virtual DataType* Copy() const = 0;
        SR_NODISCARD virtual Meta GetMeta() const noexcept = 0;
        SR_NODISCARD virtual std::string GetName() const noexcept = 0;
        SR_NODISCARD virtual Hash GetHashName() const noexcept = 0;
        SR_NODISCARD virtual DataTypeClass GetClass() const noexcept { return DataTypeClass::Default; }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeNone : public DataType {
        SR_LM_REGISTER_TYPE(None);
    public:
        SR_NODISCARD DataType* Copy() const override { return new DataTypeNone(); }
        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::None; }

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
        SR_LM_REGISTER_TYPE(Enum)
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

        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::Enum; }

    private:
        EnumReflector* m_reflector = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeArray : public DataType {
        SR_LM_REGISTER_TYPE_NO_META(Array)
    public:
        DataTypeArray();
        ~DataTypeArray() override;

    public:
        void SetType(DataType* pData);

        SR_NODISCARD Meta GetMeta() const noexcept override;
        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::Array; }

    private:
        std::vector<DataType*> m_value;
        DataType* m_type = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class DataTypeStruct : public DataType {
        SR_LM_REGISTER_TYPE(Struct)
    public:
        explicit DataTypeStruct(Hash name)
            : DataType()
        { }

        ~DataTypeStruct() override;

    public:
        SR_NODISCARD DataType* Copy() const override;
        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::Struct; }
        SR_NODISCARD std::vector<DataType*> GetMetaData() const override;
        void AddVariable(Hash name, DataType* pData);

    private:
        Hash m_name = SR_UINT64_MAX;
        std::map<Hash, DataType*> m_variables;

    };
}

#endif //SRENGINE_DATATYPE_H
