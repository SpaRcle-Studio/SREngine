//
// Created by Monika on 25.08.2023.
//

#include <Utils/SRLM/DataType.h>

namespace SR_SRLM_NS {
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
    }
}