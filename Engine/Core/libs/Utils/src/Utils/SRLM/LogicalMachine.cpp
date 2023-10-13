//
// Created by Monika on 15.08.2023.
//

#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/Xml.h>

namespace SR_SRLM_NS {
    LogicalMachine::LogicalMachine()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(LogicalMachine))
    { }

    LogicalMachine::~LogicalMachine() {
        Clear();
    }

    void LogicalMachine::UpdateMachine(float_t dt) {
        for (m_currentNode = 0; m_currentNode < m_active.size(); ++m_currentNode) {
            while (Execute(dt));

            if (!GetCurrentNode()) {
                m_active.erase(m_active.begin() + m_currentNode);
                --m_currentNode;
            }
        }
    }

    bool LogicalMachine::Init() {
        for (auto&& [name, pNode] : m_entryPoints) {
            ActiveNodeInfo info;
            info.pNode = pNode;
            info.pFromPin = nullptr;
            m_active.emplace_back(info);
        }

        return true;
    }

    void LogicalMachine::Optimize() {
        for (auto pIt = m_nodes.begin(); pIt != m_nodes.end(); ) {
            auto&& pNode = *pIt;

            if (pNode->GetType() != LogicalNodeType::Connector) {
                ++pIt;
                continue;
            }

            for (auto&& inputPin : pNode->GetInputs()) {
                for (auto&& inputConnection : inputPin.connections) {
                    inputConnection.pNode->RemoveOutputConnection(pNode, inputConnection.pinIndex);

                    for (auto&& outputPin : pNode->GetOutputs()) {
                        for (auto&& outputConnection : outputPin.connections) {
                            outputConnection.pNode->RemoveInputConnection(pNode, outputConnection.pinIndex);
                            outputConnection.pNode->AddInputConnection(inputConnection.pNode, inputConnection.pinIndex, outputConnection.pinIndex);
                            inputConnection.pNode->AddOutputConnection(outputConnection.pNode, outputConnection.pinIndex, inputConnection.pinIndex);
                        }
                    }
                }
            }

            delete pNode;
            pIt = m_nodes.erase(pIt);
        }
    }

    void LogicalMachine::AddNode(LogicalNode* pNode) {
        m_nodes.emplace_back(pNode);

        pNode->SetMachine(this);
        pNode->SetNodeIndex(m_nodes.size() - 1);

        if (pNode->IsEntryPoint()) {
            auto&& name = pNode->GetNodeName();

            if (m_entryPoints.count(name) == 0) {
                m_entryPoints.insert(std::make_pair(name, pNode));
            }
            else {
                SR_ERROR("LogicalMachine::AddNode() : entry-point \"" + name + "\" already exists!");
            }
        }
    }

    bool LogicalMachine::Load() {
        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(GetResourcePath());
        auto&& xmlDocument = SR_XML_NS::Document::Load(path);
        if (!xmlDocument) {
            SR_ERROR("LogicalMachine::Load() : failed to load xml!\n\tPath: " + path.ToStringRef());
            return false;
        }

        auto&& xmlLogicalMachine = xmlDocument.Root().GetNode("LogicalMachine");

        std::map<uint64_t, LogicalNode*> nodes;

        auto&& xmlNodes = xmlLogicalMachine.GetNode("Nodes");
        for (auto&& xmlNode : xmlNodes.GetNodes()) {
            auto&& uid = xmlNode.GetAttribute("UID").ToUInt64();

            if (auto&& pLogicalNode = SR_SRLM_NS::LogicalNode::LoadXml(xmlNode)) {
                AddNode(pLogicalNode);
                nodes[uid] = pLogicalNode;
            }
        }

        auto&& xmlLinks = xmlLogicalMachine.GetNode("Links");
        for (auto&& xmlLink : xmlLinks.GetNodes()) {
            auto&& startNodeId = xmlLink.GetAttribute("SN").ToUInt64();
            auto&& endNodeId = xmlLink.GetAttribute("EN").ToUInt64();

            if (nodes.count(startNodeId) == 0 || nodes.count(endNodeId) == 0) {
                SRHalt("Node not found!");
                continue;
            }

            auto&& startPinIndex = xmlLink.GetAttribute("SP").ToUInt();
            auto&& endPinIndex = xmlLink.GetAttribute("EP").ToUInt();

            nodes[startNodeId]->AddOutputConnection(nodes[endNodeId], endPinIndex, startPinIndex);
            nodes[endNodeId]->AddInputConnection(nodes[startNodeId], startPinIndex, endPinIndex);
        }

        Optimize();

        return Super::Load();
    }

    void LogicalMachine::Clear() {
        for (auto&& pNode : m_nodes) {
            delete pNode;
        }

        m_currentNode = 0;

        m_nodes.clear();
        m_active.clear();
        m_entryPoints.clear();
    }

    bool LogicalMachine::Unload() {
        Clear();
        return Super::Unload();
    }

    bool LogicalMachine::Execute(float_t dt) {
        if (!GetCurrentNode()) {
            return false;
        }

        if (GetCurrentNode()->GetType() == LogicalNodeType::Compute) {
            SRHalt("Compute node in queue!");
            return false;
        }

        if (auto&& pPin = GetCurrentPin()) {
            *pPin->pData->GetEnum() = static_cast<int64_t>(FlowState::Executed);
        }

        ActiveNodeInfo info;
        uint32_t offset = m_currentNode + 1;

        if (GetCurrentNode()->GetType() == LogicalNodeType::Executable) {
            auto&& pExecutable = dynamic_cast<IExecutableNode*>(GetCurrentNode());
            if (!pExecutable) {
                return false;
            }

            pExecutable->Execute(dt);

            if (pExecutable->HasErrors()) {
                return false;
            }

            bool needContinue = pExecutable->IsNeedRepeat();

            for (auto&& pin : pExecutable->GetOutputs()) {
                if (pin.pData->GetClass() != DataTypeClass::Flow) {
                    continue;
                }

                if (*pin.pData->GetEnum() == static_cast<int64_t>(FlowState::NotAvailable)) {
                    continue;
                }

                if (!needContinue) {
                    needContinue = true;
                    SetCurrentNode(pin.GetFirstNode(), &pin);
                }
                else {
                    info.pNode = pin.GetFirstNode();
                    info.pFromPin = &pin;
                    m_active.insert(m_active.begin() + offset, info);
                    ++offset;
                }
            }

            if (pExecutable->IsNeedPostRepeat()) {
                if (needContinue) {
                    info.pNode = pExecutable;
                    info.pFromPin = nullptr;
                    m_active.insert(m_active.begin() + offset, info);
                }
                needContinue = true;
            }

            return needContinue;
        }

        SRHalt("Unresolved behaviour!");

        return false;
    }

    IResource* LogicalMachine::CopyResource(SR_UTILS_NS::IResource* pDestination) const {
        return nullptr;
    }

    LogicalNode* LogicalMachine::GetCurrentNode() const {
        if (m_currentNode >= m_active.size()) {
            return nullptr;
        }
        return m_active[m_currentNode].pNode;
    }

    LogicalNode::NodePin* LogicalMachine::GetCurrentPin() const {
        if (m_currentNode >= m_active.size()) {
            return nullptr;
        }
        return m_active[m_currentNode].pFromPin;
    }

    void LogicalMachine::SetCurrentNode(LogicalNode* pNode, LogicalNode::NodePin* pFromPin) {
        if (m_currentNode < m_active.size()) {
            m_active[m_currentNode].pNode = pNode;
            m_active[m_currentNode].pFromPin = pFromPin;
        }
    }
}