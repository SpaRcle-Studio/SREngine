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
            *CalcInput(1)->GetString(),
            static_cast<SR_UTILS_NS::DebugLogType>(*CalcInput(2)->GetEnum())
        );
        *m_outputs.at(0).pData->GetEnum() = static_cast<int32_t>(FlowState::Available);
        Super::Execute(dt);
    }

    void DebugPrintNode::InitNode() {
        Super::InitNode();

        AddInputData<DataTypeFlow>();

        AddInputData<DataTypeString>(SR_HASH_STR_REGISTER("Msg"));

        AddInputData(new DataTypeEnum(
            static_cast<uint64_t>(SR_UTILS_NS::DebugLogType::Log),
            SR_UTILS_NS::EnumReflector::GetReflector<SR_UTILS_NS::DebugLogType>()
        ), SR_HASH_STR_REGISTER("Type"));

        AddOutputData<DataTypeFlow>();
    }

    void DebugPrintNode::InitValues() {
        Super::InitValues();
        m_inputs.at(1).pData->SetCustomValue<std::string>("Hello World!");
    }

    void StartNode::InitNode() {
        Super::InitNode();
        AddOutputData<DataTypeFlow>();
    }

    void StartNode::Execute(float_t dt) {
        *m_outputs.at(0).pData->GetEnum() = static_cast<int32_t>(FlowState::Available);
        Super::Execute(dt);
    }

    void PlusNode::Execute(float_t dt) {
        SR_LM_NODE_NUMERIC_OPERATORS_CALCULATION(m_outputs[0].pData, m_inputs[0].pData, m_inputs[1].pData, +);
        Super::Execute(dt);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void ConstructorNode::Execute(float_t dt) {
        CalcInput(0)->CopyTo(m_outputs[0].pData);
        m_dirty = false;
        Super::Execute(dt);
    }

    void ConstructorNode::InitNode() {
        AddInputData(DataTypeManager::Instance().CreateByName(m_initTypeHashName));
        AddOutputData(DataTypeManager::Instance().CreateByName(m_initTypeHashName));
        IComputeNode::InitNode();
    }

    uint64_t ConstructorNode::GetNodeHashName() const noexcept {
        auto&& pOutput = m_outputs[0].pData;
        return pOutput->GetHashName();
    }

    std::string ConstructorNode::GetNodeName() const noexcept {
        return SR_HASH_TO_STR(GetNodeHashName());
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void CreateStructNode::InitNode() {
        auto&& pStructInfo = SR_SRLM_NS::DataTypeManager::Instance().GetStruct(m_structHashName);
        if (pStructInfo) {
            for (auto&& [hashName, pVariable] : pStructInfo->GetVariables()) {
                AddInputData(pVariable->Copy(), hashName);
            }
            AddOutputData(pStructInfo->Copy());
        }

        Super::InitNode();
    }

    void CreateStructNode::Execute(float_t dt) {
        auto&& pStruct = dynamic_cast<DataTypeStruct*>(GetOutputs().at(0).pData);
        if (pStruct) {
            auto&& variables = pStruct->GetVariables();
            for (uint32_t i = 0; i < m_inputs.size(); ++i) {
                auto&& pInput = CalcInput(i);

                auto&& pIt = variables.find(m_inputs[i].hashName);
                if (pIt == variables.end()) {
                    SRHalt("Input not found!");
                    continue;
                }

                if (pIt->second->GetClass() != pInput->GetClass()) {
                    SRHalt("Input have incompatible class!");
                    continue;
                }

                pInput->CopyTo(pIt->second);
            }
        }

        Super::Execute(dt);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void BreakStructNode::InitNode() {
        auto&& pStructInfo = SR_SRLM_NS::DataTypeManager::Instance().GetStruct(m_structHashName);
        if (pStructInfo) {
            for (auto&& [hashName, pVariable] : pStructInfo->GetVariables()) {
                AddOutputData(pVariable->Copy(), hashName);
            }
            AddInputData(pStructInfo->Copy());
        }

        Super::InitNode();
    }

    void BreakStructNode::Execute(float_t dt) {
        auto&& pStruct = dynamic_cast<const DataTypeStruct*>(CalcInput(0));
        if (pStruct) {
            auto&& variables = pStruct->GetVariables();
            for (auto&& output : GetOutputs()) {
                auto&& pIt = variables.find(output.hashName);
                if (pIt == variables.end()) {
                    SRHalt("Output not found! Name: " + SR_HASH_TO_STR(output.hashName));
                    continue;
                }

                if (pIt->second->GetClass() != output.pData->GetClass()) {
                    SRHalt("Output have incompatible class! Name: " + SR_HASH_TO_STR(output.hashName));
                    continue;
                }

                pIt->second->CopyTo(output.pData);
            }
        }

        Super::Execute(dt);
    }

    void SequenceNode::Execute(float_t dt) {
        for (auto&& output : GetOutputs()) {
            if (*output.pData->GetEnum() != static_cast<int32_t>(FlowState::NotAvailable)) {
                continue;
            }
            *output.pData->GetEnum() = static_cast<int32_t>(FlowState::Available);
        }

        Super::Execute(dt);
    }

    void SequenceNode::InitNode() {
        Super::InitNode();

        AddInputData<DataTypeFlow>();

        AddOutputData<DataTypeFlow>(SR_HASH_STR_REGISTER("Then 0"));
        AddOutputData<DataTypeFlow>(SR_HASH_STR_REGISTER("Then 1"));
    }

    void BranchNode::Execute(float_t dt) {
        if (*CalcInput(1)->GetBool()) {
            *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::Available);
            *GetOutput(1)->GetEnum() = static_cast<int32_t>(FlowState::NotAvailable);
        }
        else {
            *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::NotAvailable);
            *GetOutput(1)->GetEnum() = static_cast<int32_t>(FlowState::Available);
        }

        Super::Execute(dt);
    }

    void BranchNode::InitNode() {
        Super::InitNode();

        AddInputData<DataTypeFlow>();
        AddInputData<DataTypeBool>(SR_HASH_STR_REGISTER("Condition"));

        AddOutputData<DataTypeFlow>(SR_HASH_STR_REGISTER("True"));
        AddOutputData<DataTypeFlow>(SR_HASH_STR_REGISTER("False"));
    }

    void StartResetNode::InitNode() {
        AddInputData<DataTypeFlow>();
        AddOutputData<DataTypeFlow>();
        Super::InitNode();
    }

    void StartResetNode::Execute(float_t dt) {
        *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::Available);
        Super::Execute(dt);
    }

    void EndResetNode::InitNode() {
        AddInputData<DataTypeFlow>();
        AddOutputData<DataTypeFlow>();
        Super::InitNode();
    }

    void EndResetNode::Execute(float_t dt) {
        *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::Available);
        Super::Execute(dt);
    }

    void SynchronizeNode::Execute(float_t dt) {
        for (uint32_t i = 0; i < m_inputs.size(); ++i) {
            if (*CalcInput(i)->GetEnum() != static_cast<int32_t>(FlowState::Executed)) {
                *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::NotAvailable);
                Super::Execute(dt);
                return;
            }
        }

        *GetOutput(0)->GetEnum() = static_cast<int32_t>(FlowState::Available);

        Super::Execute(dt);
    }

    void SynchronizeNode::InitNode() {
        Base::InitNode();

        AddInputData<DataTypeFlow>(SR_HASH_STR_REGISTER("If 0"));
        AddInputData<DataTypeFlow>(SR_HASH_STR_REGISTER("If 1"));

        AddOutputData<DataTypeFlow>();
    }
}
