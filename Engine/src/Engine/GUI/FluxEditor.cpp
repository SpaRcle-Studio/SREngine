//
// Created by Monika on 18.08.2026.
//

#include <Engine/GUI/FluxEditor.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/EngineCommands.h>

#include <Utils/Flux/Runtime/FluxComponent.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/FluxEditor.generated.hpp>

namespace SR_CORE_GUI_NS {
    FluxEditor::FluxEditor()
        : Super("Flux")
    { }

    void FluxEditor::Inspect(const SR_UTILS_NS::Path& path) {
        m_graphAsset = CoreResLoader::Load<SR_FLUX_NS::FluxGraphAsset>(path);
    }

    void FluxEditor::Init() {
        m_doInspectEntitySubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_DO_INSPECT_ENTITY_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            if (msg.GetStringAtom("ClassName") != SR_FLUX_NS::FluxComponent::GetClassStaticName()) {
                return;
            }
            const auto entityId = msg.GetInt("EntityId");
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& pEntity = pEngine->GetScene()->GetEntityController()->FindById(entityId);
            if (!pEntity) {
                SR_ERROR("AnimatorEditor::Init() : failed to find entity with id: {}", entityId);
                return;
            }
            if (auto&& pFlux = pEntity.DynamicCast<SR_FLUX_NS::FluxComponent>()) {
                Inspect(pFlux->GetGraphPath());
            }
        });

        SR_FLUX_NS::FluxGraph graph;

        SR_FLUX_NS::FluxGraphNode entryNode;
        entryNode.SetType(SR_FLUX_NS::FluxGraphNodeType::Event);
        entryNode.SetName("Entry");
        graph.AddNode(entryNode);

        SR_FLUX_NS::FluxGraphNode constNode;
        constNode.SetType(SR_FLUX_NS::FluxGraphNodeType::Constant);
        constNode.SetConstant(SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::String("Hello, Flux!")));
        graph.AddNode(constNode);

        SR_FLUX_NS::FluxGraphNode callNode;
        callNode.SetType(SR_FLUX_NS::FluxGraphNodeType::Invoke);
        callNode.SetCallable({ "Debug", "Log" });
        graph.AddNode(callNode);

        SR_FLUX_NS::FluxGraphLink link;
        link.SetSourceNode(0); // Entry node
        link.SetSourcePin(0);  // Flow output pin
        link.SetTargetNode(2); // Call node
        link.SetTargetPin(0);  // Flow input pin
        graph.AddLink(link);

        link.SetSourceNode(1); // Constant node
        link.SetSourcePin(0);  // Constant output pin
        link.SetTargetNode(2); // Call node
        link.SetTargetPin(1);  // Argument input pin
        graph.AddLink(link);

        auto&& program = graph.Compile();

        SR_UTILS_NS::String programStr;
        program.SaveToString(programStr);
        SR_LOG("FLUX Program:\n{}", programStr);
        Super::Init();
    }

    void FluxEditor::DrawNodeEditor() {
        m_backgroundText = "Flux";

        const auto size = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        if (SR_IMMEDIATE_GUI_NS::BeginChild("Node Editor")) {
            SyncLogicToVisual();
            m_nodeGraphEditor->SetStyleType(SR_IMMEDIATE_GUI_NS::NodeEditorStyleType::Graph);
            m_nodeGraphEditor->SetBackgroundText(m_backgroundText);
            m_nodeGraphEditor->SetSize(size);
            m_nodeGraphEditor->Draw();
            SyncVisualToLogic();
            SR_IMMEDIATE_GUI_NS::EndChild();
        }

        if (m_serializer && !SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseLeft)) {
            //auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            //auto&& cmd = new SR_CORE_NS::Commands::SerializableChange(pEngine, SR_UTILS_NS::SharedPtrBaseHolder(&m_pActiveGraph), std::move(m_serializer));
            //pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void FluxEditor::DrawInspectPanel() {

    }

    void FluxEditor::TopPanelSave() {

    }

    void FluxEditor::TopPanelOpen() {

    }

    void FluxEditor::SyncLogicToVisual() {

    }

    void FluxEditor::SyncVisualToLogic() {

    }

    void FluxEditor::OnNodeTypeSelected(SR_UTILS_NS::StringAtom type, SR_MATH_NS::FVector2 pos) {

    }
}