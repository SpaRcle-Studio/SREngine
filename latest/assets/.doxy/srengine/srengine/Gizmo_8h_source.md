

# File Gizmo.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**UI**](dir_4db2cc8eada578aa57e9f12bf4119b9f.md) **>** [**Gizmo.h**](Gizmo_8h.md)

[Go to the documentation of this file](Gizmo_8h.md)


```C++
//
// Created by Monika on 23.11.2023.
//

#ifndef SR_ENGINE_GRAPHICS_MANIPULATION_TOOL_H
#define SR_ENGINE_GRAPHICS_MANIPULATION_TOOL_H

#include <Graphics/Types/Geometry/MeshComponent.h>
#include <Graphics/Types/IRenderComponent.h>

namespace SR_GRAPH_UI_NS {
    SR_ENUM_NS_CLASS_T(GizmoMode, uint8_t, Local, Global);

    SR_ENUM_NS_STRUCT_T(GizmoOperation, uint64_t,
        None = 0,
        Center = 1 << 0,
        Alternative = 1 << 1,

        X = 1 << 2,
        Y = 1 << 3,
        Z = 1 << 4,

        Translate = 1 << 5,
        Rotate = 1 << 6,
        Scale = 1 << 7,
        Bounds = 1 << 8,

        Space2D = 1 << 9,

        Rotate2D = Space2D | Rotate | Z,

        TranslateX = X | Translate,
        TranslateY = Y | Translate,
        TranslateZ = Z | Translate,
        TranslateAltX = Y | Z | Translate | Alternative,
        TranslateAltY = X | Z | Translate | Alternative,
        TranslateAltZ = X | Y | Translate | Alternative,
        TranslateCenter = Translate | Center,
        TranslateAll = X | Y | Z | Translate | Center | Alternative,

        RotateX = X | Rotate,
        RotateY = Y | Rotate,
        RotateZ = Z | Rotate,
        RotateCenter = Rotate | Center,
        RotateAll = X | Y | Z | Rotate | Center,

        ScaleX = X | Scale,
        ScaleY = Y | Scale,
        ScaleZ = Z | Scale,
        ScaleCenter = Scale | Center,
        ScaleAll = X | Y | Z | Scale | Center,

        BoundsX = X | Bounds,
        BoundsY = Y | Bounds,
        BoundsZ = Z | Bounds,

        Universal = TranslateAll | RotateAll | ScaleAll
    );

    class Gizmo : public SR_GTYPES_NS::IRenderComponent {
        SR_CLASS()
        using Super = SR_GTYPES_NS::IRenderComponent;
        enum class GizmoMeshLoadMode {
            Visual, Selection, All
        };
    public:
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDestroy() override;
        void FixedUpdate() override;

        SR_NODISCARD bool IsGizmoEnabled() const {
            return SR_MATH_NS::IsAnyMaskIncludedSubMask(m_operation, { GizmoOperation::Translate, GizmoOperation::Rotate, GizmoOperation::Scale, GizmoOperation::Bounds });
        }

        SR_NODISCARD bool IsGizmoActive() const {
            return SR_MATH_NS::IsAnyMaskIncludedSubMask(m_activeOperation, { GizmoOperation::Translate, GizmoOperation::Rotate, GizmoOperation::Scale, GizmoOperation::Bounds });
        }

        SR_NODISCARD bool IsGizmoHovered() const {
            return SR_MATH_NS::IsAnyMaskIncludedSubMask(m_hoveredOperation, { GizmoOperation::Translate, GizmoOperation::Rotate, GizmoOperation::Scale, GizmoOperation::Bounds });
        }

        SR_NODISCARD bool IsGizmo2DSpace() const {
            return SR_MATH_NS::IsMaskIncludedSubMask(m_operation, GizmoOperation::Space2D);
        }

        void SetMode(GizmoMode mode) { m_mode = mode; }
        void SetOperation(GizmoOperation operation);

        SR_NODISCARD virtual GizmoMode GetMode() const { return m_mode; }
        SR_NODISCARD virtual GizmoOperation GetOperation() const { return m_operation; }

    protected:
        void ProcessGizmo(const SR_MATH_NS::FPoint& mousePos);
        void LoadGizmo();
        void ReleaseGizmo();
        void LoadMesh(GizmoOperation operation, SR_UTILS_NS::StringAtom path, SR_UTILS_NS::StringAtom name, GizmoMeshLoadMode mode);
        void UpdateGizmoTransform();

        virtual void PrepareGizmo() { }

        virtual void OnGizmoTranslated(const SR_MATH_NS::FVector3& delta);
        virtual void OnGizmoScaled(const SR_MATH_NS::FVector3& delta);
        virtual void OnGizmoRotated(const SR_MATH_NS::Quaternion& delta);

        virtual void BeginGizmo() { }
        virtual void EndGizmo() { }

        SR_NODISCARD virtual bool IsGizmoAvailable() const { return true; }
        SR_NODISCARD virtual bool IsHandledAnotherObject() const { return false; }
        SR_NODISCARD virtual SR_MATH_NS::Matrix4x4 GetGizmoMatrix() const;
        SR_NODISCARD bool IsLocal() const { return GetMode() == GizmoMode::Local; }

        SR_NODISCARD GameObjectPtr GetGameObjectByOperation(GizmoMeshLoadMode mode, GizmoOperation operation) const;

        SR_NODISCARD SR_MATH_NS::Axis GetAxis() const;

        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }

        SR_NODISCARD SR_MATH_NS::FColor GetColorByOperation(GizmoOperation operation) const;

    private:
        struct MeshInfo {
            SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Mesh> pVisual;
            SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Mesh> pSelection;
            bool isHovered = false;
        };
        std::map<GizmoOperation, MeshInfo> m_meshes;

        bool m_isGizmoDirty = false;

        float_t m_zoomFactor = 0.0665f;
        float_t m_moveFactor = 0.1f;

        SR_MATH_NS::FPoint m_lastMousePos = SR_MATH_NS::InfinityFV2;

        GizmoMode m_mode = GizmoMode::Local;
        GizmoOperation m_operation = GizmoOperation::TranslateAll;

        GizmoOperation m_activeOperation = GizmoOperation::None;
        GizmoOperation m_hoveredOperation = GizmoOperation::None;

        SR_MATH_NS::FVector3 m_translationPlanOrigin;
        SR_MATH_NS::FVector3 m_relativeOrigin;
        SR_MATH_NS::FVector3 m_rotationVectorSource;
        SR_MATH_NS::FVector4 m_translationPlan;
        SR_MATH_NS::FVector4 m_rotationPlan;
        SR_MATH_NS::Matrix4x4 m_modelMatrix;

        SR_MATH_NS::Unit m_rotationAngleOrigin = 0.f;

    };
}

#endif //SR_ENGINE_GRAPHICS_MANIPULATION_TOOL_H
```


