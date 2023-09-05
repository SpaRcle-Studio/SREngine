//
// Created by Monika on 15.08.2023.
//

#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/Xml.h>

namespace SR_SRLM_NS {
    void LogicalMachine::Update(float_t dt) {
        for (m_currentNode = 0; m_currentNode < m_active.size(); ++m_currentNode)
        {
            LogicalNode* pNode = m_active[m_currentNode];

            while (Execute(pNode, dt));

            if (!pNode) {
                m_active.erase(m_active.begin() + m_currentNode);
                --m_currentNode;
            }
        }
    }

    bool LogicalMachine::Init() {
        for (auto&& [name, pNode] : m_entryPoints) {
            m_active.emplace_back(pNode);
        }

        return true;
    }

    bool LogicalMachine::Execute(LogicalNode*& pNode, float_t dt) {
        if (!pNode) {
            return false;
        }

        if (pNode->GetType() == LogicalNodeType::Compute) {
            SRHalt("Compute node in queue!");
            return false;
        }

        if (pNode->GetType() == LogicalNodeType::Connector) {
            pNode = pNode->GetOutputNode(0);
            return true;
        }

        if (pNode->GetType() == LogicalNodeType::Executable) {
            auto&& pExecutable = dynamic_cast<IExecutableNode*>(pNode);
            if (!pExecutable) {
                return false;
            }

            pExecutable->Execute(dt);

            if (pExecutable->HasErrors()) {
                return false;
            }

            bool needContinue = pExecutable->IsNeedRepeat();

            for (auto&& pin : pExecutable->GetOutputs()) {
                if (pin.pData->GetClass() != DataTypeClass::Flow || !(*pin.pData->GetBool())) {
                    continue;
                }

                if (!needContinue) {
                    needContinue = true;
                    pNode = pin.pNode;
                }
                else {
                    m_active.insert(m_active.begin() + m_currentNode, pin.pNode);
                }
            }

            if (pExecutable->IsNeedPostRepeat()) {
                if (needContinue) {
                    m_active.insert(m_active.begin() + m_currentNode, pExecutable);
                }
                needContinue = true;
            }

            return needContinue;
        }

        SRHalt("Unresolved behaviour!");

        return false;
    }
}