//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_MESHCOMPONENT_H
#define SRENGINE_MESHCOMPONENT_H

#include <Utils/ECS/Component.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>

namespace SR_GTYPES_NS {
    class MeshComponent : public IndexedMesh, public SR_UTILS_NS::Component {
    protected:
        ~MeshComponent() override = default;

        explicit MeshComponent(MeshType type)
            : IndexedMesh(type)
        { }

    public:
        IResource* Copy(IResource* destination) const override;

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

        const SR_MATH_NS::Matrix4x4& GetModelMatrix() const override {
            return m_modelMatrix;
        }

        SR_NODISCARD std::string GetGeometryName() const override {
            return m_geometryName;
        }

        void SetGeometryName(const std::string& name) override {
            m_geometryName = name;
        }

        SR_MATH_NS::FVector3 GetTranslation() const override {
            return m_translation;
        }

        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const override;

    protected:
        SR_NODISCARD RenderScenePtr GetRenderScene();

    protected:
        RenderScenePtr m_renderScene;

        std::string m_geometryName;

        SR_MATH_NS::Matrix4x4 m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();

        SR_MATH_NS::FVector3 m_barycenter = SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX);

    };
}

#endif //SRENGINE_MESHCOMPONENT_H
