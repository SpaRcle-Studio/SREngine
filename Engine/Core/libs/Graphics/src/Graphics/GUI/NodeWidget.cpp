//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/GUI/NodeCreation.h>
#include <Graphics/Types/Texture.h>

#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/SRLM/DataTypeManager.h>
#include <Utils/Common/HashManager.h>

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

        if (auto&& pRawLink = ax::NodeEditor::GetDoubleClickedLink()) {
            auto&& pLink = reinterpret_cast<SR_GRAPH_GUI_NS::Link*>(pRawLink.AsPointer());
            auto&& clickPos = ImGui::GetMousePos();

            if (pLink->IsLinked()) {
                auto&& pNode = new Node();

                pNode->SetType(NodeType::Dot)
                    .SetIdentifier(SR_SRLM_NS::NODE_LINK_DOT)
                    .SetPosition(SR_MATH_NS::FVector2(clickPos.x, clickPos.y))
                    .AddInput(pLink->GetStart()->GetType())
                    .AddOutput(pLink->GetStart()->GetType());

                AddLink(new Link(pNode->GetOutputPin(0), pLink->GetEnd()));
                pLink->SetEnd(pNode->GetInputPin(0));

                AddNode(pNode);
            }
        }

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
        static Node def;

        if (!pNode) {
            SRHalt0();
            return def;
        }

        if (!CanAddNode(pNode)) {
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

        if (ImGui::Button("Zoom")) {
            ax::NodeEditor::NavigateToContent();
        }

        ImGui::SameLine();

        ImGui::Text(" | ");

        ImGui::SameLine();

        if (ImGui::Button("Close")) {
            TopPanelClose();
        }

        ImGui::SameLine();
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
        InitStructsCreationPopup();
        InitCreationPopup();
        Super::Init();
    }

    void NodeWidget::InitStructsCreationPopup() {
        auto&& createStructsNodesMenu = m_creationPopup->AddMenu("Create Structs");
        auto&& breakStructsNodesMenu = m_creationPopup->AddMenu("Break Structs");

        for (auto&& [hashName, pStruct] : SR_SRLM_NS::DataTypeManager::Instance().GetStructs()) {
            auto&& structName = SR_UTILS_NS::HashManager::Instance().HashToString(pStruct->GetStructName());

            createStructsNodesMenu.AddMenu(structName).SetAction([structName, pStruct = pStruct](const SR_GRAPH_GUI_NS::DrawPopupContext& context)
            {
                auto&& pNode = new SR_GRAPH_GUI_NS::Node();
                auto&& node = *pNode;

                node.SetPosition(context.popupPos);
                node.SetIdentifier(SR_SRLM_NS::NODE_CREATE_STRUCT);
                node.SetType(SR_GRAPH_GUI_NS::NodeType::Blueprint);

                node.SetName(structName);

                for (auto&& [variableHashName, pVariable] : pStruct->GetVariables()) {
                    node.AddInput(SR_UTILS_NS::HashManager::Instance().HashToString(variableHashName), pVariable->Copy());
                }

                node.AddOutput(structName, pStruct->Copy());

                context.pWidget->AddNode(pNode);
            });

            breakStructsNodesMenu.AddMenu(structName).SetAction([structName, pStruct = pStruct](const SR_GRAPH_GUI_NS::DrawPopupContext& context)
            {
                auto&& pNode = new SR_GRAPH_GUI_NS::Node();
                auto&& node = *pNode;

                node.SetPosition(context.popupPos);
                node.SetIdentifier(SR_SRLM_NS::NODE_BREAK_STRUCT);
                node.SetType(SR_GRAPH_GUI_NS::NodeType::Blueprint);

                node.SetName(structName);

                node.AddInput(structName, pStruct->Copy());

                for (auto&& [variableHashName, pVariable] : pStruct->GetVariables()) {
                    node.AddOutput(SR_UTILS_NS::HashManager::Instance().HashToString(variableHashName), pVariable->Copy());
                }

                context.pWidget->AddNode(pNode);
            });
        }
    }

    void NodeWidget::InitCreationPopup() {
        auto&& commonNodesMenu = m_creationPopup->AddMenu("Common");

        auto&& logicNodesMenu = commonNodesMenu.AddMenu("Logic");

        logicNodesMenu.AddMenu("Condition").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_BOOL_CONDITION));
        });

        logicNodesMenu.AddMenu("And").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_BOOL_AND));
        });

        logicNodesMenu.AddMenu("Or").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_BOOL_OR));
        });

        logicNodesMenu.AddMenu("Not").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_BOOL_NOT));
        });

        auto&& mathNodesMenu = commonNodesMenu.AddMenu("Math");

        mathNodesMenu.AddMenu("- Int").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_INT_NEGATIVE));
        });

        mathNodesMenu.AddMenu("- Float").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_FLOAT_NEGATIVE));
        });

        mathNodesMenu.AddMenu("Int to Float").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_INT_TO_FLOAT));
        });

        mathNodesMenu.AddMenu("Float to Int").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_FLOAT_TO_INT));
        });

        mathNodesMenu.AddMenu("int + int").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_INT_PLUS_INT));
        });

        mathNodesMenu.AddMenu("int - int").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_INT_MINUS_INT));
        });

        mathNodesMenu.AddMenu("float + float").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_FLOAT_PLUS_FLOAT));
        });

        mathNodesMenu.AddMenu("float - float").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(CreateNode(context.popupPos, SR_SRLM_NS::NODE_FLOAT_MINUS_FLOAT));
        });
    }

    void NodeWidget::TopPanelSaveAt() {

    }

    void NodeWidget::TopPanelOpen() {

    }

    void NodeWidget::TopPanelSave() {
        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/RenderTechniques/Sample.xml");

        SR_XML_NS::Document xmlDocument;

        auto&& xmlLogicalMachine = xmlDocument.Root().AppendNode("LogicalMachine");
        auto&& xmlNodes = xmlLogicalMachine.AppendNode("Nodes");

        for (auto&& [uid, pNode] : m_nodes) {
            auto&& xmlNode = xmlNodes.AppendNode("Node");

            xmlNode.AppendAttribute("UID", uid);
        }
    }

    void NodeWidget::TopPanelClose() {
        Close();
    }
}
