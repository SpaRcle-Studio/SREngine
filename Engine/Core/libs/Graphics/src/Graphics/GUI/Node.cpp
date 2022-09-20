//
// Created by Monika on 11.01.2022.
//

#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/NodeManager.h>
#include <Graphics/GUI/Pin.h>

namespace SR_GRAPH_NS {
    Node::Node()
        : Node(std::string(), NodeType::None, ImColor(255, 255, 255, 255))
    { }

    Node::Node( const std::string &name)
        : Node(name, NodeType::None, ImColor(255, 255, 255, 255))
    { }

    Node::Node(const std::string &name, NodeType type)
        : Node(name, type, ImColor(255, 255, 255, 255))
    { }

    Node::Node(const std::string &name, ImColor color)
        : Node(name, NodeType::None, color)
    { }

    Node::Node(const std::string &name, NodeType type, ImColor color)
        : m_name(name)
        , m_color(color)
        , m_type(type)
    {
        m_id = NodeManager::Instance().AllocUniqueId(this);
    }

    Node *Node::AddInput(Pin *pin) {
        pin->m_kind = PinKind::Input;
        pin->SetNode(this);

        m_inputs.emplace_back(pin);

        return this;
    }

    Node* Node::AddOutput(Pin* pin) {
        pin->m_kind = PinKind::Output;
        pin->SetNode(this);

        if (const auto pinWidth = pin->GetWidth(); pinWidth > m_maxOutputWidth)
            m_maxOutputWidth = pinWidth;

        m_outputs.emplace_back(pin);

        return this;
    }

    void Node::Draw() const {
        ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));

        ax::NodeEditor::BeginNode(m_id);
        ImGui::PushID(m_id.AsPointer());

        if (m_type == NodeType::Blueprint) {
            ImGui::Text("%s", m_name.c_str());
        }

        auto HeaderMaxY = ImGui::GetItemRectMax().y;

        ImGui::BeginGroup();
        {

            for (const auto &pin : m_inputs)
                pin->Draw();

            ImGui::EndGroup();

        }

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            if (m_type == NodeType::Simple) {
                for (uint32_t i = 0; i < m_inputs.size() / 2; ++i)
                    ImGui::Text(" ");

                ImGui::Text("\t%s\t", m_name.c_str());
            }
        }
        ImGui::EndGroup();

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            for (uint32_t i = 0; i < m_inputs.size() / 2; ++i)
                ImGui::Text(" ");

            for (const auto &pin : m_outputs)
                pin->Draw(m_maxOutputWidth);
        }
        ImGui::EndGroup();

        ax::NodeEditor::EndNode();

        if (ImGui::IsItemVisible() && m_type == NodeType::Blueprint)
        {
            const auto halfBorderWidth = ax::NodeEditor::GetStyle().NodeBorderWidth * 0.5f;

            auto HeaderMin = ImGui::GetItemRectMin();
            auto HeaderMax = ImVec2(ImGui::GetItemRectMax().x, HeaderMaxY + halfBorderWidth);

            auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(m_id);

            auto HeaderColor = IM_COL32(
                    m_color.Value.x,
                    m_color.Value.y,
                    m_color.Value.z,
                    m_color.Value.w);

            auto alpha = static_cast<int>(255 * ImGui::GetStyle().Alpha);
            auto headerColor = IM_COL32(0, 0, 0, alpha) | (HeaderColor & IM_COL32(255, 255, 255, 0));
            if ((HeaderMax.x > HeaderMin.x) && (HeaderMax.y > HeaderMin.y))
            {
                drawList->AddRectFilled(HeaderMin,
                                        HeaderMax,
                                        headerColor, ax::NodeEditor::GetStyle().NodeRounding, 1 | 2);

                auto headerSeparatorMin = ImVec2(HeaderMin.x, HeaderMax.y - 0.5);
                auto headerSeparatorMax = ImVec2(HeaderMax.x, HeaderMax.y - 0.5);

                drawList->AddLine(
                        headerSeparatorMin,
                        headerSeparatorMax,
                        ImColor(255, 255, 255, 96 * alpha / (3 * 255)), 2.0f);
            }
        }

        ax::NodeEditor::PopStyleVar();
        ImGui::PopID();
    }

    uintptr_t Node::GetId() const {
        return m_id.Get();
    }

    Node::~Node() {
        if (Valid())
            NodeManager::Instance().FreeUniqueId(m_id.Get());

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

    bool Node::Valid() const {
        return m_id != ax::NodeEditor::NodeId::Invalid;
    }

    Node* Node::Copy() const {
        auto node = new Node();
        node->m_name = m_name;
        node->m_color = m_color;
        node->m_type = m_type;
        node->m_maxOutputWidth = m_maxOutputWidth;

        for (const auto& pin : m_inputs)
            node->AddInput(pin->Copy());

        for (const auto& pin : m_outputs)
            node->AddOutput(pin->Copy());

        return node;
    }

    std::string Node::GetName() const {
        return m_name;
    }
}