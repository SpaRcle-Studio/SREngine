//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_GUI_ANIMATOR_EDITOR_H
#define SR_ENGINE_GUI_ANIMATOR_EDITOR_H

#include <Engine/GUI/AnimatorEditor/AnimatorEditorStateMachine.h>

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/Animations/AnimationGraphNode.h>

#include <Utils/Resources/Asset.h>
#include <Utils/Types/WeakPtr.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;

    class AnimatorEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
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

    protected:
        void DrawNodeEditor() override;
        void DrawInspectPanel() override;

        void TopPanelSave() override;
        void TopPanelOpen() override;

        void SyncLogicToVisual();
        void SyncVisualToLogic();

        void OnNodeTypeSelected(SR_UTILS_NS::StringAtom type, SR_MATH_NS::FVector2 pos) override;

        SR_NODISCARD bool IsStateMachineActive() const { return m_tab == Tab::StateMachine && m_pActiveStateMachine; }

    protected:
        SR_ANIMATIONS_NS::AnimationGraph::Ptr m_pActiveGraph;
        SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Animator> m_animator;
        SR_HTYPES_NS::WeakPtr<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine> m_pActiveStateMachine;

        SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer> m_propertyDrawer;
        SR_UTILS_NS::Subscription m_doInspectEntitySubscription;
        SR_UTILS_NS::Subscription m_onCommandUndoSubscription;
        SR_UTILS_NS::Subscription m_onCommandRedoSubscription;
        SR_UTILS_NS::String m_backgroundText;

        bool m_skipInspect = false;
        bool m_skipSync = false;
        bool m_keepLiveContext = false;
        bool m_live = false;

        Tab m_tab = Tab::Graph;
        Tab m_nodeSearchTabCached = Tab::Graph;

    };
}

#endif //SR_ENGINE_GUI_ANIMATOR_EDITOR_H
