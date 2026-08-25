//
// Created by Monika on 18.08.2026.
//

#include <Engine/Engine.h>
#include <Engine/GUI/FluxEditor/FluxEditor.h>
#include <Engine/GUI/EditorGUI.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>
#include <ImmediateGUI/GUI/NodeEditor.h>

#include <Utils/Common/EnumReflector.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Flux/Runtime/FluxComponent.h>
#include <Utils/Flux/Runtime/FluxRuntime.h>
#include <Utils/Reflection/Method.h>
#include <Utils/Reflection/Value.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/World/Scene.h>
#include <Utils/TypeTraits/SRClassMeta.h>

#include <Codegen/FluxEditor.generated.hpp>
#include <Engine/EngineCommands.h>

namespace SR_CORE_GUI_NS {
    namespace {
        const SR_MATH_NS::FColor SR_FLUX_HINT_COLOR = SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f);
        const SR_MATH_NS::FColor SR_FLUX_ERROR_COLOR = SR_MATH_NS::FColor(1.0f, 0.25f, 0.25f, 1.0f);

        SR_NODISCARD bool HasName(const SR_FLUX_NS::FluxGraphNodeType type) {
            return type == SR_FLUX_NS::FluxGraphNodeType::Event ||
                type == SR_FLUX_NS::FluxGraphNodeType::ReadVariable ||
                type == SR_FLUX_NS::FluxGraphNodeType::WriteVariable;
        }

        SR_NODISCARD bool HasCallable(const SR_FLUX_NS::FluxGraphNodeType type) {
            return type == SR_FLUX_NS::FluxGraphNodeType::Invoke ||
                type == SR_FLUX_NS::FluxGraphNodeType::Evaluate;
        }

