//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H
#include <Render/Shader.h>
#include <Types/Material.h>
#include <ResourceManager/IResource.h>
#include <Environment/Vertex.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Environment/Environment.h>
#include <EntityComponentSystem/Component.h>
#include <Debug.h>
#include <Types/List.h>

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
        //Mesh() : IResource("Mesh"), m_env(Environment::Get()), Component("Mesh") { }
        Mesh();
        Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
    private:
        /** \brief Default mesh destructor */
        ~Mesh();
    public:
        [[nodiscard]] inline glm::mat4 GetModelMatrix() const noexcept { return this->m_modelMat; }
        inline void SetRender(Render* render) noexcept {
            this->m_render = render;
        };
        inline void SetVertexArray(std::vector<Vertex>& vertices) noexcept {
            this->m_isCalculated = false;
            this->m_countVertices = vertices.size();
            this->m_vertices = vertices;
        }
    public:
        bool DrawOnInspector() override;

        void SetMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

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

        void SetInverse(bool value) noexcept {
            this->m_inverse = value;
            ReCalcModel();
        }
        [[nodiscard]] bool GetInverse() const noexcept {
            return this->m_inverse;
        }

        static void Inverse(Helper::Types::List<Mesh*> meshes){
            for (size_t t = 0; t < meshes.Size(); t++)
                meshes[t]->SetInverse(!meshes[t]->GetInverse());
        }
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
        bool                        m_inverse               = false;

        Environment*                m_env                   = nullptr;

        std::mutex                  m_mutex                 = std::mutex();

        std::string                 m_geometry_name         = "Unnamed";
        Shader*                     m_shader                = nullptr;
        Render*                     m_render                = nullptr;
        Material*                   m_material              = nullptr;

        /** \brief Vertices OpenGL-context calculated */
        volatile bool               m_isCalculated          = false;
        unsigned char               m_toolID                = 0; // 0 - none, 1 - x, 2 - y, 3 - z

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

        inline void SetToolID(unsigned char ID) noexcept {
            this->m_toolID = ID;
        }

        bool SimpleDraw();
        inline bool Draw() noexcept {
            //if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Indigo); }

            if (m_isDestroy) return false;

            if (!m_isCalculated)
                if (!this->Calculate())
                    return false;

            this->m_shader->SetMat4("modelMat", m_modelMat);
            this->m_shader->SetVec3("color", m_material->m_color); //TODO: change to vec4
            this->m_shader->SetIVec2("config", {
                (int)m_material->m_bloom,
                m_toolID == 0 ? (int)this->m_isSelected : (int)(m_toolID + 1)
            });
            //this->m_shader->SetInt("bloom", (int)m_material->m_bloom);
            //this->m_shader->SetInt("selected", (int)this->m_isSelected);

            this->m_material->Use();

            this->m_env->DrawTriangles(m_VAO, m_countVertices);

            return true;
        }

        /** \warning call only from render */
        bool FreeVideoMemory();

        void OnDestroyComponent() noexcept override {
            Debug::Error("Mesh::OnDestroyComponent() : TODO!");
        }
    };
}

#endif //GAMEENGINE_MESH_H
