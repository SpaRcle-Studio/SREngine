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
        None = 1 << 0,
        Center = 1 << 1,
        Alternative = 1 << 2,

        X = 1 << 3,
        Y = 1 << 4,
        Z = 1 << 5,

        TranslateX = X | 1 << 6,
        TranslateY = Y | 1 << 7,
        TranslateZ = Z | 1 << 8,
        TranslateAltX = X | Alternative,
        TranslateAltY = Y | Alternative,
        TranslateAltZ = Z | Alternative,
        Translate = TranslateX | TranslateAltX | TranslateY | TranslateAltY | TranslateZ | TranslateAltZ,

        RotateX = X | 1 << 9,
        RotateY = Y | 1 << 10,
        RotateZ = Z | 1 << 11,
        Rotate = RotateX | RotateY | RotateZ,

        ScaleX = X | 1 << 12,
        ScaleY = Y | 1 << 13,
        ScaleZ = Z | 1 << 14,
        Scale = ScaleX | ScaleY | ScaleZ,

        BoundsX = X | 1 << 15,
        BoundsY = Y | 1 << 16,
        BoundsZ = Z | 1 << 17,
        Bounds = BoundsX | BoundsY | BoundsZ,

        Universal = Translate | Rotate | Scale
    );

    class Gizmo : public SR_GTYPES_NS::IRenderComponent {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Gizmo);
        using Super = SR_GTYPES_NS::IRenderComponent;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDestroy() override;
        void Update(float_t dt) override;

        SR_NODISCARD SR_FORCE_INLINE virtual bool ExecuteInEditMode() const { return true; }

    protected:
        void LoadGizmo();
        void ReleaseGizmo();
        void LoadMesh(GizmoOperationFlag operation, SR_UTILS_NS::StringAtom path, SR_UTILS_NS::StringAtom name);

    private:
        std::map<GizmoOperationFlag, SR_GTYPES_NS::MeshComponent::Ptr> m_meshes;

        GizmoMode m_mode = GizmoMode::Local;
        GizmoOperationFlag m_operation = GizmoOperation::Universal;

    };
}

#endif //SR_ENGINE_GRAPHICS_MANIPULATION_TOOL_H
