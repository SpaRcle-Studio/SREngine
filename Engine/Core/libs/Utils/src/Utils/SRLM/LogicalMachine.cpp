//
// Created by Monika on 15.08.2023.
//

#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/Xml.h>

namespace SR_SRLM_NS {
    LogicalMachine* LogicalMachine::Load(const SR_UTILS_NS::Path& path) {
        auto&& xmlDocument = SR_XML_NS::Document::Load(path);
        if (!xmlDocument) {
            SR_ERROR("LogicalMachine::Load() : failed to load xml!n\n\tPath: " + path.ToStringRef());
            return nullptr;
        }

        auto&& xmlLogicalMachine = xmlDocument.Root().GetNode("LogicalMachine");

        std::map<uint64_t, LogicalNode*> nodes;

        auto&& pLogicalMachine = new LogicalMachine();

        auto&& xmlNodes = xmlLogicalMachine.GetNode("Nodes");
        for (auto&& xmlNode : xmlNodes.GetNodes()) {
            auto&& uid = xmlNode.GetAttribute("UID").ToUInt64();

            if (auto&& pLogicalNode = SR_SRLM_NS::LogicalNode::LoadXml(xmlNode)) {
                pLogicalMachine->AddNode(pLogicalNode);
                nodes[uid] = pLogicalNode;
            }
        }

        auto&& xmlLinks = xmlLogicalMachine.GetNode("Links");
        for (auto&& xmlLink : xmlLinks.GetNodes()) {
            auto&& startNodeId = xmlLink.GetAttribute("SN").ToUInt64();
            auto&& endNodeId = xmlLink.GetAttribute("EN").ToUInt64();

            auto&& startPinIndex = xmlLink.GetAttribute("SP").ToUInt64();
            auto&& endPinIndex = xmlLink.GetAttribute("EP").ToUInt64();

            nodes[startNodeId]->GetOutputs()[startPinIndex].pNode = nodes[endNodeId];
            nodes[startNodeId]->GetOutputs()[startPinIndex].pinIndex = endNodeId;

            nodes[endNodeId]->GetInputs()[endPinIndex].pNode = nodes[startNodeId];
            nodes[endNodeId]->GetInputs()[endPinIndex].pinIndex = startNodeId;
        }

        return pLogicalMachine;
    }

    void LogicalMachine::Update(float_t dt) {
        for (m_currentNode = 0; m_currentNode < m_active.size(); ++m_currentNode) {
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

    void LogicalMachine::AddNode(LogicalNode* pNode) {
        m_nodes.emplace_back(pNode);

        if (pNode->IsEntryPoint()) {
            auto&& name = pNode->GetName();

            if (m_entryPoints.count(name) == 0) {
                m_entryPoints.insert(std::make_pair(name, pNode));
            }
            else {
                SR_ERROR("LogicalMachine::AddNode() : entry-point \"" + name + "\" already exists!");
            }
        }
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