//
// Created by Monika on 11.01.2022.
//

#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/NodeManager.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/Common/HashManager.h>

namespace SR_GRAPH_GUI_NS {
    Node::Node()
        : Node(std::string(), NodeType::None, ImColor(255, 255, 255, 255))
    { }

    Node::Node(SR_SRLM_NS::LogicalNode* pNode)
        : m_logicalNode(pNode)
    {
        m_name = pNode->GetName();

        if (pNode->GetType() == SR_SRLM_NS::LogicalNodeType::Executable) {
            m_type = NodeType::Blueprint;
        }
        else if (pNode->GetType() == SR_SRLM_NS::LogicalNodeType::Connector) {
            m_type = NodeType::Connector;
        }
        else {
            m_type = NodeType::Simple;
        }

        for (auto&& pin : pNode->GetInputs()) {
            AddInput(new Pin(SR_HASH_TO_STR(pin.hashName), pin.pData));
        }

        for (auto&& pin : pNode->GetOutputs()) {
            AddOutput(new Pin(SR_HASH_TO_STR(pin.hashName), pin.pData));
        }
    }

    Node::Node(const std::string& name)
        : Node(name, NodeType::None, ImColor(255, 255, 255, 255))
    { }

    Node::Node(const std::string& name, NodeType type)
        : Node(name, type, ImColor(255, 255, 255, 255))
    { }

    Node::Node(const std::string& name, ImColor color)
        : Node(name, NodeType::None, color)
    { }

    Node::Node(const std::string& name, NodeType type, ImColor color)
        : m_name(name)
        , m_color(color)
        , m_type(type)
    { }

    Node& Node::AddInput(Pin *pin) {
        pin->m_kind = PinKind::Input;
        pin->SetNode(this);

        m_inputs.emplace_back(pin);

        return *this;
    }

    Node& Node::AddOutput(Pin* pin) {
        pin->m_kind = PinKind::Output;
        pin->SetNode(this);

        if (const auto pinWidth = pin->GetWidth(); pinWidth > m_maxOutputWidth) {
            m_maxOutputWidth = pinWidth;
        }

        /// if (pin->GetType() == PinType::Delegate) {
        ///     m_hasOutputDelegates = true;
        /// }

        m_outputs.emplace_back(pin);

        return *this;
    }

    void Node::Draw(NodeBuilder* pBuilder, Pin* pNewLinkPin) {
        pBuilder->Begin(this);

        const bool isSimple = m_type == NodeType::Simple || m_type == NodeType::Connector;

        if (!isSimple) {
            pBuilder->Header(m_color);

            ImGui::Spring(0);
            if (!m_name.empty() && !IsConnector()) {
                ImGui::TextUnformatted(m_name.c_str());
            }
            ImGui::Spring(1);
            ImGui::Dummy(ImVec2(0, 28));

            if (m_hasOutputDelegates) {
                /** ImGui::BeginVertical("delegates", ImVec2(0, 28));
                ImGui::Spring(1, 0);

                for (auto&& pOutput : m_outputs) {
                    if (pOutput->GetType() != PinType::Delegate)
                        continue;

                    auto alpha = ImGui::GetStyle().Alpha;
                    if (pNewLinkPin && !CanCreateLink(pNewLinkPin, pOutput) && pOutput != pNewLinkPin)
                        alpha = alpha * (48.0f / 255.0f);

                    ax::NodeEditor::BeginPin(pOutput->GetId(), ax::NodeEditor::PinKind::Output);
                    ax::NodeEditor::PinPivotAlignment(ImVec2(1.0f, 0.5f));
                    ax::NodeEditor::PinPivotSize(ImVec2(0, 0));

                    ImGui::BeginHorizontal(pOutput->GetId());
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);

                    if (!pOutput->m_name.empty()) {
                        ImGui::TextUnformatted(pOutput->m_name.c_str());
                        ImGui::Spring(0);
                    }

                    pOutput->DrawPinIcon(pOutput->IsLinked(), (int)(alpha * 255));

                    ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
                    ImGui::EndHorizontal();
                    ImGui::PopStyleVar();

                    ax::NodeEditor::EndPin();
                }

                ImGui::Spring(1, 0);
                ImGui::EndVertical();
                ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);*/
            }
            else {
                ImGui::Spring(0);
            }

            pBuilder->EndHeader();
        }

        for (auto&& pInput : m_inputs) {
            auto alpha = ImGui::GetStyle().Alpha;

            if (pNewLinkPin && !CanCreateLink(pNewLinkPin, pInput) && pInput != pNewLinkPin)
                alpha = alpha * (48.0f / 255.0f);

            pBuilder->Input(pInput);

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
            pInput->DrawPinIcon(pInput->IsLinked(), (int)(alpha * 255));

            ImGui::Spring(0);

            if (!pInput->m_name.empty())
            {
                ImGui::TextUnformatted(pInput->m_name.c_str());
                ImGui::Spring(0);
            }

            if (!pInput->IsLinked()) {
                pInput->DrawOption();
                ImGui::Spring(0);
            }

            // if (pInput->GetType() == PinType::Bool)
            // {
            //     ImGui::Button("Hello");
            //
            // }

            ImGui::PopStyleVar();
            pBuilder->EndInput();
        }

        if (isSimple) {
            pBuilder->Middle();

            ImGui::Spring(1, 0);
            if (!m_name.empty() && !IsConnector()) {
                ImGui::TextUnformatted(m_name.c_str());
            }
            ImGui::Spring(1, 0);
        }

        for (auto&& pOutput : m_outputs)
        {
            /// if (!isSimple && pOutput->GetType() == PinType::Delegate)
            ///     continue;

            auto alpha = ImGui::GetStyle().Alpha;

            if (pNewLinkPin && !CanCreateLink(pNewLinkPin, pOutput) && pOutput != pNewLinkPin)
                alpha = alpha * (48.0f / 255.0f);

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
            pBuilder->Output(pOutput);

            if (pOutput->GetType() == SR_SRLM_NS::DataTypeClass::String) {
                static char buffer[128] = "Edit Me\nMultiline!";
                static bool wasActive = false;

                ImGui::PushItemWidth(100.0f);
                ImGui::InputText("##edit", buffer, 127);
                ImGui::PopItemWidth();
                if (ImGui::IsItemActive() && !wasActive)
                {
                    ax::NodeEditor::EnableShortcuts(false);
                    wasActive = true;
                }
                else if (!ImGui::IsItemActive() && wasActive)
                {
                    ax::NodeEditor::EnableShortcuts(true);
                    wasActive = false;
                }
                ImGui::Spring(0);
            }
            if (!pOutput->m_name.empty())
            {
                ImGui::Spring(0);
                ImGui::TextUnformatted(pOutput->m_name.c_str());
            }

            ImGui::Spring(0);

            pOutput->DrawPinIcon(pOutput->IsLinked(), (int)(alpha * 255));

            ImGui::PopStyleVar();
            pBuilder->EndOutput();
        }

        pBuilder->End();
    }

