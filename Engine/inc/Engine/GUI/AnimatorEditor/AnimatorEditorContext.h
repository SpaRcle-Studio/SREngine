//
// Created by Monika on 06.07.2026.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_CONTEXT_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_CONTEXT_H

#include <Engine/stdInclude.h>

#include <Graphics/Animations/AnimationGraph.h>

#include <Utils/Types/SharedPtr.h>

namespace SR_ANIMATIONS_NS {
    class Animator;
}

namespace SR_CORE_GUI_NS {
    struct AnimatorEditorContext {
        using GraphPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Animations::AnimationGraph>;

        uint64_t openedStateMachineNodeIndex = SR_ID_INVALID;
        GraphPtr pGraph;
        void* pStateMachineEditor = nullptr;
        SR_ANIMATIONS_NS::AnimationGraph* pRuntimeGraph = nullptr;
        bool openStateMachineRequested = false;
        bool isLive = false;
        bool liveReadOnly = true;

    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_CONTEXT_H
