

# File MeshComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**MeshComponent.h**](MeshComponent_8h.md)

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


