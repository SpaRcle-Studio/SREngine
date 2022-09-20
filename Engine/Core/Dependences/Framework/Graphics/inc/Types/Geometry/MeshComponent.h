//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_MESHCOMPONENT_H
#define SRENGINE_MESHCOMPONENT_H

#include <Utils/ECS/Component.h>
#include <Types/Geometry/IndexedMesh.h>

namespace SR_GTYPES_NS {
    class MeshComponent : public IndexedMesh, public SR_UTILS_NS::Component {
    protected:
        ~MeshComponent() override = default;

        explicit MeshComponent(MeshType type)
            : IndexedMesh(type)
        { }

    public:
        SR_MATH_NS::FVector3 GetBarycenter() const override;

        void OnAttached() override;
        void OnDestroy() override;
        void OnMatrixDirty() override;
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD bool ExecuteInEditMode() const override;
        SR_NODISCARD SR_FORCE_INLINE bool IsCanUpdate() const noexcept override { return false; }

        SR_NODISCARD SR_FORCE_INLINE bool IsMeshActive() const noexcept override {
            return SR_UTILS_NS::Component::IsActive();
        }

    protected:
        SR_NODISCARD RenderScenePtr GetRenderScene();

    protected:
        RenderScenePtr m_renderScene;

    };
}

#endif //SRENGINE_MESHCOMPONENT_H
