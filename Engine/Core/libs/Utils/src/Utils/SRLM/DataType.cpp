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
}