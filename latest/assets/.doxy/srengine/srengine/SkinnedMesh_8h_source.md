

# File SkinnedMesh.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**SkinnedMesh.h**](SkinnedMesh_8h.md)

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
        using SkeletonRef = SR_UTILS_NS::EntityRef<SR_ANIMATIONS_NS::Skeleton>;
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

        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD bool IsUpdatable() const noexcept override { return true; }
        SR_NODISCARD std::string GetMeshIdentifier() const override;
        SR_NODISCARD const SkeletonRef& GetSkeletonRef() const noexcept { return m_skeleton; }
        SR_NODISCARD SkeletonRef& GetSkeletonRef() noexcept { return m_skeleton; }

        void FreeVMemory() override;

        void UseSSBO() override;

    private:
        bool OnResourceReloaded(const SR_UTILS_NS::IResource* pResource) override;
        void OnRawMeshChanged() override;
        bool Calculate() override;

        void FreeSSBO();

        SR_NODISCARD const SR_HTYPES_NS::FastMemoryArray<uint32_t>& GetIndices() const override;

    private:
        bool m_skeletonIsBroken = false;
        std::vector<int32_t> m_ssboBones;

    private:
        SkeletonRef m_skeleton;

        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

    };
}

#endif //SR_ENGINE_GRAPHICS_SKINNED_MESH_H
```


