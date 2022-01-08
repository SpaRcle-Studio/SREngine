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
        explicit IndexedMesh(const std::string& name = "UnnamedIndexedMesh")
            : VertexMesh(name) { };
    protected:
        int32_t               m_IBO          = SR_ID_INVALID;
        std::vector<uint32_t> m_indices      = std::vector<uint32_t>();
        uint32_t              m_countIndices = 0;
        bool                  m_useIndices   = false;
    public:
        template<bool fast> [[nodiscard]] int32_t GetIBO();

        IResource* Copy(IResource* destination) const override;

        void SetIndexArray(const std::vector<uint32_t>& indices) {
            this->m_countIndices = indices.size();
            this->m_indices      = indices;
            this->m_isCalculated = false;
            this->m_useIndices   = true;
        }

        bool Calculate() override;
        bool FreeVideoMemory() override;
    };

    template<bool fast> int32_t IndexedMesh::GetIBO() {
        static_assert(fast, "unsupported!");

        if constexpr (fast) {
            return m_VBO;
        }
    }
}

#endif //GAMEENGINE_INDEXEDMESH_H
