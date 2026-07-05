//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/Animations/AnimationGraph.h>

#include <Utils/Types/SharedPtr.h>

namespace SR_ANIMATIONS_NS {
    class Animator;
}

namespace SR_CORE_GUI_NS {
    class AnimatorEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
        using AnimatorPtr = SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Animator>;
        using GraphPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Animations::AnimationGraph>;
    public:
        AnimatorEditor();
        ~AnimatorEditor() override = default;

    public:
        void SetGraphPath(const SR_UTILS_NS::Path& path);

        void Init() override;
        void Draw() override;
        void OnOpen() override;
        void OnClose() override;

    protected:
        void DrawNodeEditor() override;
        void DrawLeftPanel() override;
        void DrawPopupMenu() override;
        
        void TopPanelSave() override;
        void TopPanelOpen() override;
        
        void SyncGraphToVisualNodes();
        void SyncVisualNodesToGraph();
        
        SR_GRAPH_GUI_NS::Node* CreateVisualNode(SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);
        void UpdateVisualNode(SR_GRAPH_GUI_NS::Node* pVisualNode, SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode);

    protected:
        void InitNodeTypes();
        void BuildNodeMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);
        
        SR_MATH_NS::FColor GetPinColor(SR_SRLM_NS::DataTypeClass pinType);
        
    protected:
        GraphPtr m_graph;
        SR_UTILS_NS::Path m_graphPath;
        
        // Маппинг между граф-нодами и визуальными нодами
        std::map<uint64_t, SR_GRAPH_GUI_NS::Node*> m_graphNodeToVisual;
        std::map<SR_GRAPH_GUI_NS::Node*, uint64_t> m_visualToGraphNode;
        
        // Кэш доступных типов нод
        std::vector<SR_UTILS_NS::StringAtom> m_availableNodeTypes;

    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_H
