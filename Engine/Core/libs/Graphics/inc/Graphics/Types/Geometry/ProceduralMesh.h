//
// Created by Monika on 05.04.2022.
//

#ifndef SRENGINE_PROCEDURALMESH_H
#define SRENGINE_PROCEDURALMESH_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class ProceduralMesh : public MeshComponent {
        using Super = MeshComponent;
        SR_REGISTER_NEW_COMPONENT(ProceduralMesh, 1001);
    public:
        ProceduralMesh();

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        void SetIndexedVertices(void* pData, uint64_t count);
        void SetIndices(void* pData, uint64_t count);
        void SetVertices(const std::vector<Vertices::StaticMeshVertex>& vertices);

        void UseMaterial() override;
        void UseModelMatrix() override;

        SR_NODISCARD bool IsUniqueMesh() const override { return true; }

        SR_NODISCARD bool IsCalculatable() const override;

        SR_NODISCARD Component* CopyComponent() const override;

    private:
        bool Calculate() override;
        void Draw() override;
        void SetDirtyMesh();

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    private:
        std::vector<Vertices::StaticMeshVertex> m_vertices;
        std::vector<uint32_t> m_indices;

    };
}

#endif //SRENGINE_PROCEDURALMESH_H
