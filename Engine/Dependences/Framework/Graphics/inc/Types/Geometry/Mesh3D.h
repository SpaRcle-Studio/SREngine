//
// Created by Nikita on 01.06.2021.
//

#ifndef GAMEENGINE_MESH3D_H
#define GAMEENGINE_MESH3D_H

#include <Types/Mesh.h>
#include <Types/Vertices.h>

#include <utility>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Types {
    class Mesh3D : public Mesh {
    public:
        Mesh3D(Shader* shader, Material* material, std::string name = "Unnamed") : Mesh(shader, material, std::move(name)) {

        }
        Mesh3D() : Mesh(nullptr, nullptr, "Unnamed")  {

        }
    private:
        std::vector<Vertices::Mesh3DVertex> m_vertices = std::vector<Vertices::Mesh3DVertex>();
    private:
        void ReCalcModel() override;
    public:
        SR_FORCE_INLINE void DrawVulkan() override {
            if (!this->IsReady() || m_isDestroy) return;

            if (m_descriptorSet < 0) {
                this->m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform });
                if (m_descriptorSet < 0) {
                    Helper::Debug::Error("Mesh3D::Calculate() : failed to calculate descriptor set!");
                    this->m_hasErrors = true;
                    return;
                }

                this->m_UBO = m_env->AllocateUBO(sizeof(Mesh3DUBO));
                if (m_UBO < 0) {
                    Helper::Debug::Error("Mesh3D::Calculate() : failed to allocate uniform buffer object!");
                    return;
                }

                this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                        { DescriptorType::Uniform, { 0, m_UBO                                 } },
                        { DescriptorType::Uniform, { 1, Shader::GetCurrentShader()->GetUBO(0) } },
                });

                Mesh3DUBO ubo = { m_modelMat }; m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3DUBO));
            }

            if (!m_isCalculated)
                if (m_hasErrors || !this->Calculate())
                    return;

            this->m_env->BindDescriptorSet(m_descriptorSet);

            this->m_env->DrawIndices(this->m_countIndices);
        }

        Mesh* Copy() override;

        SR_FORCE_INLINE void SetVertexArray(const std::vector<Vertices::Mesh3DVertex>& vertices) noexcept {
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

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_MESH3D_H
