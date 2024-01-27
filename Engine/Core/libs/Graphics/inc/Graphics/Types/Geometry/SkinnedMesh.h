//
// Created by Nikita on 01.06.2021.
//

#ifndef SR_ENGINE_GRAPHICS_SKINNED_MESH_H
#define SR_ENGINE_GRAPHICS_SKINNED_MESH_H

#include <Utils/Types/IRawMeshHolder.h>
#include <Utils/ECS/EntityRef.h>

#include <Graphics/Types/Geometry/MeshComponent.h>
#include <Graphics/Animations/Skeleton.h>

namespace SR_GTYPES_NS {
    class SkinnedMesh final : public MeshComponent, public SR_HTYPES_NS::IRawMeshHolder {
        SR_REGISTER_NEW_COMPONENT(SkinnedMesh, 1003);
        using Super = MeshComponent;
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SKELETON_REF_PROP_NAME = "Skeleton";
    public:
        SkinnedMesh();

    private:
        ~SkinnedMesh() override;

    public:
        typedef Vertices::SkinnedMeshVertex VertexType;

    public:
        SR_NODISCARD bool InitializeEntity() noexcept override;

        void Update(float dt) override;
        void UseMaterial() override;
        void UseModelMatrix() override;

        SR_NODISCARD bool IsSkeletonUsable() const;
        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD bool IsUpdatable() const noexcept override { return true; }
        SR_NODISCARD std::string GetMeshIdentifier() const override;
        SR_NODISCARD SR_UTILS_NS::EntityRef& GetSkeleton() const;
        SR_NODISCARD uint32_t GetMaxBones() const;

    private:
        bool PopulateSkeletonMatrices();

        bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource) override;
        void OnRawMeshChanged() override;
        bool Calculate() override;
        void Draw() override;

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    private:
        bool m_skeletonIsBroken = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_SKINNED_MESH_H
