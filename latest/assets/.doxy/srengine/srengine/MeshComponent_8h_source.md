

# File MeshComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**MeshComponent.h**](MeshComponent_8h.md)

[Go to the documentation of this file](MeshComponent_8h.md)


```C++
//
// Created by Monika on 19.09.2022.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_COMPONENT_H
#define SR_ENGINE_GRAPHICS_MESH_COMPONENT_H

#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Types/IRenderComponent.h>

namespace SR_GTYPES_NS {
    /*class IMeshComponent : public SR_GTYPES_NS::IRenderComponent {
        SR_CLASS()
        using Super = SR_GTYPES_NS::IRenderComponent;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IMeshComponent>;

    protected:
        explicit IMeshComponent(Mesh* pMesh);

    public:
        SR_NODISCARD bool InitializeEntity() noexcept override;

        void OnDestroy() override;
        void OnMatrixDirty() override;

        void OnEnable() override;
        void OnDisable() override;

        void OnLayerChanged() override;
        void OnPriorityChanged() override;

        SR_NODISCARD bool ExecuteInEditMode() const override;
        SR_NODISCARD bool IsUpdatable() const noexcept override { return false; }

    protected:
        std::string m_geometryName;

    private:
        Mesh* m_pInternal = nullptr;

    };


    class IndexedMeshComponent : public IMeshComponent, public IndexedMesh {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IndexedMeshComponent>;

    protected:
        IndexedMeshComponent();

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsMeshActive() const noexcept override {
            return SR_UTILS_NS::Component::IsActive() && IndexedMesh::IsMeshActive();
        }

        SR_NODISCARD std::string GetGeometryName() const override { return m_geometryName; }
        void SetGeometryName(const std::string& name) override { m_geometryName = name; }

        SR_NODISCARD int64_t GetSortingPriority() const override;
        SR_NODISCARD bool HasSortingPriority() const override;
        SR_NODISCARD SR_UTILS_NS::StringAtom GetMeshLayer() const override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() const override;

    };*/


    /*class MeshComponent : public Mesh {
        using Super = Mesh;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<MeshComponent>;

    public:
        MeshComponent();

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsMeshActive() const noexcept override {
            return SR_UTILS_NS::Component::IsActive() && Mesh::IsMeshActive();
        }

        SR_NODISCARD std::string GetGeometryName() const override { return m_geometryName; }
        void SetGeometryName(const std::string& name) override { m_geometryName = name; }
        const SR_MATH_NS::Matrix4x4& GetMatrix() const override;

        SR_NODISCARD int64_t GetSortingPriority() const override;
        SR_NODISCARD bool HasSortingPriority() const override;
        SR_NODISCARD SR_UTILS_NS::StringAtom GetMeshLayer() const override;

    private:
        std::string m_geometryName;

    };*/
}

#endif //SR_ENGINE_GRAPHICS_MESH_COMPONENT_H
```


