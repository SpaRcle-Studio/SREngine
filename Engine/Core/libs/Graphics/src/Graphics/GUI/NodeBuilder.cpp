//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/Node.h>

namespace SR_GRAPH_NS::GUI {
    NodeBuilder::NodeBuilder(SR_GTYPES_NS::Texture *pTexture)
        : m_texture(pTexture)
    {
        if (m_texture) {
            m_texture->AddUsePoint();
        }
    }

    NodeBuilder::~NodeBuilder() {
        if (m_texture) {
            m_texture->RemoveUsePoint();
        }
    }

    void NodeBuilder::Begin(Node *pNode) {
        m_hasHeader = false;
        m_headerMin = m_headerMax = ImVec2();

        ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));

        m_currentNodeId = pNode->GetId();

        ax::NodeEditor::BeginNode(m_currentNodeId);

        ImGui::PushID(m_currentNodeId);

        SetStage(Stage::Begin);
    }

    void NodeBuilder::End() {
        SetStage(Stage::End);

        ax::NodeEditor::EndNode();

        if (ImGui::IsItemVisible())
        {
            auto alpha = static_cast<int>(255 * ImGui::GetStyle().Alpha);

            auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(m_currentNodeId);

            const auto halfBorderWidth = ax::NodeEditor::GetStyle().NodeBorderWidth * 0.5f;

            auto headerColor = IM_COL32(0, 0, 0, alpha) | (m_headerColor & IM_COL32(255, 255, 255, 0));
            if ((m_headerMax.x > m_headerMin.x) && (m_headerMax.y > m_headerMin.y) && GetTextureId())
            {
                const auto uv = ImVec2(
                        (m_headerMax.x - m_headerMin.x) / (float)(4.0f * m_texture->GetWidth()),
                        (m_headerMax.y - m_headerMin.y) / (float)(4.0f * m_texture->GetHeight()));

                drawList->AddImageRounded(GetTextureId(),
                                          m_headerMin - ImVec2(8 - halfBorderWidth, 4 - halfBorderWidth),
                                          m_headerMax + ImVec2(8 - halfBorderWidth, 0),
                                          ImVec2(0.0f, 0.0f), uv,
                                          headerColor, ax::NodeEditor::GetStyle().NodeRounding, ImDrawFlags_RoundCornersTop);

                auto headerSeparatorMin = ImVec2(m_headerMin.x, m_headerMax.y);
                auto headerSeparatorMax = ImVec2(m_headerMax.x, m_headerMin.y);

                if ((headerSeparatorMax.x > headerSeparatorMin.x) && (headerSeparatorMax.y > headerSeparatorMin.y))
                {
                    drawList->AddLine(
                            headerSeparatorMin + ImVec2(-(8 - halfBorderWidth), -0.5f),
                            headerSeparatorMax + ImVec2( (8 - halfBorderWidth), -0.5f),
                            ImColor(255, 255, 255, 96 * alpha / (3 * 255)), 1.0f);
                }
            }
        }

        m_currentNodeId = 0;

        ImGui::PopID();

        ax::NodeEditor::PopStyleVar();

        SetStage(Stage::Invalid);
    }

    void NodeBuilder::Header(const ImVec4 &color) {
        m_headerColor = ImColor(color);
        SetStage(Stage::Header);
    }

    void NodeBuilder::EndHeader() {
        SetStage(Stage::Content);
    }

    ImTextureID NodeBuilder::GetTextureId() const {
        if (!m_texture) {
            return nullptr;
        }

        auto&& id = m_texture->GetId();
        if (id == SR_ID_INVALID) {
            return nullptr;
        }

        if (auto&& pPipeline = m_texture->GetPipeline()) {
            return pPipeline->GetDescriptorSetFromTexture(id, true);
        }

        return nullptr;
    }

    void NodeBuilder::Input(Pin *pPin) {
        if (m_currentStage == Stage::Begin)
            SetStage(Stage::Content);

        const auto applyPadding = (m_currentStage == Stage::Input);

        SRAssert(!m_currentPin);
        m_currentPin = pPin;

        SetStage(Stage::Input);

        if (applyPadding)
            ImGui::Spring(0);

        pPin->Begin(PinKind::Input);

        ImGui::BeginHorizontal(pPin->GetId());
    }

    void NodeBuilder::EndInput() {
        ImGui::EndHorizontal();
        SRAssert(m_currentPin);
        m_currentPin->End();
        m_currentPin = nullptr;
    }

    void NodeBuilder::Middle() {
        if (m_currentStage == Stage::Begin)
            SetStage(Stage::Content);

        SetStage(Stage::Middle);
    }

    void NodeBuilder::Output(Pin *pPin) {
        if (m_currentStage == Stage::Begin)
            SetStage(Stage::Content);

        const auto applyPadding = (m_currentStage == Stage::Output);

        SRAssert(!m_currentPin);
        m_currentPin = pPin;

        SetStage(Stage::Output);

        if (applyPadding)
            ImGui::Spring(0);

        pPin->Begin(PinKind::Output);

        ImGui::BeginHorizontal(pPin->GetId());
    }

    void NodeBuilder::EndOutput() {
        ImGui::EndHorizontal();
        SRAssert(m_currentPin);
        m_currentPin->End();
        m_currentPin = nullptr;
    }

    bool NodeBuilder::SetStage(NodeBuilder::Stage stage) {
        if (stage == m_currentStage)
            return false;

        auto oldStage = m_currentStage;
        m_currentStage = stage;

        ImVec2 cursor;
        switch (oldStage)
        {
            case Stage::Begin:
                break;

            case Stage::Header:
                ImGui::EndHorizontal();
                m_headerMin = ImGui::GetItemRectMin();
                m_headerMax = ImGui::GetItemRectMax();

                /// spacing between header and content
                ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);

                break;

            case Stage::Content:
                break;

            case Stage::Input:
                ax::NodeEditor::PopStyleVar(2);

                ImGui::Spring(1, 0);
                ImGui::EndVertical();

                break;

            case Stage::Middle:
                ImGui::EndVertical();

                break;

            case Stage::Output:
                ax::NodeEditor::PopStyleVar(2);

                ImGui::Spring(1, 0);
                ImGui::EndVertical();

                break;

            case Stage::End:
                break;

            case Stage::Invalid:
                break;
        }

        switch (stage)
        {
            case Stage::Begin:
                ImGui::BeginVertical("node");
                break;

            case Stage::Header:
                m_hasHeader = true;
                ImGui::BeginHorizontal("header");
                break;

            case Stage::Content:
                if (oldStage == Stage::Begin)
                    ImGui::Spring(0);

                ImGui::BeginHorizontal("content");
                ImGui::Spring(0, 0);
                break;

            case Stage::Input:
                ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);

                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));

                if (!m_hasHeader)
                    ImGui::Spring(1, 0);

                break;

            case Stage::Middle:
                ImGui::Spring(1);
                ImGui::BeginVertical("middle", ImVec2(0, 0), 1.0f);
                break;

            case Stage::Output:
                if (oldStage == Stage::Middle || oldStage == Stage::Input)
                    ImGui::Spring(1);
                else
                    ImGui::Spring(1, 0);

                ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);

                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));

                if (!m_hasHeader)
                    ImGui::Spring(1, 0);

                break;

            case Stage::End:
                if (oldStage == Stage::Input)
                    ImGui::Spring(1, 0);

                if (oldStage != Stage::Begin)
                    ImGui::EndHorizontal();

                m_contentMin = ImGui::GetItemRectMin();
                m_contentMax = ImGui::GetItemRectMax();

                ImGui::EndVertical();

                m_nodeMin = ImGui::GetItemRectMin();
                m_nodeMax = ImGui::GetItemRectMax();
                break;

            case Stage::Invalid:
                break;
        }

        return true;
    }
}

