//
// Created by Monika on 03.02.2024.
//

#ifndef SR_ENGINE_EDITOR_GIZMO_H
#define SR_ENGINE_EDITOR_GIZMO_H

#include <Engine/stdInclude.h>

#include <Graphics/UI/Gizmo.h>

namespace SR_CORE_GUI_NS {
    class Hierarchy;

    /// @category(Editor)
    class EditorGizmo final : public SR_GRAPH_UI_NS::Gizmo {
        SR_CLASS()
        using Super = SR_GRAPH_UI_NS::Gizmo;
    public:
        ~EditorGizmo() override;

        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }

        void SetHierarchy(Hierarchy* pHierarchy) { m_hierarchy = pHierarchy; }

        SR_NODISCARD SR_MATH_NS::Matrix4x4 GetGizmoMatrix() const override;
        SR_NODISCARD bool IsHandledAnotherObject() const override { return true; }
        SR_NODISCARD bool IsGizmoAvailable() const override;

        SR_NODISCARD SR_GRAPH_UI_NS::GizmoMode GetMode() const override;

        void OnGizmoTranslated(const SR_MATH_NS::FVector3& delta) override;
        void OnGizmoScaled(const SR_MATH_NS::FVector3& delta) override;
        void OnGizmoRotated(const SR_MATH_NS::Quaternion& delta) override;

        void Update(float_t dt) override;

        void PrepareGizmo() override;
        void BeginGizmo() override;
        void EndGizmo() override;

    private:
        bool m_holding = false;
        Hierarchy* m_hierarchy = nullptr;
        std::vector<std::pair<uint64_t, std::unique_ptr<SR_UTILS_NS::ISerializer>>> m_pSerializers;

    };
}

#endif //SR_ENGINE_EDITOR_GIZMO_H
