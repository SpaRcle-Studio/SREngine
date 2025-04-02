

# File Mesh.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Mesh.h**](Mesh_8h.md)

[Go to the documentation of this file](Mesh_8h.md)


```C++
//
// Created by Nikita on 17.11.2020.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_H
#define SR_ENGINE_GRAPHICS_MESH_H

#include <Utils/Math/Matrix4x4.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SortedVector.h>

#include <Graphics/Utils/MeshUtils.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Material/MaterialProperty.h>
#include <Graphics/Memory/DescriptorManager.h>
#include <Graphics/Material/MeshMaterialProperty.h>
#include <Graphics/Render/RenderQueue.h>
#include <Graphics/Types/IRenderComponent.h>

namespace SR_UTILS_NS {
    class IResource;
}

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
}

namespace SR_GRAPH_NS {
    class BaseMaterial;
}

namespace SR_GTYPES_NS {
    class Shader;

    class Mesh : public SR_GTYPES_NS::IRenderComponent, public Memory::IGraphicsResource {
        SR_CLASS()
        using Super = SR_GTYPES_NS::IRenderComponent;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using ShaderPtr = Shader*;
        using MaterialPtr = SR_HTYPES_NS::SharedPtr<BaseMaterial>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Mesh>;

        using RenderQueues = SR_HTYPES_NS::SortedVector<SR_GRAPH_NS::RenderQueueInfo, SR_GRAPH_NS::RenderQueuePredicate>;

    public:
        Mesh();
        ~Mesh() override;

    public:
        static std::vector<Mesh::Ptr> Load(const SR_UTILS_NS::Path& path, MeshType type);
        static Mesh::Ptr TryLoad(SR_HTYPES_NS::RawMesh* pRawMesh, MeshType type, uint32_t id);
        static Mesh::Ptr TryLoad(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh::Ptr Load(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh::Ptr Load(const SR_UTILS_NS::Path& path, MeshType type, SR_UTILS_NS::StringAtom name);

    public:
        void OnDestroy() override;
        void OnMatrixDirty() override;
        void OnLayerChanged() override;
        void OnPriorityChanged() override;
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD virtual int32_t GetIBO() { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t GetVBO() { return SR_ID_INVALID; }

        SR_NODISCARD virtual bool IsCalculatable() const;
        SR_NODISCARD virtual bool IsUniqueMesh() const { return false; }

        SR_NODISCARD bool IsActive() const noexcept override;
        SR_NODISCARD virtual SR_FORCE_INLINE bool IsFlatMesh() const noexcept { return false; }
        SR_NODISCARD virtual std::string GetMeshIdentifier() const;
        SR_NODISCARD virtual int64_t GetSortingPriority() const;
        SR_NODISCARD virtual bool HasSortingPriority() const;
        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetMeshLayer() const;
        SR_NODISCARD virtual bool IsSupportVBO() const = 0;
        SR_NODISCARD virtual uint32_t GetIndicesCount() const = 0;
        SR_NODISCARD virtual uint32_t GetVerticesCount() const { return 0; }
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        SR_NODISCARD ShaderPtr GetShader() const;
        SR_NODISCARD const MaterialPtr& GetMaterial() const noexcept { return m_material; }
        SR_NODISCARD int32_t GetVirtualUBO() const { return m_virtualUBO; }
        SR_NODISCARD virtual MeshType GetMeshType() const noexcept = 0;
        SR_NODISCARD bool IsWaitReRegister() const noexcept { return m_isWaitReRegister; }
        SR_NODISCARD bool IsMeshRegistered() const noexcept { return m_registrationInfo.has_value(); }
        SR_NODISCARD bool IsUniformsDirty() const noexcept { return m_isUniformsDirty; }
        SR_NODISCARD const MeshRegistrationInfo& GetMeshRegistrationInfo() const noexcept { return m_registrationInfo.value(); }
        SR_NODISCARD RenderQueues& GetRenderQueues() noexcept { return m_renderQueues; }
        SR_NODISCARD virtual FrustumCullingType GetFrustumCullingType() const noexcept { return m_frustumCullingType; }

        void SetMeshRegistrationInfo(const std::optional<MeshRegistrationInfo>& info) { m_registrationInfo = info; }

        virtual void SetMatrix(const SR_MATH_NS::Matrix4x4& matrix);

        SR_NODISCARD virtual const SR_MATH_NS::Matrix4x4& GetMatrix() const;

        virtual bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource);
        virtual bool BindMesh();

        virtual void Draw();

        virtual void UseMaterial();
        virtual void UseModelMatrix() { }
        virtual void UseSamplers();
        virtual void UseSSBO() { }

        void OnReRegistered();
        void MarkUniformsDirty(bool force = false);
        void MarkMaterialDirty();
        bool DestroyMesh();
        void ReRegisterMesh();
        void UnRegisterMesh();

        void SetMaterial(const MaterialPtr& pMaterial);
        void SetMaterial(const SR_UTILS_NS::Path& path);

        void SetErrorsClean() { m_hasErrors = false; }
        void SetUniformsClean() { m_isUniformsDirty = false; }

    protected:
        void FreeVideoMemory() override;

        virtual bool Calculate();

    protected:
        RenderQueues m_renderQueues;

        Memory::UBOManager& m_uboManager;
        SR_GRAPH_NS::DescriptorManager& m_descriptorManager;

        int32_t m_virtualUBO = SR_ID_INVALID;
        int32_t m_virtualDescriptor = SR_ID_INVALID;

    protected:
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        MaterialPtr m_material;
        FrustumCullingType m_frustumCullingType = FrustumCullingType::Sphere;
        bool m_isWaitReRegister = false;
        SR_VIRTUAL_PROPERTY
        bool m_hasErrors = false;
        bool m_dirtyMaterial = false;
        bool m_isUniformsDirty = false;

    private:
        bool m_isDestroyingState = false;
        std::optional<MeshRegistrationInfo> m_registrationInfo;
        uint32_t m_materialRegisterId = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_H
```


