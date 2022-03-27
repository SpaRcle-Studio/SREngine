//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_INDEXEDMESH_H
#define GAMEENGINE_INDEXEDMESH_H

#include <Types/Geometry/VertexMesh.h>
#include <Environment/PipeLine.h>
#include <Memory/MeshManager.h>

#include <utility>

namespace Framework::Graphics::Types {
    class IndexedMesh : public VertexMesh {
    protected:
        ~IndexedMesh() override = default;
        explicit IndexedMesh(MeshType type, const std::string& name = "UnnamedIndexedMesh")
            : VertexMesh(type, name)
        { }

    public:
        template<bool fast> [[nodiscard]] int32_t GetIBO();
        SR_NODISCARD uint32_t GetIndicesCount() const { return m_countIndices; }

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;
        bool FreeVideoMemory() override;

        void SetRawMesh(Helper::Types::RawMesh* raw) override;

    protected:
        int32_t               m_IBO          = SR_ID_INVALID;
        uint32_t              m_countIndices = 0;

    };

    template<bool fast> int32_t IndexedMesh::GetIBO() {
        static_assert(fast, "unsupported!");

        if constexpr (fast) {
            return m_VBO;
        }
    }
}

#endif //GAMEENGINE_INDEXEDMESH_H
