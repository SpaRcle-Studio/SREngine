

# File DebugRenderer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**DebugRenderer.h**](DebugRenderer_8h.md)

[Go to the documentation of this file](DebugRenderer_8h.md)


```C++
//
// Created by Monika on 20.09.2022.
//

#ifndef SR_ENGINE_GRAPHICS_DEBUG_RENDERER_H
#define SR_ENGINE_GRAPHICS_DEBUG_RENDERER_H

#include <Graphics/Memory/MeshManager.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Render/IRenderer.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

namespace SR_GTYPES_NS {
    class Mesh;
}

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;
    class FileMaterial;

    class DebugRenderer : public IRenderer {
        using Super = IRenderer;
        SR_CLASS()
    public:
        enum class DrawType : int32_t {
            None = -2, Line = -1, Mesh = 0,
            Cube = Mesh, Sphere, Cylinder,
            CustomMesh
        };
        struct DrawInfo {
            DrawType type = DrawType::None;
            SR_MATH_NS::FVector3 start;
            SR_MATH_NS::FVector3 end;
            SR_MATH_NS::Matrix4x4 modelMatrix;
            SR_MATH_NS::FColor color;
        };
        struct DebugTimedObject {
            uint64_t startTimePoint = 0;
            uint64_t endTimePoint = 0;
            uint64_t duration = 0;
            DrawInfo drawInfo;
        };
    public:
        ~DebugRenderer() override;

        void Init() override;
        void DeInit() override;
        void Prepare() override;
        void Clear() override;

        void ResetChangedFlags() noexcept;

        SR_NODISCARD bool IsEmpty() const noexcept override { return m_timedObjects.IsEmpty(); }
        SR_NODISCARD uint64_t GetTimedObjectPoolSize() const noexcept { return m_timedObjects.GetAliveCount(); }
        SR_NODISCARD uint64_t GetEmptyIdsPoolSize() const noexcept { return m_timedObjects.GetCapacity(); }
        SR_NODISCARD SR_HTYPES_NS::ObjectPool<DebugTimedObject>& GetTimedObjects() noexcept { return m_timedObjects; }
        SR_NODISCARD SR_FORCE_INLINE const Memory::BakedMesh& GetMeshUnchecked(uint32_t index) const noexcept { return m_meshes[index].GetUncheckedRef(); }
        SR_NODISCARD bool IsRenderSceneChanged() const noexcept { return m_renderSceneChanged; }

    private:
        uint64_t AddLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t seconds);
        uint64_t AddMesh(uint64_t id, uint32_t meshId, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t seconds);
        uint64_t AddCustomMesh(SR_HTYPES_NS::RawMesh* pRawMesh, int32_t meshIndex, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t seconds);

    private:
        uint64_t AddTimedObject(float_t seconds, SR_GTYPES_NS::Mesh* pMesh);
        void Remove(uint64_t id, bool fromPool);
        void OnSceneChanged();

    private:
        bool m_renderSceneChanged = false;

        SR_HTYPES_NS::ObjectPool<DebugTimedObject> m_timedObjects;

        std::vector<Memory::BakedMesh::Ptr> m_meshes;
    };
}

#endif //SR_ENGINE_GRAPHICS_DEBUG_RENDERER_H
```


