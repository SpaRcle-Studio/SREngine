//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_DEBUGWIREFRAMEMESH_H
#define GAMEENGINE_DEBUGWIREFRAMEMESH_H

#include <Types/Geometry/IndexedMesh.h>
#include <Types/Vertices.h>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Memory {
    class MeshAllocator;
}

namespace SR_GTYPES_NS {
    class DebugWireframeMesh final : public IndexedMesh {
        friend class Mesh;
        using Super = IndexedMesh;
    public:
        typedef Vertices::SimpleVertex VertexType;

    public:
        DebugWireframeMesh();

    private:
        ~DebugWireframeMesh() override;

    public:
        void Draw() override;

        void SetRawMesh(SR_HTYPES_NS::RawMesh* raw);
        void SetMatrix(const SR_MATH_NS::Matrix4x4& matrix4X4);

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD uint32_t GetMeshId() const { return m_meshId; }
        SR_NODISCARD SR_FORCE_INLINE bool IsDebugMesh() const noexcept override { return true; }

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;
        void FreeVideoMemory() override;

        void UseMaterial() override;

    protected:
        bool Reload() override;
        bool Load() override;
        bool Unload() override;

    private:
        SR_HTYPES_NS::RawMesh* m_rawMesh = nullptr;
        /// определяет порядок меша в файле, если их там несколько
        int32_t m_meshId = SR_UINT32_MAX;

    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
