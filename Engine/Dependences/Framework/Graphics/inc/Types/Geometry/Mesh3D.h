//
// Created by Nikita on 01.06.2021.
//

#ifndef GAMEENGINE_MESH3D_H
#define GAMEENGINE_MESH3D_H

#include <Types/Mesh.h>
#include <Types/Vertices.h>

namespace Framework::Graphics::Types {
    class Mesh3D : public Mesh {
    public:
        Mesh3D(Shader* shader, Material* material, std::string name = "Unnamed") : Mesh(shader, material, name) {

        }
        Mesh3D() : Mesh(nullptr, nullptr, "Unnamed")  {

        }
    private:
        std::vector<Vertices::Mesh3DVertex> m_vertices = std::vector<Vertices::Mesh3DVertex>();
    public:
        Mesh* Copy() override {
            if (m_isDestroy) {
                Debug::Error("Mesh3D::Copy() : mesh already destroyed!");
                return nullptr;
            }

            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Mesh3D::Copy() : copy \""+m_resource_id+ "\" mesh...");

            if (!m_material){
                Debug::Error("Mesh3D::Copy() : material is nullptr! Something went wrong...");
                return nullptr;
            }

            m_mutex.lock();

            Material* mat = new Material(
                    m_material->m_diffuse,
                    m_material->m_normal,
                    m_material->m_specular,
                    m_material->m_glossiness
            );

            Mesh3D* copy = new Mesh3D(this->m_shader, mat, this->m_geometry_name);

            {
                mat->m_mesh         = copy;
                mat->m_bloom        = m_material->m_bloom;
                mat->m_transparent  = m_material->m_transparent;
                mat->m_color        = m_material->m_color;
            }

            copy->m_countVertices = m_countVertices;
            copy->m_countIndices  = m_countIndices;
            copy->m_useIndices    = m_useIndices;

            copy->m_position = m_position;
            copy->m_rotation = m_rotation;
            copy->m_scale    = m_scale;

            if (m_isCalculated) {
                if (m_VAO != -1)
                    VAO_usages[m_VAO]++;

                copy->m_VAO = m_VAO;
            }else{
                copy->m_vertices = m_vertices;
                copy->m_indices  = m_indices;
            }

            copy->m_isCalculated = m_isCalculated;
            copy->m_autoRemove = m_autoRemove;
            copy->m_modelMat = m_modelMat;

            copy->m_resource_id = m_resource_id;

            m_mutex.unlock();

            return copy;
        }

        SR_FORCE_INLINE void SetVertexArray(std::vector<Vertices::Mesh3DVertex>& vertices) noexcept {
            this->m_isCalculated  = false;
            this->m_countVertices = vertices.size();
            this->m_vertices      = vertices;
        }

        bool Free() override {
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Debug::Log("Mesh3D::Free() : free mesh memory...");
            delete this;
            return true;
        }

        bool Calculate() override {
            if (!m_render){
                Debug::Error("Mesh3D::Calculate() : mesh is not register in render!");
                return false;
            }

            if (!m_shader){
                if (!Shader::GetDefaultGeometryShader()) {
                    Debug::Error("Mesh3D::Calculate() : mesh have not shader!");
                    return false;
                }
            }

            if (!m_material){
                Debug::Error("Mesh::Calculate() : mesh have not material!");
                return false;
            }

            m_mutex.lock();

            {
                /* Check exists pre-calculated meshes */
                if (m_env->GetPipeLine() == PipeLine::OpenGL) {
                    unsigned int exists = VAO_names[m_resource_id];
                    if (exists) {
                        if (Debug::GetLevel() >= Debug::Level::High)
                            Debug::Log("Mesh3D::Calculate() : copy VAO...");

                        m_VAO = (int) exists;

                        VAO_usages[m_VAO]++;
                        m_isCalculated = true;
                        m_mutex.unlock();

                        return true;
                    }
                } else {
                    auto exists = VBOandIBO_names.find(m_resource_id);
                    if (exists != VBOandIBO_names.end()) {
                        if (Debug::GetLevel() >= Debug::Level::High)
                            Debug::Log("Mesh3D::Calculate() : copy VBO and IBO...");

                        m_VBO = (int)exists->second.first;
                        m_IBO = (int)exists->second.second;

                        VBO_usages[m_VBO]++;
                        IBO_usages[m_IBO]++;
                        m_isCalculated = true;
                        m_mutex.unlock();

                        return true;
                    }
                }
            }

            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Mesh3D::Calculate() : calculating \""+ m_geometry_name +"\"...");

            if (m_env->GetPipeLine() == PipeLine::OpenGL) {
                if (!this->m_env->CalculateVAO(reinterpret_cast<unsigned int &>(m_VAO), m_vertices, m_countVertices)) {
                    Debug::Error("Mesh3D::Calculate() : failed calculate \"" + m_geometry_name + "\" mesh!");
                    m_mutex.unlock();
                    return false;
                }

                VAO_usages[m_VAO]++;
                VAO_names[m_resource_id] = m_VAO;
            } else {
                //if (!this->m_env->CalculateVBO(reinterpret_cast<unsigned int &>(m_VBO), m_vertices.data(), sizeof(Vertices::Model3DVertex), m_countVertices)) {
                //    Debug::Error("Mesh::Calculate() : failed calculate \"" + m_geometry_name + "\" mesh!");
                //     m_mutex.unlock();
                //     return false;
                // }
            }

            m_isCalculated = true;

            m_mutex.unlock();

            return true;
        }
    };
}

#endif //GAMEENGINE_MESH3D_H
