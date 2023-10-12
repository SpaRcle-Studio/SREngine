//
// Created by Monika on 25.08.2023.
//

#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/DataTypeManager.h>

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

    void DataTypeStruct::Reset() {
        for (auto&& [name, pVariable] : m_variables) {
            pVariable->Reset();
        }
    }

    void DataTypeStruct::CopyTo(DataType* pData) const {
        if (auto&& pStruct = dynamic_cast<DataTypeStruct*>(pData)) {
            for (auto&& [hashName, pVar] : m_variables) {
                pVar->CopyTo(pStruct->m_variables.at(hashName));
            }
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

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
        Reset();
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

    void DataTypeArray::Reset() {
        for (auto&& pValue : m_value) {
            delete pValue;
        }
        m_value.clear();
    }

    void DataTypeArray::CopyTo(DataType* pData) const {
        if (auto&& pArray = dynamic_cast<DataTypeArray*>(pData)) {
            pArray->Reset();

            pArray->m_value.reserve(m_value.size());

            for (auto&& pValue : m_value) {
                pArray->m_value.emplace_back(pValue->Copy());
            }
        }
    }

    void DataType::SaveXml(SR_XML_NS::Node& xmlNode) {
        xmlNode.AppendAttribute("Name", GetHashName());
        xmlNode.AppendAttribute("Class", SR_UTILS_NS::EnumReflector::ToString(GetClass()));

        switch (GetClass()) {
            case DataTypeClass::Flow:
                break;
            case DataTypeClass::Enum: {
                if (auto&& pEnum = dynamic_cast<DataTypeEnum*>(this)) {
                    if (!pEnum->GetReflector()) {
                        SRHalt("Bad reflector!");
                        break;
                    }
                    xmlNode.AppendAttribute(*pEnum->GetEnum());
                }
                else {
                    SRHalt("Bad cast!");
                }
                break;
            }
            case DataTypeClass::Struct:
                if (auto&& pStruct = dynamic_cast<DataTypeStruct*>(this)) {
                    xmlNode.AppendAttribute("Struct", pStruct->GetStructName());
                    for (auto&& [hashName, pVar] : pStruct->GetVariables()) {
                        auto&& xmlVariable = xmlNode.AppendNode("Var");
                        xmlVariable.AppendAttribute("VarName", hashName);
                        pVar->SaveXml(xmlVariable);
                    }
                }
                else {
                    SRHalt("Bad cast!");
                }
                break;
            case SR_SRLM_NS::DataTypeClass::Array:
                break;
            case SR_SRLM_NS::DataTypeClass::Map:
                break;
            case SR_SRLM_NS::DataTypeClass::Set:
                break;
            case DataTypeClass::Bool: xmlNode.AppendAttribute(*GetBool()); break;
            case DataTypeClass::Float: xmlNode.AppendAttribute(*GetFloat()); break;
            case DataTypeClass::Double: xmlNode.AppendAttribute(*GetDouble()); break;
            case DataTypeClass::String: xmlNode.AppendAttribute(*GetString()); break;
            case DataTypeClass::Int8: xmlNode.AppendAttribute(*GetInt8()); break;
            case DataTypeClass::Int16: xmlNode.AppendAttribute(*GetInt16()); break;
            case DataTypeClass::Int32: xmlNode.AppendAttribute(*GetInt32()); break;
            case DataTypeClass::Int64: xmlNode.AppendAttribute(*GetInt64()); break;
            case DataTypeClass::UInt8: xmlNode.AppendAttribute(*GetUInt8()); break;
            case DataTypeClass::UInt16: xmlNode.AppendAttribute(*GetUInt16()); break;
            case DataTypeClass::UInt32: xmlNode.AppendAttribute(*GetUInt32()); break;
            case DataTypeClass::UInt64: xmlNode.AppendAttribute(*GetUInt64()); break;
            default:
                SRHalt("Unknown type! Type: " + SR_UTILS_NS::EnumReflector::ToString(GetClass()));
                break;
        }
    }

    DataType* DataType::LoadXml(const SR_XML_NS::Node& xmlNode) {
        if (!xmlNode.HasAttribute("Name")) {
            return nullptr;
        }

        auto&& hashName = xmlNode.GetAttribute("Name").ToUInt64();
        auto&& pDataType = SR_SRLM_NS::DataTypeManager::Instance().CreateByName(hashName);
        if (!pDataType) {
            SRHalt("Data type not found! Name: \"" + SR_HASH_TO_STR(hashName) + "\"");
            return nullptr;
        }

        auto&& dataTypeClass = SR_UTILS_NS::EnumReflector::FromString<DataTypeClass>(xmlNode.GetAttribute("Class").ToString());
        switch (dataTypeClass) {
            case DataTypeClass::Flow:
                break;
            case DataTypeClass::Enum: {
                auto&& enumValue = xmlNode.GetAttribute<int64_t>();

                auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(hashName);
                if (!pReflector) {
                    SRHalt("Reflector not found! Hash name: \"" + SR_UTILS_NS::ToString(hashName) + "\"");
                    delete pDataType;
                    return nullptr;
                }

                if (auto&& pEnum = dynamic_cast<DataTypeEnum*>(pDataType)) {
                    pEnum->SetReflector(pReflector);
                    pEnum->SetValue(enumValue);
                }
                else {
                    SRHalt("Bad cast!");
                    return nullptr;
                }
                break;
            }
            case DataTypeClass::Struct: {
                if (auto&& pStruct = dynamic_cast<DataTypeStruct*>(pDataType)) {
                    pStruct->SetStructHashName(xmlNode.GetAttribute("Struct").ToUInt64());
                    for (auto&& xmlVariable : xmlNode.GetNodes("Var")) {
                        auto&& varHashName = xmlVariable.GetAttribute("VarName").ToUInt64();
                        if (auto&& pVarData = LoadXml(xmlVariable)) {
                            pStruct->AddVariable(varHashName, pVarData);
                        }
                        else {
                            SRHalt("Failed to load variable! Hash name: " + SR_UTILS_NS::ToString(varHashName));
                        }
                    }
                }
                else {
                    SRHalt("Bad cast!");
                    return nullptr;
                }
                break;
            }
             case DataTypeClass::Array:
                 break; /// TODO
             case DataTypeClass::Map:
                 break; /// TODO
             case DataTypeClass::Set:
                 break; /// TODO
            case DataTypeClass::Bool: pDataType->SetCustomValue(xmlNode.GetAttribute<bool>()); break;
            case DataTypeClass::Float: pDataType->SetCustomValue(xmlNode.GetAttribute<float_t>()); break;
            case DataTypeClass::Double: pDataType->SetCustomValue(xmlNode.GetAttribute<double_t>()); break;
            case DataTypeClass::String: pDataType->SetCustomValue(xmlNode.GetAttribute<std::string>()); break;
            case DataTypeClass::Int8: pDataType->SetCustomValue(xmlNode.GetAttribute<int8_t>()); break;
            case DataTypeClass::Int16: pDataType->SetCustomValue(xmlNode.GetAttribute<int16_t>()); break;
            case DataTypeClass::Int32: pDataType->SetCustomValue(xmlNode.GetAttribute<int32_t>()); break;
            case DataTypeClass::Int64: pDataType->SetCustomValue(xmlNode.GetAttribute<int64_t>()); break;
            case DataTypeClass::UInt8: pDataType->SetCustomValue(xmlNode.GetAttribute<uint8_t>()); break;
            case DataTypeClass::UInt16: pDataType->SetCustomValue(xmlNode.GetAttribute<uint16_t>()); break;
            case DataTypeClass::UInt32: pDataType->SetCustomValue(xmlNode.GetAttribute<uint32_t>()); break;
            case DataTypeClass::UInt64: pDataType->SetCustomValue(xmlNode.GetAttribute<uint64_t>()); break;
            default:
                SRHalt("Unknown type! Type: " + SR_UTILS_NS::EnumReflector::ToString(dataTypeClass));
                break;
        }

        return pDataType;
    }

    DataTypeEnum::Hash DataTypeEnum::GetHashName() const noexcept {
        return m_reflector ? m_reflector->GetHashNameInternal() : HASH_NAME;
    }

    std::string DataTypeEnum::GetName() const noexcept {
        return m_reflector ? m_reflector->GetNameInternal() : NAME;
    }
}