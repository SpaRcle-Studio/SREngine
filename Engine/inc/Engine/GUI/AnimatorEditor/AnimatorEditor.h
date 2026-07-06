//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_H

#include <Engine/GUI/AnimatorEditor/AnimatorEditorStateMachine.h>

#include <Graphics/GUI/NodeWidget.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;

    class AnimatorEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
        using AnimatorPtr = SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Animator>;
        enum class Tab : uint8_t {
            Graph,
            StateMachine
        };
    public:
        AnimatorEditor();
        ~AnimatorEditor() override = default;

    public:
        void Inspect(const SR_UTILS_NS::Path& path);

        void Init() override;
        void Draw() override;
        void OnOpen() override;
        void OnClose() override;

        void Zoom() override;

    protected:
        void DrawNodeEditor() override;
        void DrawLeftPanel() override;
        void DrawPopupMenu() override;
        
        void TopPanelSave() override;
        void TopPanelOpen() override;
        
        void SyncGraphToVisualNodes();
        void SyncVisualNodesToGraph();

        void DrawGraphEditor();
        
        SR_GRAPH_GUI_NS::Node* CreateVisualNode(SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);
        void UpdateVisualNode(SR_GRAPH_GUI_NS::Node* pVisualNode, SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);

    protected:
        void InitNodeTypes();
        void BuildNodeMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);

        SR_MATH_NS::FColor GetPinColor(SR_SRLM_NS::DataTypeClass pinType);
        
    protected:
        AnimatorEditorContext m_context;
        AnimatorEditorStateMachine m_editorStateMachine;

        SR_UTILS_NS::Subscription m_doInspectEntitySubscription;
        SR_UTILS_NS::Asset::Ptr m_asset;
        SR_GRAPH_NS::Animations::AnimationGraphAsset::Ptr m_graphAsset;
        SR_UTILS_NS::Path m_graphPath;

        SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer> m_propertyDrawer;

        AnimatorPtr m_animator;

        bool m_keepLiveContext = false;

        Tab m_tab = Tab::Graph;

        // Маппинг между граф-нодами и визуальными нодами
        std::map<SR_ANIMATIONS_NS::AnimationGraphNode*, SR_GRAPH_GUI_NS::Node*> m_graphNodeToVisual;
        std::map<SR_GRAPH_GUI_NS::Node*, SR_ANIMATIONS_NS::AnimationGraphNode*> m_visualToGraphNode;
        
        // Кэш доступных типов нод
        std::vector<SR_UTILS_NS::StringAtom> m_availableNodeTypes;

        std::string m_createNodeSearch;

        SR_MATH_NS::FVector2 m_popupMousePos;

        // Live overlay cache (graph)
        std::unordered_set<uint64_t> m_activeGraphNodes;
        std::unordered_set<uintptr_t> m_activeGraphLinks;
    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_H
