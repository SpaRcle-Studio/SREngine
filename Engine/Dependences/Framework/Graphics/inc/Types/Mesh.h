//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <ResourceManager/IResource.h>
#include <Environment/Vertex.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Environment/Environment.h>
#include "Material.h"
#include <EntityComponentSystem/Component.h>
#include <Debug.h>

namespace Framework::Graphics{
    class Render;
    class Shader;
}

namespace Framework::Graphics::Types {
    using namespace Helper;

    class Material;

    class Mesh : public IResource, public Component {
        friend class Material;
    public:
        /** \brief Default mesh constructor */
        Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
    private:
        /** \brief Default mesh destructor */
        ~Mesh();
    public:
        inline void SetRender(Render* render) noexcept {
            this->m_render = render;
        };
        inline void SetVertexArray(std::vector<Vertex>& vertices) noexcept {
            this->m_isCalculated = false;
            this->m_countVertices = vertices.size();
            this->m_vertices = vertices;
        }
    public:
        void OnMove(glm::vec3 newValue) noexcept override{
            m_position = newValue;
            ReCalcModel();
        }
        void OnRotate(glm::vec3 newValue) noexcept override{
            m_rotation = newValue;
            ReCalcModel();
        }
        void OnScaled(glm::vec3 newValue) noexcept override{
            m_scale = newValue;
            ReCalcModel();
        }
        void OnSelected(bool value) noexcept override;
    public:
        /** \brief Free mesh pointer
         * \return bool */
        bool Free() override {
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Debug::Log("Mesh::Free() : free mesh memory...");
            delete this;
            return true;
        }
        /** \brief Set mesh to destroy in res manager
        * \return bool */
        bool Destroy() override;
    private:
        Environment*                m_env                   = nullptr;

        std::mutex                  m_mutex                 = std::mutex();

        std::string                 m_geometry_name         = "Unnamed";
        Shader*                     m_shader                = nullptr;
        Render*                     m_render                = nullptr;
        Material*                   m_material              = nullptr;

        /** \brief Vertices OpenGL-context calculated */
        volatile bool               m_isCalculated          = false;

        unsigned int                m_VAO                   = 0;

        std::vector<Vertex>			m_vertices				= std::vector<Vertex>();
        size_t						m_countVertices		    = 0;

        std::vector<glm::mat4>      m_bonesTransforms       = std::vector<glm::mat4>();
    private:
        /** \brief Re-calc mesh space-transform matrix */
        void ReCalcModel();
        /** \brief Re-calc mesh space-transform matrix */
        bool Calculate();
    protected:
        void OnDestroyGameObject() noexcept override;
    public:
        inline void WaitCalculate() const {
            ret:
            if (m_isCalculated)
                return;
            goto ret;
        }
    public:
        glm::vec3				    m_position			= glm::vec3();
        glm::vec3					m_rotation			= glm::vec3();
        glm::vec3					m_scale				= {1,1,1};
        glm::mat4					m_modelMat			= glm::mat4(0);
    public:
        [[nodiscard]] std::string GetGeometryName() const noexcept { return this->m_geometry_name; }
        // TODO: Repeat. Make a comments, please
        static std::vector<Mesh*> Load(std::string path);
        static Mesh* LoadJson(std::string json_data, std::vector<Mesh*>* allMeshes = nullptr);

        nlohmann::json Save() override;

        [[nodiscard]] size_t GetCountVertices() const noexcept { return m_countVertices; }

        [[nodiscard]] inline Material* GetMaterial() const noexcept { return this->m_material; }

        [[nodiscard]] inline bool IsCalculated() const noexcept { return m_isCalculated; }

        Mesh* Copy();

        bool Draw();

        /** \warning call only from render */
        bool FreeVideoMemory();
    };
}

#endif //GAMEENGINE_MESH_H
