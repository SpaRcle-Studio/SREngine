//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_VERTEXMESH_H
#define GAMEENGINE_VERTEXMESH_H

#include <any>
#include <Types/Mesh.h>
#include <Memory/MeshManager.h>

namespace Framework::Graphics::Types {
    class VertexMesh : public Mesh {
    protected:
        explicit VertexMesh(MeshType type, const std::string& name = "UnnamedVertexMesh")
            : Mesh(type, name)
        { }

        ~VertexMesh() override = default;

    public:
        template<bool fast> [[nodiscard]] int32_t GetVBO();

        ///virtual void SetVertexArray(const std::any& vertices) = 0;

        SR_NODISCARD uint32_t GetVerticesCount() const { return m_countVertices; }

    protected:
        IResource* Copy(IResource* destination) const override {
            if (auto vertex = dynamic_cast<VertexMesh*>(destination)) {
                /// Копирование VBO происходит в классе-наследнике
                vertex->m_countVertices = m_countVertices;
                return Mesh::Copy(vertex);
            }
            else {
                SR_ERROR("VertexMesh::Copy() : bad cast!");
                return nullptr;
            }
        }

        bool Calculate() override {
            return Mesh::Calculate();
        }

        void SetRawMesh(Helper::Types::RawMesh* raw) override {
            m_countVertices = raw->GetVertices(m_meshId).size();
            Mesh::SetRawMesh(raw);
        }

    protected:
        template<Vertices::Type type> bool CalculateVBO(void* data);
        template<Vertices::Type type> bool FreeVBO();

    protected:
        int32_t  m_VBO = SR_ID_INVALID;
        uint32_t m_countVertices = 0;

    };

    template<bool fast> int32_t VertexMesh::GetVBO() {
        if constexpr (fast) {
            return m_VBO;
        } else {
            //if (m_isDestroy) // TODO: what?
            //    return m_VBO;

            if (!m_isCalculated && !Calculate())
                return SR_ID_INVALID;

            return m_VBO;
        }
    }

    template<Vertices::Type type> bool VertexMesh::CalculateVBO(void* data) {
        if (m_VBO = Memory::MeshManager::Instance().CopyIfExists<type, Memory::MeshManager::VBO>(GetResourceId()); m_VBO == SR_ID_INVALID) {
            if (m_countVertices == 0 || !data) {
                SR_ERROR("VertexMesh::Calculate() : invalid vertices! \n\tResource id: " + GetResourceId() + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_VBO = m_env->CalculateVBO(data, type, m_countVertices); m_VBO == SR_ID_INVALID) {
                SR_ERROR("VertexMesh::Calculate() : failed calculate VBO \"" + m_geometryName + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else {
                return Memory::MeshManager::Instance().Register<type, Memory::MeshManager::VBO>(GetResourceId(), m_VBO);
            }
        }

        return true;
    }

    template<Vertices::Type type> bool VertexMesh::FreeVBO() {
        using namespace Memory;

        if (MeshManager::Instance().Free<type, MeshManager::VBO>(GetResourceId()) == MeshManager::FreeResult::Freed) {
            if (!m_env->FreeVBO(m_VBO)) {
                SR_ERROR("VertexMesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
                return false;
            }
        }

        return true;
    }
}

#endif //GAMEENGINE_VERTEXMESH_H
