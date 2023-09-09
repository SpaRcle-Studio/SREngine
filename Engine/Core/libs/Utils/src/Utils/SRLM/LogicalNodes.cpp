//
// Created by Monika on 05.09.2023.
//

#include <Utils/SRLM/LogicalNodes.h>
#include <Utils/SRLM/DataType.h>

#define SR_LM_NODE_OPERATOR_CALCULATION(pOutput, pFirst, pSecond, type, operator)                                       \
    pOutput->SetCustomValue(*pFirst->Get##type() operator *pSecond->Get##type());                                       \

#define SR_LM_NODE_NUMERIC_OPERATORS_CALCULATION(pOut, pFirst, pSecond, op)                                             \
    switch (pOut->GetClass()) {                                                                                         \
    case SR_SRLM_NS::DataTypeClass::Int8: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Int8, op); break;      \
    case SR_SRLM_NS::DataTypeClass::Int16: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Int16, op); break;    \
    case SR_SRLM_NS::DataTypeClass::Int32: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Int32, op); break;    \
    case SR_SRLM_NS::DataTypeClass::Int64: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Int64, op); break;    \
    case SR_SRLM_NS::DataTypeClass::UInt8: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, UInt8, op); break;    \
    case SR_SRLM_NS::DataTypeClass::UInt16: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, UInt16, op); break;  \
    case SR_SRLM_NS::DataTypeClass::UInt32: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, UInt32, op); break;  \
    case SR_SRLM_NS::DataTypeClass::UInt64: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, UInt64, op); break;  \
    default:                                                                                                            \
        SRHalt("Unknown type!");                                                                                        \
        break;                                                                                                          \
    }                                                                                                                   \

#define SR_LM_NODE_FLOATING_OPERATORS_CALCULATION(pOut, pFirst, pSecond, op)                                            \
    switch (pOut->GetClass()) {                                                                                         \
    case SR_SRLM_NS::DataTypeClass::Float: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Float, op); break;    \
    case SR_SRLM_NS::DataTypeClass::Double: SR_LM_NODE_OPERATOR_CALCULATION(pOut, pFirst, pSecond, Double, op); break;  \
    default:                                                                                                            \
        SRHalt("Unknown type!");                                                                                        \
        break;                                                                                                          \
    }                                                                                                                   \

namespace SR_SRLM_NS {
    void DebugPrintNode::Execute(float_t dt) {
        SR_UTILS_NS::Debug::Instance().Print(
            *m_inputs.at(1).pData->GetString(),
            static_cast<SR_UTILS_NS::DebugLogType>(*m_inputs.at(2).pData->GetEnum())
        );
        *m_outputs.at(0).pData->GetBool() = true;
        m_status |= LogicalNodeStatus::Success;
    }

    void DebugPrintNode::InitNode() {
        IExecutableNode::InitNode();

        AddInputData<DataTypeFlow>();

        AddInputData<DataTypeString>(SR_HASH_STR_REGISTER("Msg"));

        AddInputData(new DataTypeEnum(
                static_cast<uint64_t>(SR_UTILS_NS::DebugLogType::Log),
                SR_UTILS_NS::EnumReflector::GetReflector<SR_UTILS_NS::DebugLogType>()
        ), SR_HASH_STR_REGISTER("Type"));

        AddOutputData<DataTypeFlow>();
    }

    void DebugPrintNode::InitValues() {
        IExecutableNode::InitValues();
        m_inputs.at(1).pData->SetCustomValue<std::string>("Hello World!");
    }

    void StartNode::InitNode() {
        IExecutableNode::InitNode();
        AddOutputData<DataTypeFlow>();
    }

    void StartNode::Execute(float_t dt) {
        *m_outputs.at(0).pData->GetBool() = true;
        m_status |= LogicalNodeStatus::Success;
    }

    void PlusNode::Compute() {
        SR_LM_NODE_NUMERIC_OPERATORS_CALCULATION(m_outputs[0].pData, m_inputs[0].pData, m_inputs[1].pData, +);
    }

    void ConstructorNode::Compute() {
        m_inputs[0].pData->CopyTo(m_outputs[0].pData);
        m_status |= LogicalNodeStatus::Success;
        m_dirty = false;
    }

    void ConstructorNode::InitNode() {
        AddInputData(DataTypeAllocator::Instance().Allocate(m_initTypeHashName));
        AddOutputData(DataTypeAllocator::Instance().Allocate(m_initTypeHashName));
        IComputeNode::InitNode();
    }

    uint64_t ConstructorNode::GetHashName() const noexcept {
        auto&& pOutput = m_outputs[0].pData;
        return pOutput->GetHashName();
    }

    std::string ConstructorNode::GetName() const noexcept {
        return SR_HASH_TO_STR(GetHashName());
    }
}
