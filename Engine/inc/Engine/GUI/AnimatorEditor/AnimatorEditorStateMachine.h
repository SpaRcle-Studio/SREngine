//
// Created by Monika on 06.07.2026.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H

#include <Engine/GUI/AnimatorEditor/AnimatorEditorContext.h>

#include <Graphics/GUI/NodeWidget.h>

#include <Graphics/GUI/Node.h>

namespace SR_ANIMATIONS_NS {
    class AnimationStateMachine;
}

namespace SR_CORE_GUI_NS {
    class AnimatorEditorStateMachine : public SR_GRAPH_GUI_NS::NodeWidget {
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
    public:
        AnimatorEditorStateMachine(AnimatorEditorContext& context)
            : m_context(context)
        { }

        void DrawStateMachineEditor();
        void SyncStateMachineToVisual();
        void SyncVisualToStateMachine();
        void ClearStateMachineVisual();
        void InitStateTypes();
        void ResetSelectedLink();

        SR_NODISCARD SR_UTILS_NS::SRClass* GetSelectedNode(uintptr_t nodeId) const;
        SR_NODISCARD SR_UTILS_NS::SRClass* GetSelectedLink() const;

    private:
        void DrawNodes(bool& needResync, SR_ANIMATIONS_NS::AnimationStateMachine& machine);
        void DrawLinks(bool& needResync, SR_ANIMATIONS_NS::AnimationStateMachine& machine);
        void BuildStateMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawStateMenuRecursive(bool& needResync, const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);

    private:
        AnimatorEditorContext& m_context;

        SR_MATH_NS::FRect m_nodeEditorRegion;
        SR_MATH_NS::FVector2 m_popupMousePos;
        SR_GRAPH_GUI_NS::Node* m_fromStateNode = nullptr;
        SR_GRAPH_GUI_NS::Node* m_popupNode = nullptr;
        SR_GRAPH_GUI_NS::Link* m_selectedLink = nullptr;
        std::string m_createStateSearch;

        std::vector<SR_UTILS_NS::StringAtom> m_availableStateTypes;

    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H
