//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <vector>
#include <macros.h>

#include <Debug.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <Render/Shader.h>
#include <Types/Material.h>
#include <ResourceManager/IResource.h>
#include <Environment/Vertex.h>
#include <Environment/Environment.h>
#include <EntityComponentSystem/Component.h>
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
    protected:
        /** \brief Default mesh constructor */
        Mesh();
        Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
    protected:
        /** \brief Default mesh destructor */
        ~Mesh();
    public:
        [[nodiscard]] SR_FORCE_INLINE glm::mat4 GetModelMatrix() const noexcept { return this->m_modelMat; }
        SR_FORCE_INLINE void SetRender(Render* render) noexcept {
            this->m_render = render;
        };
        SR_FORCE_INLINE void SetIndexArray(std::vector<unsigned int>& indices) noexcept {
            this->m_isCalculated = false;
            this->m_countIndices = indices.size();
            this->m_indices      = indices;
        }
    public:
        bool DrawOnInspector() override;

        void SetMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

        SR_FORCE_INLINE void OnMove(glm::vec3 newValue) noexcept override{
            m_position = newValue;
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnRotate(glm::vec3 newValue) noexcept override{
            m_rotation = newValue;
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnScaled(glm::vec3 newValue) noexcept override{
            m_scale = newValue;
            ReCalcModel();
        }
        void OnSelected(bool value) noexcept override;

        SR_FORCE_INLINE void SetInverse(bool value) noexcept {
            this->m_inverse = value;
            ReCalcModel();
        }
        [[nodiscard]] SR_FORCE_INLINE bool GetInverse() const noexcept { return this->m_inverse; }

        SR_FORCE_INLINE static void Inverse(Helper::Types::List<Mesh*> meshes){
            for (size_t t = 0; t < meshes.Size(); t++)
                meshes[t]->SetInverse(!meshes[t]->GetInverse());
        }
    public:
        /** \brief Set mesh to destroy in res manager
        * \return bool */
        bool Destroy() override;
    protected:
        bool                        m_inverse           = false;

        Environment*                m_env               = nullptr;
        PipeLine                    m_pipeline          = PipeLine::Unknown;

        std::mutex                  m_mutex             = std::mutex();

        std::string                 m_geometry_name     = "Unnamed";
        Shader*                     m_shader            = nullptr;
        Render*                     m_render            = nullptr;
        Material*                   m_material          = nullptr;

        /** \brief Vertices OpenGL-context calculated */
        volatile bool               m_hasErrors         = false;
        volatile bool               m_isCalculated      = false;
        unsigned char               m_toolID            = 0; // 0 - none, 1 - x, 2 - y, 3 - z

        int                         m_descriptorSet     = -1;
        int                         m_VAO               = -1;
        int                         m_VBO               = -1;
        int                         m_IBO               = -1;
        int32_t                     m_UBO               = -1;

        std::vector<uint32_t>	    m_indices           = std::vector<uint32_t>();
        size_t						m_countVertices	    = 0;
        size_t						m_countIndices	    = 0;
        bool                        m_useIndices        = false;
    private:
        /** \brief Re-calc mesh space-transform matrix */
        void ReCalcModel();
        /** \brief Re-calc mesh space-transform matrix */
        virtual bool Calculate() = 0;
    protected:
        void OnDestroyGameObject() noexcept override;
        void OnReady(bool ready) override {
            this->m_env->SetBuildState(false);
        }
    public:
        SR_FORCE_INLINE void WaitCalculate() const {
            ret:
            if (m_isCalculated)
                return;
            goto ret;
        }
    public:
        glm::vec3 m_position = glm::vec3();
        glm::vec3 m_rotation = glm::vec3();
        glm::vec3 m_scale    = { 1, 1, 1 };
        glm::mat4 m_modelMat = glm::mat4(0);
    public:
        [[nodiscard]] SR_FORCE_INLINE uint32_t FastGetVAO() const noexcept { return (uint32_t)m_VAO; }
        [[nodiscard]] SR_FORCE_INLINE uint32_t FastGetVBO() const noexcept { return (uint32_t)m_VBO; }
        [[nodiscard]] SR_FORCE_INLINE uint32_t FastGetIBO() const noexcept { return (uint32_t)m_IBO; }
        [[nodiscard]] SR_FORCE_INLINE int32_t  FastGetUBO() const noexcept { return m_UBO;           }

        [[nodiscard]] SR_FORCE_INLINE int32_t GetVAO() {
            if (m_isDestroy)
                return m_VAO;

            if (!m_isCalculated)
                if (!Calculate())
                    return -1;
            return m_VAO;
        }

        [[nodiscard]] SR_FORCE_INLINE int32_t GetVBO() {
            if (m_isDestroy)
                return m_VBO;

            if (!m_isCalculated)
                if (!Calculate())
                    return -1;
            return m_VBO;
        }

        void PrintInfo();

        [[nodiscard]] std::string GetGeometryName() const noexcept { return this->m_geometry_name; }
        // TODO: Repeat. Make a comments, please
        static std::vector<Mesh*> Load(std::string path, bool withIndices = false);
        static Mesh* LoadJson(std::string json_data, std::vector<Mesh*>* allMeshes = nullptr);

        nlohmann::json Save() override;

        [[nodiscard]] SR_FORCE_INLINE size_t GetCountVertices() const noexcept { return m_countVertices;  }
        [[nodiscard]] SR_FORCE_INLINE Material* GetMaterial()   const noexcept { return this->m_material; }
        [[nodiscard]] SR_FORCE_INLINE bool IsCalculated()       const noexcept { return m_isCalculated;   }

        virtual Mesh* Copy() = 0;

        SR_FORCE_INLINE void SetToolID(unsigned char ID) noexcept { this->m_toolID = ID; }

#define ConfigureShader(shader) \
        shader->SetMat4("modelMat", m_modelMat); \
        shader->SetVec3("color", m_material->m_color); \
        shader->SetIVec2("config", { \
            (int)m_material->m_bloom, \
                    m_toolID == 0 ? (int)this->m_isSelected : (int)(m_toolID + 1) \
        }); \

        bool SimpleDraw();

        virtual SR_FORCE_INLINE void DrawVulkan() = 0;

        SR_FORCE_INLINE bool DrawOpenGL() noexcept {
            if (m_isDestroy) return false;

            if (!m_isCalculated)
                if (!this->Calculate())
                    return false;

            if (!m_shader) {
                ConfigureShader(Shader::GetDefaultGeometryShader())
                this->m_material->UseWithDefShader();
            }
            else {
                ConfigureShader(m_shader)
                this->m_material->Use();
            }

            this->m_env->DrawTriangles(m_countVertices);

            return true;
        }

        SR_FORCE_INLINE bool DrawWireFrame() noexcept {
            if (m_isDestroy) return false;

            if (!m_isCalculated)
                if (!this->Calculate())
                    return false;

            if (!m_shader) {
                ConfigureShader(Shader::GetDefaultGeometryShader())
                this->m_material->UseWithDefShader();
            }
            else {
                ConfigureShader(m_shader)
                this->m_material->Use();
            }

            this->m_env->DrawLines(m_VAO, m_countVertices);

            return true;
        }

        /** \warning call only from render */
        virtual bool FreeVideoMemory() = 0;

        void OnDestroyComponent() noexcept override {
            Debug::Error("Mesh::OnDestroyComponent() : TODO!");
        }
    };
}

#endif //GAMEENGINE_MESH_H
