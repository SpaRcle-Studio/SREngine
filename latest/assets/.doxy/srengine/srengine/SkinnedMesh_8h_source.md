

# File SkinnedMesh.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**SkinnedMesh.h**](SkinnedMesh_8h.md)

[Go to the documentation of this file](SkinnedMesh_8h.md)


```C++
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
    class SkinnedMesh final : public IndexedMesh, public SR_HTYPES_NS::IRawMeshHolder {
        SR_CLASS()
        using Super = IndexedMesh;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<SkinnedMesh>;

        SkinnedMesh();

    public:
        typedef Vertices::SkinnedMeshVertex VertexType;

    public:
        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Skinned; }

        void LateUpdate() override;
        void UseMaterial() override;
        void UseModelMatrix() override;

        SR_NODISCARD bool IsSkeletonUsable() const;
        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD bool IsUpdatable() const noexcept override { return true; }
        SR_NODISCARD std::string GetMeshIdentifier() const override;
        SR_NODISCARD const SR_UTILS_NS::EntityRef& GetSkeleton() const noexcept { return m_skeleton; }
        SR_NODISCARD SR_UTILS_NS::EntityRef& GetSkeleton() noexcept { return m_skeleton; }

        void FreeVideoMemory() override;

        void UseSSBO() override;

    private:
        bool PopulateSkeletonMatrices();

        bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource) override;
        void OnRawMeshChanged() override;
        bool Calculate() override;

        void FreeSSBO();

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    private:
        bool m_skeletonIsBroken = false;
        int32_t m_ssboBones = SR_ID_INVALID;
        int32_t m_ssboOffsets = SR_ID_INVALID;

    private:
        SR_UTILS_NS::EntityRef m_skeleton;

        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

    };
}

#endif //SR_ENGINE_GRAPHICS_SKINNED_MESH_H
```


