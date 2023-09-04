//
// Created by Monika on 30.08.2023.
//

#include <Utils/SRLM/LogicalNode.h>

namespace SR_SRLM_NS {
    LogicalNode::~LogicalNode() {
        for (auto&& pData : m_inputs) {
            delete pData.second;
        }

        for (auto&& pData : m_outputs) {
            delete pData.second;
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

        auto&& pSelfInput = m_inputs.at(index).second;
        if (pSelfInput->GetMeta() != pInput->GetMeta()) {
            m_status |= LogicalNodeStatus::InputTypeError;
            return;
        }

        pInput->CopyTo(pSelfInput);
    }

    void LogicalNode::Reset() {
        for (auto&& pData : m_inputs) {
            pData.second->Reset();
        }

        for (auto&& pData : m_outputs) {
            pData.second->Reset();
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

        return m_inputs.at(index).second;
    }

    void LogicalNode::MarkDirty() {
        if (GetType() == LogicalNodeType::Compute || GetType() == LogicalNodeType::Connector) {
            for (auto&& [pNode, pData] : m_outputs) {
                pNode->MarkDirty();
            }
        }
    }

    LogicalNode* LogicalNode::GetOutputNode(uint8_t index) {
        if (index >= m_inputs.size()) {
            m_status |= LogicalNodeStatus::OutputRangeError;
            return nullptr;
        }

        return m_inputs.at(index).first;
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