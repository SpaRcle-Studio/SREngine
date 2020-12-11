//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <Render/Shader.h>
#include <EntityComponentSystem/Component.h>
#include <Render/PostProcessing.h>
#include <Debug.h>

using namespace Framework::Helper;

namespace Framework::Graphics {
    class Window;

    class Camera : public Component {
    private:
        ~Camera();
    public:
        Camera();
        void UpdateProjection(unsigned int w, unsigned int h);
    public:
        bool Create(Window* window);

        inline void AwaitFree(){
            ret: if (m_isUse)
                goto ret;
            this->Free();
        }
        inline bool Free(){
            if (m_isUse){
                Debug::Error("Camera::Free() : camera used now!");
                return false;
            }
            else{
                Debug::Log("Camera::Free() : free camera pointer...");
                delete this;
                return true;
            }
        }
    protected:
        void OnDestroyGameObject() noexcept override;
    public:
        void OnRotate(glm::vec3 newValue) noexcept override;
        void OnMove(glm::vec3 newValue) noexcept override;
    public:
        inline bool IsUse() const noexcept { return this->m_isUse; }
        inline void SetUse(bool value) noexcept { this->m_isUse = value; }

        glm::vec2 GetSize() { return m_cameraSize; }
        PostProcessing* GetPostProcessing() { return m_postProcessing; }
        /**
         \brief Update shader parameters: proj-mat and view-mat.
         \warning Call after shader use, and before draw. */
        void UpdateShader(Shader* shader) noexcept;
    private:
        void UpdateView() noexcept;
        bool Calculate() noexcept;
    private:
        volatile bool   m_isCreate          = false;
        volatile bool   m_isCaclucate       = false;
        volatile bool   m_needUpdate        = false;

        PostProcessing* m_postProcessing    = nullptr;

        Window*			m_window			= nullptr;
        glm::mat4		m_projection		= glm::mat4(0);
        glm::mat4		m_viewMat			= glm::mat4(0);
        glm::vec3		m_pos				= {0,0,0};

        glm::vec2       m_cameraSize        = glm::vec2(0,0);

        volatile bool   m_isUse             = false;

        volatile float	m_yaw				= 0;
        volatile float	m_pitch				= 0;
        volatile float	m_roll				= 0;

        float			m_dxx				= 0;
        float			m_dxz				= 0;
        float			m_dyy				= 0;
    };
}

#endif //GAMEENGINE_CAMERA_H
