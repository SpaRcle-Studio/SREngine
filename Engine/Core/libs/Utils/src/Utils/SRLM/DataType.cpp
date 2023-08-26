//
// Created by Monika on 25.08.2023.
//

#include <Utils/SRLM/DataType.h>

namespace SR_SRLM_NS {
    bool DataTypeAllocator::Register(DataTypeClass dataTypeClass, Hash hashName, Allocator allocator) {
        m_allocators[static_cast<uint32_t>(dataTypeClass)] = std::move(allocator);
        m_hashes[static_cast<uint32_t>(dataTypeClass)] = hashName;
        return true;
    }

    DataType* DataTypeAllocator::Allocate(DataTypeClass dataTypeClass) {
        auto&& index = static_cast<uint32_t>(dataTypeClass);
        if (m_allocators[index]) {
            return m_allocators[index]();
        }
        return nullptr;
    }

    DataType* DataTypeAllocator::Allocate(DataTypeAllocator::Hash hashName) {
        for (uint32_t i = 0; i < EnumMax; ++i) {
            if (m_hashes[i] == hashName) {
                return Allocate(static_cast<DataTypeClass>(i));
            }
        }
        return nullptr;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    DataType* DataTypeStruct::Copy() const {
        auto&& pStruct = new DataTypeStruct(m_name);

        for (auto&& [hash, pData] : m_variables) {
            pStruct->m_variables[hash] = pData->Copy();
        }

        return pStruct;
    }

    DataTypeStruct::~DataTypeStruct() {
        for (auto&& [hash, pData] : m_variables) {
            delete pData;
        }
    }

    void DataTypeStruct::AddVariable(Hash name, DataType* pData) {
        SRAssert(m_variables.count(name) == 0);
        m_variables[name] = pData;
    }

    std::vector<DataType*> DataTypeStruct::GetMetaData() const {
        std::vector<DataType*> data;

        data.reserve(m_variables.size());

        for (auto&& [hash, pData] : m_variables) {
            data.emplace_back(pData);
        }

        return data;
    }

    DataTypeArray::DataTypeArray()
        : DataType()
    {
        SetType(new DataTypeNone());
    }

    DataTypeArray::~DataTypeArray() {
        SetType(nullptr);
    }

    DataType::Meta DataTypeArray::GetMeta() const noexcept {
        return SR_COMBINE_HASHES(GetHashName(), m_type->GetHashName());
    }

    void DataTypeArray::SetType(DataType* pData) {
        SR_SAFE_DELETE_PTR(m_type);
        m_type = pData;
        for (auto&& pValue : m_value) {
            delete pValue;
        }
        m_value.clear();
    }

    DataType* DataTypeArray::Copy() const {
        auto&& pData = AllocateNew();

        pData->m_type = m_type ? m_type->Copy() : nullptr;
        pData->m_value.reserve(m_value.size());

        for (auto&& pValue : m_value) {
            pData->m_value.emplace_back(pValue->Copy());
        }

        return pData;
    }
}