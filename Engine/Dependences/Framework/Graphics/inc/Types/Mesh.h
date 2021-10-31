//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <vector>
#include <macros.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <Render/Shader.h>
#include <Types/Material.h>
#include <ResourceManager/IResource.h>

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

    enum class MeshFeatures {
        None     = 0,
        Vertices = 1 << 0,
        Indices  = 1 << 1,
        Skinning = 1 << 2
    };

    SR_ENUM_CLASS(MeshType,
        Unknown = 0,
        Static = 1,
        Wireframe = 2,
        Skinned = 3,
    )

    class Mesh : public IResource, public Component {
        friend class Material;
        friend class ::Framework::API;
    protected:
        Mesh();
        Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
    protected:
        ~Mesh() override;
    protected:
        bool                         m_inverse           = false;

        Environment*                 m_env               = nullptr;
        const PipeLine               m_pipeline          = PipeLine::Unknown;

        mutable std::recursive_mutex m_mutex             = std::recursive_mutex();

        std::string                  m_geometry_name     = "Unnamed";
        Shader*                      m_shader            = nullptr;
        Render*                      m_render            = nullptr;
        Material*                    m_material          = nullptr;

        volatile bool                m_hasErrors         = false;
        volatile bool                m_isCalculated      = false;

        int32_t                      m_descriptorSet     = SR_ID_INVALID;
        int32_t                      m_UBO               = SR_ID_INVALID;
    public:
        Math::Vector3                m_barycenter = glm::vec3();
        Math::Vector3                m_position   = glm::vec3();
        Math::Vector3                m_rotation   = glm::vec3();
        Math::Vector3                m_scale      = { 1, 1, 1 };
        glm::mat4                    m_modelMat   = glm::mat4(0);
    public:
        static Mesh* Allocate(MeshType type);
        static std::vector<Mesh*> Load(const std::string& path, MeshType type);
    public:
        /** \brief Set mesh to destroy in res manager
        * \return bool */
        bool Destroy() override;
    protected:
         /** \brief Re-calc mesh space-transform matrix */
        virtual void ReCalcModel();
        virtual bool Calculate();
    public:
        virtual Mesh* Copy(Mesh* mesh = nullptr) const;

        virtual void DrawVulkan() = 0;
        virtual void DrawOpenGL() = 0;

        /** \warning call only from render */
        virtual bool FreeVideoMemory();
    protected:
        bool DrawOnInspector() override;
        Math::Vector3 GetBarycenter() const override;
    public:
        SR_FORCE_INLINE void OnMove(const Math::Vector3& newValue) override {
            m_position = newValue.ToGLM();
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnRotate(const Math::Vector3& newValue) override{
            m_rotation = newValue.ToGLM();
            ReCalcModel();
        }
        SR_FORCE_INLINE void OnScaled(const Math::Vector3& newValue) override{
            m_scale = newValue.ToGLM();
            ReCalcModel();
        }
        void OnSelected(bool value) override;
        void OnDestroyGameObject() override;
        void OnRemoveComponent() override {
            this->OnDestroyGameObject();
        }
        void OnReady(bool ready) override {
            this->m_env->SetBuildState(false);
        }
        void OnAttachComponent() override { }
    public:
        void WaitCalculate() const;
        bool IsCanCalculate() const;

        [[nodiscard]] std::string GetGeometryName() const { return this->m_geometry_name; }
        [[nodiscard]] Shader* GetShader()           const { return this->m_shader; }
        [[nodiscard]] Material* GetMaterial()       const { return this->m_material; }
        [[nodiscard]] bool IsCalculated()           const { return m_isCalculated; }
        [[nodiscard]] bool GetInverse()             const { return this->m_inverse; }

        void SetRender(Render* render) { this->m_render = render; };
        void SetInverse(bool value) { this->m_inverse = value; ReCalcModel(); }
    };
}

#endif //GAMEENGINE_MESH_H
