//
// Created by Monika on 05.09.2023.
//

#include <Utils/SRLM/LogicalNodes.h>
#include <Utils/SRLM/DataType.h>

namespace SR_SRLM_NS {
    DebugPrintNode::DebugPrintNode()
        : Base()
    {
        AddInputData<DataTypeFlow>();

        AddInputData<DataTypeString>(SR_HASH_STR_REGISTER("Msg"));

        AddInputData(new DataTypeEnum(
            static_cast<uint64_t>(SR_UTILS_NS::DebugLogType::Log),
            SR_UTILS_NS::EnumReflector::GetReflector<SR_UTILS_NS::DebugLogType>()
        ), SR_HASH_STR_REGISTER("Type"));

        AddOutputData<DataTypeFlow>();
    }

    void DebugPrintNode::Execute(float_t dt) {
        SR_UTILS_NS::Debug::Instance().Print(
            *m_inputs.at(1).pData->GetString(),
            static_cast<SR_UTILS_NS::DebugLogType>(*m_inputs.at(2).pData->GetEnum())
        );
        *m_outputs.at(0).pData->GetBool() = true;
        m_status |= LogicalNodeStatus::Success;
    }

    void DebugPrintNode::InitDefault() {
        m_inputs.at(1).pData->SetCustomValue<std::string>("Hello World!");
    }

    StartNode::StartNode()
        : Base()
    {
        AddOutputData<DataTypeFlow>();
    }

    void StartNode::Execute(float_t dt) {
        *m_outputs.at(0).pData->GetBool() = true;
        m_status |= LogicalNodeStatus::Success;
    }
}
