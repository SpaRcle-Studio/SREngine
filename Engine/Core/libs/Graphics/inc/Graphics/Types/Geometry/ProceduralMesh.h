//
// Created by Monika on 05.04.2022.
//

#ifndef SRENGINE_PROCEDURALMESH_H
#define SRENGINE_PROCEDURALMESH_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class ProceduralMesh : public MeshComponent {
        friend class Mesh;
        using Super = MeshComponent;
        SR_ENTITY_SET_VERSION(1000);
    public:
        ProceduralMesh();

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        IResource* CopyResource(IResource* destination) const override;

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        void SetIndexedVertices(void* pData, uint64_t count);
        void SetIndices(void* pData, uint64_t count);
        void SetVertices(const std::vector<Vertices::StaticMeshVertex>& vertices);

        void UseMaterial() override;

        SR_NODISCARD bool IsCanCalculate() const override;

    private:
        bool Calculate() override;
        void FreeVideoMemory() override;
        void Draw() override;
        void SetDirtyMesh();

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;
        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    private:
        std::vector<Vertices::StaticMeshVertex> m_vertices;
        std::vector<uint32_t> m_indices;

    };
}

#endif //SRENGINE_PROCEDURALMESH_H
