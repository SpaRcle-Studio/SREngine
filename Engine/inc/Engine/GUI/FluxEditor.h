//
// Created by Monika on 18.08.2026.
//

#ifndef SR_ENGINE_CORE_GUI_FLUX_EDITOR_H
#define SR_ENGINE_CORE_GUI_FLUX_EDITOR_H

#include <Engine/GUI/PropertyDrawer.h>

#include <Graphics/GUI/NodeWidget.h>

#include <Utils/Flux/Graph/FluxGraph.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;

    class FluxEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
    public:
        FluxEditor();
        ~FluxEditor() override = default;

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

    protected:
        SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer> m_propertyDrawer;
        SR_UTILS_NS::Subscription m_doInspectEntitySubscription;
        SR_UTILS_NS::Subscription m_onCommandUndoSubscription;
        SR_UTILS_NS::Subscription m_onCommandRedoSubscription;
        SR_UTILS_NS::String m_backgroundText;

    };
}

#endif //SR_ENGINE_CORE_GUI_FLUX_EDITOR_H
