//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/Types/Texture.h>

namespace SR_GRAPH_GUI_NS {
    NodeWidget::NodeWidget(std::string name, SR_MATH_NS::IVector2 size)
        : Super(std::move(name), size)
    {
        auto&& texturePath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Textures/BlueprintBackground.png");
        m_nodeBuilder = new NodeBuilder(SR_GTYPES_NS::Texture::Load(texturePath));

        m_creationPopup = new PopupItemSubWidget(GetName() + "-Popup");
    }

    NodeWidget::~NodeWidget() {
        Clear();
        delete m_nodeBuilder;
    }

    void NodeWidget::UpdateTouch() {
        const auto deltaTime = ImGui::GetIO().DeltaTime;
        for (auto&& entry : m_nodeTouchTime) {
            if (entry.second > 0.0f) {
                entry.second -= deltaTime;
            }
        }
    }

    void NodeWidget::Clear() {
        for (auto&& [id, pLink] : m_links) {
            delete pLink;
        }

        for (auto&& [id, pNode] : m_nodes) {
            delete pNode;
        }

        m_nodes.clear();
        m_links.clear();
    }

    void NodeWidget::Draw() {
        if (!m_editor) {
            ImGui::Text("Invalid editor!");
            return;
        }

        DrawTopPanel();

        if (!IsOpen()) {
            return;
        }

        ImGui::Separator();

        UpdateTouch();

        ax::NodeEditor::SetCurrentEditor(m_editor);

        ax::NodeEditor::Begin(GetName().c_str());

        for (auto&& [id, node] : m_nodes)
            node->Draw(m_nodeBuilder, nullptr);

        for (auto pIt = m_links.begin(); pIt != m_links.end(); ) {
            auto&& [id, pLink] = *pIt;

            if (pLink->IsLinked()) {
                pLink->Draw();
                ++pIt;
            }
            else {
                pIt = m_links.erase(pIt);
            }
        }

        if (ax::NodeEditor::BeginCreate()) {
            ax::NodeEditor::PinId inputPinId, outputPinId;
            if (ax::NodeEditor::QueryNewLink(&inputPinId, &outputPinId) && (inputPinId && outputPinId)) {
                auto&& pInputPin = reinterpret_cast<SR_GRAPH_GUI_NS::Pin*>(inputPinId.AsPointer());
                auto&& pOutputPin = reinterpret_cast<SR_GRAPH_GUI_NS::Pin*>(outputPinId.AsPointer());

                if (pInputPin != pOutputPin) {
                    if (SR_GRAPH_GUI_NS::CanCreateLink(pInputPin, pOutputPin) && ax::NodeEditor::AcceptNewItem()) {
                        AddLink(new SR_GRAPH_GUI_NS::Link(pInputPin, pOutputPin));
                    }
                }
            }
        }

        ax::NodeEditor::EndCreate();

        if (ax::NodeEditor::BeginDelete()) {
            ax::NodeEditor::NodeId deleteNodeId;
            if (ax::NodeEditor::QueryDeletedNode(&deleteNodeId)) {
                auto&& pNode = reinterpret_cast<SR_GRAPH_GUI_NS::Node*>(deleteNodeId.AsPointer());
                RemoveNode(pNode);
            }

            ax::NodeEditor::LinkId deleteLinkId;
            if (ax::NodeEditor::QueryDeletedLink(&deleteLinkId)) {
                auto&& pLink = reinterpret_cast<SR_GRAPH_GUI_NS::Link*>(deleteLinkId.AsPointer());
                RemoveLink(pLink);
            }
        }

        ax::NodeEditor::EndDelete();

        DrawPopupMenu();

        ax::NodeEditor::End();
    }

    void NodeWidget::RemoveLink(Link *pLink) {
        pLink->Broke(nullptr);
    }

    void NodeWidget::RemoveNode(Node* pNode) {
        auto&& pIt = m_nodes.find(pNode->GetId());
        if (pIt == m_nodes.end()) {
            SRHalt0();
            return;
        }

        m_nodes.erase(pIt);
        delete pNode;
    }

    Node& NodeWidget::AddNode(Node* pNode) {
        if (!pNode) {
            SRHalt0();
            static Node def;
            return def;
        }

        SRAssert(m_nodes.count(pNode->GetId()) == 0);
        m_nodes.insert(std::make_pair(pNode->GetId(), pNode));

        return *pNode;
    }

    Link& NodeWidget::AddLink(Link* pLink) {
        if (!pLink) {
            SRHalt0();
            static Link def;
            return def;
        }

        SRAssert(m_links.count(pLink->GetId()) == 0);
        m_links.insert(std::make_pair(pLink->GetId(), pLink));

        return *pLink;
    }

    void NodeWidget::OnClose() {
        if (m_editor) {
            ax::NodeEditor::DestroyEditor(m_editor);
            m_editor = nullptr;
        }

        Super::OnClose();
    }

    void NodeWidget::DrawTopPanel() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

        if (ImGui::Button("Open")) {
            TopPanelOpen();
        }

        ImGui::SameLine();

        if (ImGui::Button("Save")) {
            TopPanelSave();
        }

        ImGui::SameLine();

        if (ImGui::Button("Save at")) {
            TopPanelSaveAt();
        }

        ImGui::SameLine();

        ImGui::Text(" | ");

        ImGui::SameLine();

        if (ImGui::Button("Close")) {
            TopPanelClose();
        }

        ImGui::PopStyleVar(3);
    }

    void NodeWidget::DrawPopupMenu() {
        auto&& openPopupPosition = ImGui::GetMousePos();

        ax::NodeEditor::Suspend();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

        DrawPopupContext context;
        context.popupPos = SR_MATH_NS::FVector2(openPopupPosition.x, openPopupPosition.y);
        context.pWidget = this;

        m_creationPopup->Draw(context);

        ImGui::PopStyleVar();

        ax::NodeEditor::Resume();
    }

    void NodeWidget::Init() {
        InitCreationPopup();
        Super::Init();
    }

    void NodeWidget::InitCreationPopup() {

    }

    void NodeWidget::TopPanelSaveAt() {

    }

    void NodeWidget::TopPanelOpen() {

    }

    void NodeWidget::TopPanelSave() {

    }

    void NodeWidget::TopPanelClose() {
        Close();
    }
}
