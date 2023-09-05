//
// Created by Monika on 30.08.2023.
//

#include <Utils/SRLM/LogicalNode.h>

namespace SR_SRLM_NS {
    LogicalNode::~LogicalNode() {
        for (auto&& pin : m_inputs) {
            delete pin.pData;
        }

        for (auto&& pin : m_outputs) {
            delete pin.pData;
        }
    }

    void LogicalNode::SetInput(const DataType* pInput, uint8_t index) {
        if (!pInput) {
            m_status |= LogicalNodeStatus::InputNullPtr;
            return;
        }

        if (index >= m_inputs.size()) {
            m_status |= LogicalNodeStatus::InputRangeError;
            return;
        }

        auto&& pSelfInput = m_inputs.at(index).pData;
        if (pSelfInput->GetMeta() != pInput->GetMeta()) {
            m_status |= LogicalNodeStatus::InputTypeError;
            return;
        }

        pInput->CopyTo(pSelfInput);
    }

    void LogicalNode::Reset() {
        for (auto&& pin : m_inputs) {
            pin.pData->Reset();
        }

        for (auto&& pin : m_outputs) {
            pin.pData->Reset();
        }

        m_status = LogicalNodeStatus::None;
    }

    const DataType* LogicalNode::GetOutput(uint8_t index) {
        if (index >= m_inputs.size()) {
            m_status |= LogicalNodeStatus::OutputRangeError;
            return nullptr;
        }

        if (m_status & LogicalNodeStatus::ErrorStatus) {
            return nullptr;
        }

        return m_inputs.at(index).pData;
    }

    void LogicalNode::MarkDirty() {
        if (GetType() == LogicalNodeType::Compute || GetType() == LogicalNodeType::Connector) {
            for (auto&& pin : m_outputs) {
                pin.pNode->MarkDirty();
            }
        }
    }

    LogicalNode* LogicalNode::GetOutputNode(uint8_t index) {
        if (index >= m_inputs.size()) {
            m_status |= LogicalNodeStatus::OutputRangeError;
            return nullptr;
        }

        return m_inputs.at(index).pNode;
    }

    void LogicalNode::AddInputData(DataType* pData, uint64_t hashName) {
        auto&& pin = NodePin();
        pin.pData = pData;
        pin.hashName = hashName;
        m_inputs.emplace_back(pin);
    }

    void LogicalNode::AddOutputData(DataType* pData, uint64_t hashName) {
        auto&& pin = NodePin();
        pin.pData = pData;
        pin.hashName = hashName;
        m_outputs.emplace_back(pin);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    const DataType* IComputeNode::GetOutput(uint8_t index) {
        if (m_dirty)
        {
            Compute();

            if (HasErrors()) {
                m_dirty = false;
                m_status ^= LogicalNodeStatus::ComputeError;
            }
            else {
                m_status |= LogicalNodeStatus::ComputeError;
                return nullptr;
            }
        }

        return LogicalNode::GetOutput(index);
    }

    void IComputeNode::MarkDirty() {
        m_dirty = true;
        LogicalNode::MarkDirty();
    }
}