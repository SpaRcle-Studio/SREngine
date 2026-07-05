//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/Animations/AnimationGraph.h>

#include <Utils/Resources/Asset.h>
#include <Utils/Types/SharedPtr.h>

#include <unordered_set>
#include <map>

namespace SR_ANIMATIONS_NS {
    class Animator;
}

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;

    class AnimatorEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
        using AnimatorPtr = SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Animator>;
        using GraphPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Animations::AnimationGraph>;
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
        void DrawStateMachineEditor();

        void SyncStateMachineToVisual();
        void SyncVisualToStateMachine();
        void ClearStateMachineVisual();
        
        SR_GRAPH_GUI_NS::Node* CreateVisualNode(SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);
        void UpdateVisualNode(SR_GRAPH_GUI_NS::Node* pVisualNode, SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);

    protected:
        void InitNodeTypes();
        void InitStateTypes();
        void BuildNodeMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);

        void BuildStateMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawStateMenuRecursive(bool& needResync, const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);
        
        SR_MATH_NS::FColor GetPinColor(SR_SRLM_NS::DataTypeClass pinType);
        
    protected:
        SR_UTILS_NS::Subscription m_doInspectEntitySubscription;
        GraphPtr m_graph;
        SR_UTILS_NS::Asset::Ptr m_asset;
        SR_GRAPH_NS::Animations::AnimationGraphAsset::Ptr m_graphAsset;
        SR_UTILS_NS::Path m_graphPath;

        SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer> m_propertyDrawer;

        AnimatorPtr m_animator;
        bool m_isLive = false;
        bool m_liveReadOnly = true;
        bool m_keepLiveContext = false;
        SR_ANIMATIONS_NS::AnimationGraph* m_runtimeGraph = nullptr;

        Tab m_tab = Tab::Graph;
        void* m_stateMachineEditor = nullptr;
        uint64_t m_openedStateMachineNodeIndex = SR_ID_INVALID;
        bool m_openStateMachineRequested = false;
        
        // Маппинг между граф-нодами и визуальными нодами
        std::map<uint64_t, SR_GRAPH_GUI_NS::Node*> m_graphNodeToVisual;
        std::map<SR_GRAPH_GUI_NS::Node*, uint64_t> m_visualToGraphNode;
        
        // Кэш доступных типов нод
        std::vector<SR_UTILS_NS::StringAtom> m_availableNodeTypes;
        std::vector<SR_UTILS_NS::StringAtom> m_availableStateTypes;

        std::string m_createNodeSearch;
        std::string m_createStateSearch;

        // Live overlay cache (graph)
        std::unordered_set<uint64_t> m_activeGraphNodes;
        std::unordered_set<uintptr_t> m_activeGraphLinks;

        // Visual state machine (separate editor)
        std::map<uintptr_t, SR_GRAPH_GUI_NS::Node*> m_smNodes;
        std::map<uintptr_t, SR_GRAPH_GUI_NS::Link*> m_smLinks;
        std::map<uint32_t, SR_GRAPH_GUI_NS::Node*> m_stateIndexToVisual;
        std::map<SR_GRAPH_GUI_NS::Node*, uint32_t> m_visualToStateIndex;
        std::map<uintptr_t, std::pair<uint32_t, uint32_t>> m_smLinkToTransition;
        std::map<uintptr_t, SR_MATH_NS::FRect> m_smNodeRects;

        // State machine transition creation (context-menu + click target)
        int32_t m_smCreateTransitionFrom = -1;

    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_H