    uintptr_t Node::GetId() const {
        /// TODO: переделать, при сохранении будут проблемы
        return reinterpret_cast<const uintptr_t>(this);
    }

    Node::~Node() {
        for (auto& pin : m_inputs)
            delete pin;

        for (auto& pin : m_outputs)
            delete pin;

        m_inputs.clear();
        m_outputs.clear();
    }

    Pin* Node::GetInputPin(uint32_t index) {
        if (m_inputs.size() <= index) {
            SRAssert(false);
            return nullptr;
        }
        return m_inputs.at(index);
    }

    Pin* Node::GetOutputPin(uint32_t index) {
        if (m_outputs.size() <= index) {
            SRAssert(false);
            return nullptr;
        }
        return m_outputs.at(index);
    }

    Node& Node::SetPosition(const SR_MATH_NS::FVector2& pos) {
        ax::NodeEditor::SetNodePosition(GetId(), ImVec2(pos.x, pos.y));
        return *this;
    }

    Node& Node::SetName(std::string name) {
        m_name = std::move(name);
        return *this;
    }

    Node& Node::SetType(NodeType type) {
        m_type = type;
        return *this;
    }

    Node* Node::Copy() const {
        auto&& pNode = new Node();

        pNode->m_name = m_name;
        pNode->m_color = m_color;
        pNode->m_type = m_type;
        pNode->m_maxOutputWidth = m_maxOutputWidth;

        for (const auto& pin : m_inputs)
            pNode->AddInput(pin->Copy());

        for (const auto& pin : m_outputs)
            pNode->AddOutput(pin->Copy());

        return pNode;
    }

    std::string Node::GetName() const {
        return m_name;
    }

    Node& Node::AddInput(PinType type) {
        return AddInput(new Pin(std::string(), SR_SRLM_NS::DataTypeAllocator::Instance().Allocate(type)));
    }

    Node& Node::AddOutput(PinType type) {
        return AddOutput(new Pin(std::string(), SR_SRLM_NS::DataTypeAllocator::Instance().Allocate(type)));
    }

    Node& Node::AddInput(const std::string &name, PinType type) {
        return AddInput(new Pin(name, SR_SRLM_NS::DataTypeAllocator::Instance().Allocate(type)));
    }

    Node& Node::AddOutput(const std::string &name, PinType type) {
        return AddOutput(new Pin(name, SR_SRLM_NS::DataTypeAllocator::Instance().Allocate(type)));
    }

    Node& Node::AddInput(const std::string& name, SR_SRLM_NS::DataType* pDataType) {
        return AddInput(new Pin(name, pDataType));
    }

    Node& Node::AddOutput(const std::string& name, SR_SRLM_NS::DataType* pDataType) {
        return AddOutput(new Pin(name, pDataType));
    }

    uint64_t Node::GetHashName() const {
        return m_logicalNode->GetHashName();
    }

    SR_MATH_NS::FVector2 Node::GetPosition() const {
        auto&& pos = ax::NodeEditor::GetNodePosition(GetId());
        return SR_MATH_NS::FVector2(pos.x, pos.y);
    }

    int32_t Node::GetPinIndex(const Pin* pPin) const {
        for (uint32_t i = 0; i < m_inputs.size(); ++i) {
            if (m_inputs.at(i) == pPin) {
                return i;
            }
        }

        for (uint32_t i = 0; i < m_outputs.size(); ++i) {
            if (m_outputs.at(i) == pPin) {
                return i;
            }
        }

        return SR_ID_INVALID;
    }
}