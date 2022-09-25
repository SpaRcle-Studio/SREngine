//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_DEBUGWIREFRAMEMESH_H
#define GAMEENGINE_DEBUGWIREFRAMEMESH_H

#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Uniforms.h>

namespace SR_GRAPH_NS::Memory {
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
        void SetColor(const SR_MATH_NS::FVector4& color);

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD uint32_t GetMeshId() const { return m_meshId; }
        SR_NODISCARD SR_FORCE_INLINE bool IsDebugMesh() const noexcept override { return true; }

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetModelMatrix() const override;

        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const override;

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;
        void FreeVideoMemory() override;

        void UseMaterial() override;

    protected:
        bool Reload() override;
        bool Load() override;
        bool Unload() override;

    private:
        SR_MATH_NS::Matrix4x4 m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::FVector4 m_color;

        SR_HTYPES_NS::RawMesh* m_rawMesh = nullptr;
        /// определяет порядок меша в файле, если их там несколько
        int32_t m_meshId = SR_UINT32_MAX;

    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
