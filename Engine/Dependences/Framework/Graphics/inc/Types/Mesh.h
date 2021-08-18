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

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <Environment/Environment.h>
#include <EntityComponentSystem/Component.h>
#include <Types/List.h>

namespace Framework::Graphics{
    class Render;
    class Shader;
}

namespace Framework {
    class API;
}

namespace Framework::Graphics::Types {
    using namespace Helper;

    class Material;

    class Mesh : public IResource, public Component {
        friend class Material;
        friend class ::Framework::API;
    protected:
        /** \brief Default mesh constructor */
        Mesh();
        Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
    protected:
        /** \brief Default mesh destructor */
        ~Mesh();
    public:
        static std::vector<Mesh*> Load(const std::string& path);
    public:
        [[nodiscard]] SR_FORCE_INLINE glm::mat4 GetModelMatrix() const noexcept { return this->m_modelMat; }
        SR_FORCE_INLINE void SetRender(Render* render) noexcept {
            this->m_render = render;
        };
        SR_FORCE_INLINE void SetIndexArray(std::vector<uint32_t>& indices) noexcept {
            this->m_isCalculated = false;
            this->m_countIndices = indices.size();
            this->m_indices      = indices;
        }
    public:
        bool DrawOnInspector() override;
        Math::Vector3 GetBarycenter() const override;
        SR_FORCE_INLINE void OnMove(Math::Vector3 newValue) noexcept override{
            m_position = newValue.ToGLM();
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnRotate(Math::Vector3 newValue) noexcept override{
            m_rotation = newValue.ToGLM();
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnScaled(Math::Vector3 newValue) noexcept override{
            m_scale = newValue.ToGLM();
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

        mutable std::mutex          m_mutex             = std::mutex();

        std::string                 m_geometry_name     = "Unnamed";
        Shader*                     m_shader            = nullptr;
        Render*                     m_render            = nullptr;
        Material*                   m_material          = nullptr;

        /** \brief Vertices OpenGL-context calculated */
        volatile bool               m_hasErrors         = false;
        volatile bool               m_isCalculated      = false;

        int32_t                     m_descriptorSet     = -1;
        int32_t                     m_VBO               = -1;
        int32_t                     m_IBO               = -1;
        int32_t                     m_UBO               = -1;

        std::vector<uint32_t>	    m_indices           = std::vector<uint32_t>();
        uint32_t 					m_countVertices	    = 0;
        uint32_t					m_countIndices	    = 0;
        bool                        m_useIndices        = false;
    protected:
         /** \brief Re-calc mesh space-transform matrix */
        virtual void ReCalcModel() { }
    private:
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
        Math::Vector3 m_barycenter = glm::vec3();
        Math::Vector3 m_position   = glm::vec3();
        Math::Vector3 m_rotation   = glm::vec3();
        Math::Vector3 m_scale      = { 1, 1, 1 };
        glm::mat4     m_modelMat   = glm::mat4(0);
    public:
        [[nodiscard]] SR_FORCE_INLINE uint32_t FastGetVBO() const noexcept { return (uint32_t)m_VBO; }
        [[nodiscard]] SR_FORCE_INLINE uint32_t FastGetIBO() const noexcept { return (uint32_t)m_IBO; }
        [[nodiscard]] SR_FORCE_INLINE int32_t  FastGetUBO() const noexcept { return m_UBO;           }

        [[nodiscard]] SR_FORCE_INLINE int32_t GetVBO() {
            if (m_isDestroy)
                return m_VBO;

            if (!m_isCalculated)
                if (!Calculate())
                    return -1;
            return m_VBO;
        }

        [[nodiscard]] std::string GetGeometryName() const noexcept { return this->m_geometry_name; }

        [[nodiscard]] SR_FORCE_INLINE uint32_t GetCountVertices() const noexcept { return m_countVertices;  }
        [[nodiscard]] SR_FORCE_INLINE Material* GetMaterial()   const noexcept { return this->m_material; }
        [[nodiscard]] SR_FORCE_INLINE bool IsCalculated()       const noexcept { return m_isCalculated;   }

        virtual Mesh* Copy() const = 0;

#define ConfigureShader(shader) \
        shader->SetMat4("modelMat", m_modelMat); \
        shader->SetVec3("color", m_material->m_color); \
        shader->SetIVec2("config", { (int)m_material->m_bloom, (int)this->m_isSelected }); \

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
                this->m_material->UseOpenGL();
            }

            this->m_env->DrawTriangles(m_countIndices);

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
                this->m_material->UseOpenGL();
            }

            //this->m_env->DrawLines(m_VAO, m_countVertices);

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
