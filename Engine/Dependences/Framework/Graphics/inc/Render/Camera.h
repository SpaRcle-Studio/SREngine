//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <Render/Shader.h>
#include <EntityComponentSystem/Component.h>
#include <Render/PostProcessing.h>
#include <Debug.h>
#include <functional>
#include <GUI/ICanvas.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>
#include <Types/Uniforms.h>

using namespace Framework::Helper;

namespace Framework::Graphics {
    class Window;

    class Camera : public Component {
    private:
        ~Camera() = default;
        Camera() : Component("Camera"), m_env(Environment::Get()), m_pipeline(m_env->GetPipeLine()) { }
    public:
        void UpdateProjection(unsigned int w, unsigned int h);
        void UpdateProjection();

        SR_FORCE_INLINE void SetDirectOutput(bool value) noexcept { this->m_isEnableDirectOut = value; }
    public:
        static Camera* Allocate();
    public:
        bool Create(Window* window);

        /// \warning Call only from window class!
        bool Free();
    protected:
        void OnDestroyGameObject() noexcept override;
    public:
        void OnRotate(glm::vec3 newValue) noexcept override;
        void OnMove(glm::vec3 newValue) noexcept override;
    public:
        bool DrawOnInspector() override;

        nlohmann::json Save() override;

        [[nodiscard]] SR_FORCE_INLINE bool IsAllowUpdateProjection() const noexcept { return m_allowUpdateProj; }
        [[nodiscard]] SR_FORCE_INLINE bool IsDirectOutput()     const noexcept  { return m_isEnableDirectOut;        }
        [[nodiscard]] SR_FORCE_INLINE glm::vec3 GetRotation()   const noexcept  { return { m_pitch, m_yaw, m_roll }; }
        [[nodiscard]] SR_FORCE_INLINE glm::mat4 GetView()       const noexcept  { return this->m_viewMat;            }
        [[nodiscard]] SR_FORCE_INLINE glm::mat4 GetProjection() const noexcept  { return this->m_projection;         }
        [[nodiscard]] SR_FORCE_INLINE Math::Vector2 GetSize()   const noexcept  { return m_cameraSize;               }
        [[nodiscard]] SR_FORCE_INLINE PostProcessing* GetPostProcessing() const { return m_postProcessing;           }
        [[nodiscard]] SR_FORCE_INLINE glm::vec3 GetGLPosition() const noexcept  { return this->m_pos;                }

        void WaitCalculate() const {
            ret:
            if (!m_isCalculate)
                goto ret;
        }
        void WaitBuffersCalculate() const {
            ret:
            if (!m_isBuffCalculate)
                goto ret;
        }

        /**
         \brief Update shader parameters: proj-mat and view-mat.
         \warning Call after shader use, and before draw. */
        void UpdateShader(Shader* shader) noexcept;
        void UpdateShaderProjView(Shader* shader) noexcept;

        void OnDestroyComponent() noexcept override {
            Debug::Error("Camera::OnDestroyComponent() : TODO!");
        }
    private:
        void UpdateView() noexcept;
        bool Calculate() noexcept;
    private:
        volatile bool   m_isCreate          = false;
        volatile bool   m_isCalculate       = false;
        volatile bool   m_isBuffCalculate   = false;
        volatile bool   m_needUpdate        = false;

        volatile float  m_yaw               = 0;
        volatile float  m_pitch             = 0;
        volatile float  m_roll              = 0;
    private:
        PostProcessing* m_postProcessing    = nullptr;
        Environment*    m_env               = nullptr;
        const PipeLine  m_pipeline          = PipeLine::Unknown;

        Window*		    m_window	     	= nullptr;
        glm::mat4	    m_projection        = glm::mat4(0);
        glm::mat4	    m_viewMat           = glm::mat4(0);
        glm::vec3	    m_pos               = {0,0,0};

        ProjViewUBO     m_ubo               = { };

        bool            m_isEnableDirectOut = false;
        bool            m_allowUpdateProj   = true;

        float           m_far               = 8000.f;
        float           m_near              = 0.01f;

        GUI::ICanvas*   m_canvas            = nullptr;

        glm::vec2       m_cameraSize        = glm::vec2(0,0);
    };
}

#endif //GAMEENGINE_CAMERA_H