        SR_NODISCARD bool IsVariableNode(const SR_FLUX_NS::FluxGraphNodeType type) {
            return type == SR_FLUX_NS::FluxGraphNodeType::ReadVariable ||
                type == SR_FLUX_NS::FluxGraphNodeType::WriteVariable;
        }
    }

    FluxEditor::FluxEditor()
        : Super("Flux")
    { }

    void FluxEditor::Init() {
        Super::Init();

        m_onCommandRedoSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_COMMAND_REDO_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            m_skipInspect = true;
            m_previewCompiled = false;
        });
        m_onCommandUndoSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_COMMAND_UNDO_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            m_skipInspect = true;
            m_previewCompiled = false;
        });
        m_doInspectEntitySubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_DO_INSPECT_ENTITY_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            if (msg.GetStringAtom("ClassName") != SR_FLUX_NS::FluxComponent::GetClassStaticName()) {
                return;
            }
            const auto entityId = msg.GetInt("EntityId");
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& pEntity = pEngine->GetScene()->GetEntityController()->FindById(entityId);
            if (!pEntity) {
                SR_ERROR("FluxEditor::Init() : failed to find entity with id: {}", entityId);
                return;
            }
            if (auto&& pFlux = pEntity.DynamicCast<SR_FLUX_NS::FluxComponent>()) {
                Inspect(pFlux->GetGraphPath());
            }
        });
    }

    void FluxEditor::Inspect(const SR_UTILS_NS::Path& path) {
        m_graphAsset.Reset();
        m_currentFile = path;
        m_previewCompiled = false;

        if (path.IsEmpty()) {
            return;
        }

        Open();
        Focus();

        auto&& loadPath = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
        m_graphAsset = SR_UTILS_NS::Asset::Load<SR_FLUX_NS::FluxGraphAsset>(loadPath);

        if (!m_graphAsset) {
            SR_ERROR("FluxEditor::Inspect() : failed to load flux graph asset: {}", loadPath);
            return;
        }

        m_nodeGraphEditor->ClearSelection();
        m_nodeGraphEditor->ResetEditor();
    }

    SR_FLUX_NS::FluxGraph* FluxEditor::GetGraph() const {
        return m_graphAsset ? &m_graphAsset->GetGraphMutable() : nullptr;
    }

    void* FluxEditor::IndexToUserData(const uint32_t index) {
        /// нулевой указатель означает отсутствие данных, поэтому индексы смещены на единицу
        return reinterpret_cast<void*>(static_cast<uintptr_t>(index) + 1);
    }

    uint32_t FluxEditor::UserDataToIndex(const void* pUserData) {
        return pUserData ? static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pUserData) - 1) : SR_UINT32_MAX;
    }

    void FluxEditor::DrawNodeEditor() {
        SR_TRACY_ZONE;

        if (!m_nodeGraphEditor) {
            return;
        }

        const auto size = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();

        if (SR_IMMEDIATE_GUI_NS::BeginChild("Node Editor")) {
            m_backgroundText = "Flux";
            if (m_graphAsset) {
                m_backgroundText += ": ";
                m_backgroundText += m_graphAsset->GetResourcePath().View();
            }

            SyncLogicToVisual();
            m_nodeGraphEditor->SetStyleType(SR_IMMEDIATE_GUI_NS::NodeEditorStyleType::Graph);
            m_nodeGraphEditor->SetBackgroundText(m_backgroundText);
            m_nodeGraphEditor->SetSize(size);
            m_nodeGraphEditor->Draw();
            SyncVisualToLogic();
            ApplyPendingRemoves();

            SR_IMMEDIATE_GUI_NS::EndChild();
        }

        if (m_serializer && !SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseLeft)) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& cmd = new SR_CORE_NS::Commands::SerializableChange(pEngine, SR_UTILS_NS::SharedPtrBaseHolder(m_graphAsset.Get()), std::move(m_serializer));
            pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void FluxEditor::SyncLogicToVisual() {
        SR_TRACY_ZONE;

        m_nodeGraphEditor->ResetEditor();

        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        m_nodeGraphEditor->SetSomethingChangedCallback([this]() {
            if (!m_serializer && m_graphAsset) {
                m_previewCompiled = false;
                m_serializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_serializer, *m_graphAsset, SR_UTILS_NS::COMMAND_DATA_ID);
            }
        });

        m_nodeGraphEditor->SetBackgroundPopupCallback([this](const SR_MATH_NS::FVector2& pos) {
            DrawCreateNodeMenu(pos);
        });

        m_nodeGraphEditor->SetNodeDeletedCallback([this](SR_IMMEDIATE_GUI_NS::NodeInstance& node) {
            OnNodeDeleted(node);
        });

        m_nodeGraphEditor->SetLinkDeletedCallback([this](SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
            OnLinkDeleted(link);
        });

        m_nodeGraphEditor->SetLinkCreatedCallback([this](SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
            OnLinkCreated(link);
        });

        m_nodes.resize(pGraph->GetNodeCount());
        m_layouts.resize(pGraph->GetNodeCount());

        for (uint32_t nodeIndex = 0; nodeIndex < pGraph->GetNodeCount(); ++nodeIndex) {
            auto&& pNodeInstance = m_nodeGraphEditor->CreateNode();
            m_nodes[nodeIndex] = pNodeInstance;

            if (!pNodeInstance) {
                continue;
            }

            auto&& layout = m_layouts[nodeIndex];
            BuildFluxNodeLayout(*pGraph, nodeIndex, layout, m_tmpTypeInfos);

            pNodeInstance->SetUserData(IndexToUserData(nodeIndex));
            pNodeInstance->SetPosition(pGraph->GetNode(nodeIndex)->GetPosition());
            pNodeInstance->SetTitle(layout.title);

            pGraph->GetNode(nodeIndex)->SetUserData(pNodeInstance);

            for (auto&& pin : layout.inputs) {
                pNodeInstance->AddInputPin(pin.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo(pin.pTypeInfo, pin.isFlow));
            }
            for (auto&& pin : layout.outputs) {
                pNodeInstance->AddOutputPin(pin.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo(pin.pTypeInfo, pin.isFlow));
            }
        }

        m_brokenLinks.clear();
        for (uint32_t linkIndex = 0; linkIndex < pGraph->GetLinks().size(); ++linkIndex) {
            auto&& link = pGraph->GetLinks()[linkIndex];

            if (link.GetSourceNode() >= m_nodes.size() || link.GetTargetNode() >= m_nodes.size()) {
                SR_WARN("FluxEditor::SyncLogicToVisual() : link {} references an unknown node!", linkIndex);
                continue;
            }

            auto&& pSourceNode = m_nodes[link.GetSourceNode()];
            auto&& pTargetNode = m_nodes[link.GetTargetNode()];

            if (!pSourceNode || !pTargetNode) {
                continue;
            }

            if (link.GetSourcePin() >= pSourceNode->GetOutputs().size() || link.GetTargetPin() >= pTargetNode->GetInputs().size()) {
                SR_WARN("FluxEditor::SyncLogicToVisual() : link {} references an unknown pin! Link will be broken.", linkIndex);
                m_brokenLinks.emplace_back(link);
                continue;
            }

            if (auto&& pLinkInstance = pSourceNode->LinkTo(pTargetNode, link.GetSourcePin(), link.GetTargetPin())) {
                pLinkInstance->SetUserData(IndexToUserData(linkIndex));
            }
        }
    }

    void FluxEditor::SyncVisualToLogic() {
        SR_TRACY_ZONE;

        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        for (auto&& node : pGraph->GetNodes()) {
            if (auto&& pNode = static_cast<SR_IMMEDIATE_GUI_NS::NodeInstance*>(node.GetUserData())) {
                node.SetPosition(pNode->GetPosition());
            }
        }

        for (auto&& link : m_brokenLinks) {
            pGraph->RemoveLink(link.GetSourceNode(), link.GetSourcePin(), link.GetTargetNode(), link.GetTargetPin());
        }

        for (auto&& pTmpTypeInfo : m_tmpTypeInfos) {
            SR_UTILS_NS::Reflection::FreeTypeInfo(pTmpTypeInfo);
        }
        m_tmpTypeInfos.clear();
    }

    void FluxEditor::OnNodeTypeSelected(const SR_UTILS_NS::StringAtom type, const SR_MATH_NS::FVector2 pos) {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        if (!m_serializer && m_graphAsset) {
            m_serializer = SR_CORE_NS::Commands::CreateSerializer();
            SR_UTILS_NS::Serialization::Save(*m_serializer, *m_graphAsset, SR_UTILS_NS::COMMAND_DATA_ID);
            m_previewCompiled = false;
        }

        SR_FLUX_NS::FluxGraphNode node;
        node.SetType(SR_UTILS_NS::EnumReflector::FromString<SR_FLUX_NS::FluxGraphNodeType>(type));
        node.SetPosition(SR_IMMEDIATE_GUI_NS::NodeEditor::ScreenToCanvas(pos));

        if (node.GetType() == SR_FLUX_NS::FluxGraphNodeType::Constant) {
            node.SetConstant(CreateFluxValue(SR_UTILS_NS::StringAtom("int32_t")));
        }

        pGraph->AddNode(node);
    }

    void FluxEditor::DrawCreateNodeMenu(const SR_MATH_NS::FVector2& popupPos) {
        if (!GetGraph()) {
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::InputText("##NodeSearch", &m_createNodeSearch);
        SR_GRAPH_GUI_NS::Immediate::Separator();

        for (auto&& name : SR_UTILS_NS::EnumReflector::GetNames<SR_FLUX_NS::FluxGraphNodeType>()) {
            if (name == SR_UTILS_NS::EnumReflector::ToStringAtom(SR_FLUX_NS::FluxGraphNodeType::Unknown)) {
                continue;
            }

            if (!m_createNodeSearch.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_createNodeSearch, name.ToStringView())) {
                continue;
            }

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem(name.c_str())) {
                OnNodeTypeSelected(name, popupPos);
            }
        }
    }

    void FluxEditor::OnNodeDeleted(SR_IMMEDIATE_GUI_NS::NodeInstance& node) {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        const uint32_t nodeIndex = UserDataToIndex(node.GetUserData());
        if (nodeIndex < pGraph->GetNodeCount()) {
            m_pendingNodeRemoves.emplace_back(nodeIndex);
        }
    }

    void FluxEditor::OnLinkDeleted(SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        const uint32_t linkIndex = UserDataToIndex(link.GetUserData());
        if (linkIndex < pGraph->GetLinks().size()) {
            m_pendingLinkRemoves.emplace_back(pGraph->GetLinks()[linkIndex]);
        }
    }

    void FluxEditor::ApplyPendingRemoves() {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            m_pendingNodeRemoves.clear();
            m_pendingLinkRemoves.clear();
            return;
        }

        for (auto&& link : m_pendingLinkRemoves) {
            pGraph->RemoveLink(link.GetSourceNode(), link.GetSourcePin(), link.GetTargetNode(), link.GetTargetPin());
        }
        m_pendingLinkRemoves.clear();

        /// удаляем с конца, чтобы сдвиг индексов не задел ещё не удалённые узлы
        std::sort(m_pendingNodeRemoves.begin(), m_pendingNodeRemoves.end(), std::greater<>());
        uint32_t previousIndex = SR_UINT32_MAX;
        for (auto&& nodeIndex : m_pendingNodeRemoves) {
            if (nodeIndex != previousIndex) {
                pGraph->RemoveNode(nodeIndex);
                previousIndex = nodeIndex;
            }
        }
        m_pendingNodeRemoves.clear();
    }

    void FluxEditor::OnLinkCreated(SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        auto&& pInputPin = link.GetInputPin();
        auto&& pOutputPin = link.GetOutputPin();

        if (!pInputPin || !pOutputPin) {
            return;
        }

        auto&& pTargetNodeInstance = pInputPin->GetNode();
        auto&& pSourceNodeInstance = pOutputPin->GetNode();

        const uint32_t targetNode = UserDataToIndex(pTargetNodeInstance->GetUserData());
        const uint32_t sourceNode = UserDataToIndex(pSourceNodeInstance->GetUserData());

        if (targetNode >= pGraph->GetNodeCount() || sourceNode >= pGraph->GetNodeCount()) {
            return;
        }

        const uint32_t targetPin = pTargetNodeInstance->GetPinIndex(pInputPin);
        const uint32_t sourcePin = pSourceNodeInstance->GetPinIndex(pOutputPin);

        /// входной пин данных принимает только одно значение, а вот входной flow-пин принимает
        /// сколько угодно связей - это и есть точка слияния ветвей исполнения
        if (!pInputPin->GetType().isFlow) {
            pGraph->RemoveInputLink(targetNode, targetPin);
        }

        /// поток исполнения может уходить из выходного пина только в один узел
        if (pOutputPin->GetType().isFlow) {
            pGraph->RemoveOutputLink(sourceNode, sourcePin);
        }

        SR_FLUX_NS::FluxGraphLink graphLink;
        graphLink.SetSourceNode(sourceNode);
        graphLink.SetSourcePin(sourcePin);
        graphLink.SetTargetNode(targetNode);
        graphLink.SetTargetPin(targetPin);

        pGraph->AddLink(graphLink);
    }

    /// ================================================ Панель свойств =================================================

    SR_FLUX_NS::FluxGraphNode* FluxEditor::GetSelectedNode() const {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return nullptr;
        }

        auto&& selectedNodes = m_nodeGraphEditor->GetSelectedNodes();
        if (selectedNodes.size() != 1) {
            return nullptr;
        }

        return pGraph->GetNode(UserDataToIndex(selectedNodes.front()->GetUserData()));
    }

    void FluxEditor::DrawGraphPreviewCode() {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        if (!m_previewCompiled) {
            m_previewCompiled = true;
            pGraph->Compile().SaveToString(m_previewCode);
            SR_UTILS_NS::StringUtils::Instance().SplitView(m_previewCode, "\n", m_previewCodeLines);
        }

        for (auto&& line : m_previewCodeLines) {
            m_previewLine = line;
            SR_GRAPH_GUI_NS::Immediate::Text("%s", m_previewLine.c_str());
        }
    }

    void FluxEditor::DrawInspectPanel() {
        if (!m_graphAsset) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_HINT_COLOR, "Open a flux graph to start editing.");
            return;
        }

        if (m_skipInspect) {
            m_skipInspect = false;
            return;
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginTabBar("InspectorTabs")) {
            if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Inspector")) {
                if (auto&& pNode = GetSelectedNode()) {
                    DrawNodeInspector(*pNode);
                }
                else {
                    DrawGraphInspector();
                }
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Preview code")) {
                DrawGraphPreviewCode();
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
            }
            SR_GRAPH_GUI_NS::Immediate::EndTabBar();
        }
    }

    void FluxEditor::DrawNodeInspector(SR_FLUX_NS::FluxGraphNode& node) {
        SR_GRAPH_GUI_NS::Immediate::Text("Node properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        const auto type = node.GetType();

        SR_GRAPH_GUI_NS::Immediate::Text("Type: %s", SR_UTILS_NS::EnumReflector::ToStringAtom(type).c_str());

        if (HasName(type) && !IsVariableNode(type)) {
            m_nameBuffer = node.GetName().ToStringRef();
            if (SR_GRAPH_GUI_NS::Immediate::InputText("Name", &m_nameBuffer)) {
                node.SetName(SR_UTILS_NS::StringAtom(m_nameBuffer));
            }
        }

        if (IsVariableNode(type)) {
            DrawVariableSelector(node);
        }

        if (HasCallable(type)) {
            DrawCallableInspector(node);
        }

        if (type == SR_FLUX_NS::FluxGraphNodeType::Constant) {
            DrawConstantInspector(node);
        }

        if (type == SR_FLUX_NS::FluxGraphNodeType::Cast) {
            DrawCastInspector(node);
        }
    }

    void FluxEditor::DrawCastInspector(SR_FLUX_NS::FluxGraphNode& node) {
        /// целевой тип каста хранится в имени узла
        m_castTypeBuffer = node.GetName().ToStringRef();
        if (SR_GRAPH_GUI_NS::Immediate::InputText("Target type", &m_castTypeBuffer)) {
            node.SetName(SR_UTILS_NS::StringAtom(m_castTypeBuffer));
        }

        if (node.GetName().empty()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_ERROR_COLOR, "Target type is not specified!");
            return;
        }

        if (!SR_UTILS_NS::Factory::Instance().GetType(node.GetName())) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_ERROR_COLOR, "Unknown class \"%s\"!", node.GetName().c_str());
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_HINT_COLOR, "On success the flow goes to \"Exec\", otherwise to \"Cast Failed\".");
    }

    void FluxEditor::DrawCallableInspector(SR_FLUX_NS::FluxGraphNode& node) {
        const auto callable = node.GetCallable();

        m_objectBuffer = callable.object.ToStringRef();
        if (SR_GRAPH_GUI_NS::Immediate::InputText("Object", &m_objectBuffer)) {
            node.SetCallable({ SR_UTILS_NS::StringAtom(m_objectBuffer), callable.function });
        }

        auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(node.GetCallable().object);
        if (!pMeta) {
            m_functionBuffer = callable.function.ToStringRef();
            if (SR_GRAPH_GUI_NS::Immediate::InputText("Function", &m_functionBuffer)) {
                node.SetCallable({ node.GetCallable().object, SR_UTILS_NS::StringAtom(m_functionBuffer) });
            }
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_ERROR_COLOR, "Unknown class \"%s\"!", node.GetCallable().object.c_str());
            return;
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Function", callable.function.c_str())) {
            pMeta->ForEachMethod([&](const SR_UTILS_NS::Reflection::Method& method, uint64_t) {
                if (SR_GRAPH_GUI_NS::Immediate::Selectable(method.GetName().c_str(), method.GetName() == callable.function)) {
                    node.SetCallable({ node.GetCallable().object, method.GetName() });
                }
            });
            SR_GRAPH_GUI_NS::Immediate::EndCombo();
        }

        if (auto&& pMethod = node.GetCallable().FindMethodMeta()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_HINT_COLOR, "Arguments: %u, returns: %s",
                pMethod->GetParamsCount(), pMethod->HasReturn() ? "yes" : "no"
            );
        }
        else if (!node.GetCallable().function.empty()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_ERROR_COLOR, "Method is not found!");
        }
    }

    void FluxEditor::DrawVariableSelector(SR_FLUX_NS::FluxGraphNode& node) {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Variable", node.GetName().c_str())) {
            for (auto&& [name, value] : pGraph->GetVariables()) {
                if (SR_GRAPH_GUI_NS::Immediate::Selectable(name.c_str(), name == node.GetName())) {
                    node.SetName(name);
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndCombo();
        }

        if (pGraph->GetVariables().count(node.GetName()) == 0) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_ERROR_COLOR, "Variable is not declared in the graph!");
        }
    }

    void FluxEditor::DrawConstantInspector(SR_FLUX_NS::FluxGraphNode& node) {
        const SR_UTILS_NS::StringAtom typeName = GetFluxValueTypeName(node.GetConstant());

        if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Value type", typeName.c_str())) {
            for (auto&& availableType : GetFluxValueTypeNames()) {
                if (SR_GRAPH_GUI_NS::Immediate::Selectable(availableType.c_str(), availableType == typeName)) {
                    if (availableType != typeName) {
                        node.SetConstant(CreateFluxValue(availableType));
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndCombo();
        }

        auto&& constant = node.GetConstantMutable();
        if (!constant.IsValid()) {
            return;
        }

        if (typeName == "bool") {
            SR_GRAPH_GUI_NS::Immediate::Checkbox("Value", constant.Cast<bool>());
        }
        else if (typeName == "float") {
            SR_GRAPH_GUI_NS::Immediate::InputFloat("Value", constant.Cast<float_t>());
        }
        else if (typeName == "double") {
            auto value = static_cast<float_t>(*constant.Cast<double_t>());
            if (SR_GRAPH_GUI_NS::Immediate::InputFloat("Value", &value)) {
                *constant.Cast<double_t>() = static_cast<double_t>(value);
            }
        }
        else if (typeName == "String") {
            m_nameBuffer = *constant.Cast<SR_UTILS_NS::String>();
            if (SR_GRAPH_GUI_NS::Immediate::InputText("Value", &m_nameBuffer)) {
                *constant.Cast<SR_UTILS_NS::String>() = SR_UTILS_NS::String(m_nameBuffer);
            }
        }
        else if (typeName == "int32_t") {
            SR_GRAPH_GUI_NS::Immediate::InputInt("Value", constant.Cast<int32_t>());
        }
        else if (typeName == "int64_t" || typeName == "uint32_t" || typeName == "uint64_t") {
            auto value = static_cast<int32_t>(typeName == "int64_t" ? *constant.Cast<int64_t>() :
                (typeName == "uint32_t" ? static_cast<int64_t>(*constant.Cast<uint32_t>()) : static_cast<int64_t>(*constant.Cast<uint64_t>()))
            );
            if (SR_GRAPH_GUI_NS::Immediate::InputInt("Value", &value)) {
                if (typeName == "int64_t") { *constant.Cast<int64_t>() = value; }
                else if (typeName == "uint32_t") { *constant.Cast<uint32_t>() = static_cast<uint32_t>(SR_MAX(value, 0)); }
                else { *constant.Cast<uint64_t>() = static_cast<uint64_t>(SR_MAX(value, 0)); }
            }
        }
    }

    void FluxEditor::DrawGraphInspector() {
        auto&& pGraph = GetGraph();
        if (!pGraph) {
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Graph variables");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_UTILS_NS::StringAtom variableToRemove;

        for (auto&& [name, value] : pGraph->GetVariables()) {
            SR_GRAPH_GUI_NS::Immediate::PushID(name.c_str());

            SR_GRAPH_GUI_NS::Immediate::Text("%s : %s", name.c_str(), GetFluxValuePreview(value).c_str());
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            if (SR_GRAPH_GUI_NS::Immediate::Button("X")) {
                variableToRemove = name;
            }

            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        if (!variableToRemove.empty()) {
            pGraph->GetVariables().erase(variableToRemove);
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_GRAPH_GUI_NS::Immediate::InputText("##NewVariable", &m_newVariableName);

        for (auto&& typeName : GetFluxValueTypeNames()) {
            SR_GRAPH_GUI_NS::Immediate::PushID(typeName.c_str());
            if (SR_GRAPH_GUI_NS::Immediate::Button(typeName.c_str())) {
                if (m_newVariableName.empty()) {
                    SR_WARN("FluxEditor::DrawGraphInspector() : variable name is empty!");
                }
                else {
                    pGraph->GetVariables()[SR_UTILS_NS::StringAtom(m_newVariableName)] = CreateFluxValue(typeName);
                    m_newVariableName.clear();
                }
            }
            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();
        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_FLUX_HINT_COLOR, "Select a node to edit its properties.");
    }

    /// ================================================= Верхняя панель ================================================

    void FluxEditor::TopPanelSave() {
        if (!m_graphAsset) {
            return;
        }

        if (!m_graphAsset->SaveAsset()) {
            SR_ERROR("FluxEditor::TopPanelSave() : failed to save asset \"{}\"!", m_graphAsset->GetResourcePath());
        }
    }

    void FluxEditor::TopPanelOpen() {
        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(
            SR_UTILS_NS::ResourceManager::Instance().GetResPath(),
            { { "Flux", "flux" } }
        );

        if (path.empty()) {
            return;
        }

        Inspect(path);
    }

    void FluxEditor::Execute() {
        if (!m_graphAsset) {
            return;
        }

        m_graphAsset->Invalidate();

        auto&& pProgram = m_graphAsset->Compile();
        if (!pProgram) {
            SR_ERROR("FluxEditor::Execute() : failed to compile graph!");
            return;
        }

        SR_UTILS_NS::String programStr;
        pProgram->SaveToString(programStr);
        SR_LOG("FluxEditor::Execute() : compiled program:\n{}", programStr);

        if (pProgram->labels.empty()) {
            SR_WARN("FluxEditor::Execute() : graph has no events to execute!");
            return;
        }

        SR_FLUX_NS::FluxRuntime runtime(pProgram);
        if (!runtime.Initialize()) {
            SR_ERROR("FluxEditor::Execute() : failed to initialize runtime!");
            return;
        }

        const SR_UTILS_NS::String& labelName = pProgram->labels.front().name;
        SR_LOG("FluxEditor::Execute() : emitting event \"{}\"...", labelName);

        runtime.Emit(labelName, {}, false);

        /// программа исполняется по тикам, поэтому крутим её до завершения всех точек входа
        for (uint32_t tick = 0; tick < 16 && !runtime.m_executions.empty(); ++tick) {
            runtime.Update(runtime.m_tickDuration);
        }
    }
}
