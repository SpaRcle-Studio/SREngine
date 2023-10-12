//
// Created by innerviewer on 9/9/2023.
//

#include <Utils/SRLM/ConvertorNode.h>

namespace SR_SRLM_NS {
    void ConvertorNode::InitNode() {
        AddInputData(DataTypeAllocator::Instance().Allocate(m_initInputTypeHashName));
        AddOutputData(DataTypeAllocator::Instance().Allocate(m_initOutputTypeHashName));

        LogicalNode::InitNode();
    }

    std::string ConvertorNode::GetInputTypeName() const noexcept {
        return SR_HASH_TO_STR(GetInputHashName());
    }

    std::string ConvertorNode::GetOutputTypeName() const noexcept {
        return SR_HASH_TO_STR(GetOutputHashName());
    }

    uint64_t ConvertorNode::GetInputHashName() const noexcept {
        auto&& pInput = m_inputs[0].pData;
        return pInput->GetHashName();
    }

    uint64_t ConvertorNode::GetOutputHashName() const noexcept {
        auto&& pOutput = m_outputs[0].pData;
        return pOutput->GetHashName();
    }

    void ConvertorNode::Execute(float_t dt) {
        switch (m_outputs[0].pData->GetClass()) {
            case DataTypeClass::String:
                m_outputs[0].pData->SetCustomValue(ToString(CalcInput(0)));
                break;
            default:
                m_status |= LogicalNodeStatus::ComputeError;
                return;
        }

        m_status |= LogicalNodeStatus::Success;
        m_dirty = false;
    }

    std::string ConvertorNode::ToString(const DataType *pDataType) const {
        auto&& dataTypeClass = pDataType->GetClass();

        switch (dataTypeClass) {
            case DataTypeClass::UInt8: return SR_UTILS_NS::ToString(*pDataType->GetUInt8());
            case DataTypeClass::UInt16: return SR_UTILS_NS::ToString(*pDataType->GetUInt16());
            case DataTypeClass::UInt32: return SR_UTILS_NS::ToString(*pDataType->GetUInt32());
            case DataTypeClass::UInt64: return SR_UTILS_NS::ToString(*pDataType->GetUInt64());
            case DataTypeClass::Int8: return SR_UTILS_NS::ToString(*pDataType->GetInt8());
            case DataTypeClass::Int16: return SR_UTILS_NS::ToString(*pDataType->GetInt16());
            case DataTypeClass::Int32: return SR_UTILS_NS::ToString(*pDataType->GetInt32());
            case DataTypeClass::Int64: return SR_UTILS_NS::ToString(*pDataType->GetInt64());
            case DataTypeClass::Bool: return SR_UTILS_NS::ToString(*pDataType->GetBool());
            case DataTypeClass::Float: return SR_UTILS_NS::ToString(*pDataType->GetFloat());
            case DataTypeClass::Double: return SR_UTILS_NS::ToString(*pDataType->GetDouble());
            case DataTypeClass::String: return *pDataType->GetString();
            default:
                m_status |= LogicalNodeStatus::ComputeError;
                return std::string(); /// NOLINT
        }
    }

    uint64_t ConvertorNode::GetNodeHashName() const noexcept {
        return SR_HASH_STR_REGISTER(GetNodeName());
    }

    std::string ConvertorNode::GetNodeName() const noexcept {
        return std::string(GetInputTypeName() + " to " + GetOutputTypeName());
    }
}