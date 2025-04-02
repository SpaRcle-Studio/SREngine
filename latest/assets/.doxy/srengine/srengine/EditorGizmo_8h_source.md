

# File EditorGizmo.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**EditorGizmo.h**](EditorGizmo_8h.md)

[Go to the documentation of this file](EditorGizmo_8h.md)


```C++
//
// Created by Monika on 03.02.2024.
//

#ifndef SR_ENGINE_EDITOR_GIZMO_H
#define SR_ENGINE_EDITOR_GIZMO_H

#include <Graphics/UI/Gizmo.h>

namespace SR_CORE_GUI_NS {
    class Hierarchy;

    class EditorGizmo final : public SR_GRAPH_UI_NS::Gizmo {
        SR_CLASS()
        using Super = SR_GRAPH_UI_NS::Gizmo;
    public:
        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }

        void SetHierarchy(Hierarchy* pHierarchy) { m_hierarchy = pHierarchy; }

        SR_NODISCARD SR_MATH_NS::Matrix4x4 GetGizmoMatrix() const override;
        SR_NODISCARD bool IsHandledAnotherObject() const override { return true; }
        SR_NODISCARD bool IsGizmoAvailable() const override;

        SR_NODISCARD SR_GRAPH_UI_NS::GizmoMode GetMode() const override;

        void OnGizmoTranslated(const SR_MATH_NS::FVector3& delta) override;
        void OnGizmoScaled(const SR_MATH_NS::FVector3& delta) override;
        void OnGizmoRotated(const SR_MATH_NS::Quaternion& delta) override;

        void PrepareGizmo() override;
        void BeginGizmo() override;
        void EndGizmo() override;

    private:
        Hierarchy* m_hierarchy = nullptr;
        SR_UTILS_NS::ISerializer::UniquePtr m_pSerializer;

    };
}

#endif //SR_ENGINE_EDITOR_GIZMO_H
```


