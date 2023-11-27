//
// Created by Monika on 19.09.2022.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_COMPONENT_H
#define SR_ENGINE_GRAPHICS_MESH_COMPONENT_H

#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Types/IRenderComponent.h>

namespace SR_GTYPES_NS {
    class MeshComponent : public IndexedMesh, public SR_GTYPES_NS::IRenderComponent {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<MeshComponent>;

    protected:
        explicit MeshComponent(MeshType type);

    public:
        SR_NODISCARD bool InitializeEntity() noexcept override;

        SR_MATH_NS::FVector3 GetBarycenter() const override;

        void OnLoaded() override;
        void OnAttached() override;
        void OnDestroy() override;
        void OnMatrixDirty() override;

        void FreeMesh() override;

        SR_NODISCARD bool ExecuteInEditMode() const override;
        SR_NODISCARD bool IsUpdatable() const noexcept override { return false; }
        SR_NODISCARD int64_t GetSortingPriority() const override;

        SR_NODISCARD SR_FORCE_INLINE bool IsMeshActive() const noexcept override {
            return SR_UTILS_NS::Component::IsActive() && IndexedMesh::IsMeshActive();
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

    protected:
        std::string m_geometryName;

        SR_MATH_NS::Matrix4x4 m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();

        SR_MATH_NS::FVector3 m_barycenter = SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX);

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_COMPONENT_H
