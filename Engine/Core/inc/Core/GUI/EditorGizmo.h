//
// Created by Monika on 03.02.2024.
//

#ifndef SR_ENGINE_EDITOR_GIZMO_H
#define SR_ENGINE_EDITOR_GIZMO_H

#include <Graphics/UI/Gizmo.h>

namespace SR_CORE_GUI_NS {
    class Hierarchy;

    class EditorGizmo final : public SR_GRAPH_UI_NS::Gizmo {
        SR_ENTITY_SET_VERSION(1000);
        using Super = SR_GRAPH_UI_NS::Gizmo;
    public:
        explicit EditorGizmo(Hierarchy* pHierarchy);

    public:
        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }

    private:
        Hierarchy* m_hierarchy = nullptr;

    };
}

#endif //SR_ENGINE_EDITOR_GIZMO_H
