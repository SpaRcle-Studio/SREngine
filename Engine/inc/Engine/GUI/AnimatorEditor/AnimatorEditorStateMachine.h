//
// Created by Monika on 06.07.2026.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H

#include <Engine/GUI/AnimatorEditor/AnimatorEditorContext.h>

#include <Graphics/GUI/Node.h>

namespace SR_CORE_GUI_NS {
    class AnimatorEditorStateMachine {
    public:
        AnimatorEditorStateMachine(AnimatorEditorContext& context)
            : m_context(context)
        { }

        void DrawStateMachineEditor();
        void SyncStateMachineToVisual();
        void SyncVisualToStateMachine();
        void ClearStateMachineVisual();
        void InitStateTypes();

        SR_NODISCARD SR_UTILS_NS::SRClass* GetSelectedObject(uintptr_t nodeId) const;

    private:
        void BuildStateMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories);
        void DrawStateMenuRecursive(bool& needResync, const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix);

    private:
        AnimatorEditorContext& m_context;

        SR_MATH_NS::FVector2 m_popupMousePos;
        std::string m_createStateSearch;

        std::vector<SR_UTILS_NS::StringAtom> m_availableStateTypes;

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

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_STATE_MACHINE_H
