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

using namespace Framework::Helper;

namespace Framework::Graphics {
    class Window;

    class Camera : public Component {
    private:
    public:
        ~Camera();
        Camera(unsigned char countHDRBuffers = 2);
        void UpdateProjection(unsigned int w, unsigned int h);
        void UpdateProjection();

        inline void SetDirectOutput(bool value) noexcept {
            this->m_isEnableDirectOut = value;
        }
        [[nodiscard]] inline bool IsDirectOutput() const noexcept { return m_isEnableDirectOut; }
    public:
        bool Create(Window* window);

        //void AwaitFree();
        bool Free();
    protected:
        void OnDestroyGameObject() noexcept override;
    public:
        void OnRotate(glm::vec3 newValue) noexcept override;
        void OnMove(glm::vec3 newValue) noexcept override;
    public:
        bool DrawOnInspector() override;

        nlohmann::json Save() override;

        Math::Vector2 WorldToScreenPoint(Math::Vector3 point3D) const noexcept {
            Math::Matrix4x4 viewProjectionMatrix = m_projection * m_viewMat;
            //transform world to clipping coordinates
            point3D = viewProjectionMatrix.Translate(point3D);

            int winX = (int)round(((point3D.x + 1) / 2.0) * m_cameraSize.x);
            //we calculate -point3D.getY() because the screen Y axis is
            //oriented top->down

            int winY = (int)round(((1 - point3D.y) / 2.0) * m_cameraSize.y);
            return Math::Vector2(winX, winY);
        }

        inline Math::Vector3 ScreenToWorldPoint(Math::Vector2 scr) const noexcept {
            return Math::Vector3();

            // NORMALISED DEVICE SPACE
            //double x = 2.0 * 800 / m_cameraSize.x - 1;
            //double y = 2.0 * 450 / m_cameraSize.y - 1;

            /*scr = Math::Vector2(
                    2.0 * scr.x / m_cameraSize.x - 1,
                    2.0 * scr.y / m_cameraSize.y - 1
                    );


            Debug::Log(scr.ToString());

            double x = scr.x;
            double y = scr.y;

            // HOMOGENEOUS SPACE
            glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);
            // Projection/Eye Space
            glm::mat4 ProjectView = m_projection * m_viewMat;
            glm::mat4 viewProjectionInverse = inverse(ProjectView);
            glm::vec4 worldPos = viewProjectionInverse * screenPos;
            return glm::vec3(worldPos);*/

            /*auto matInverse = Math::Matrix4x4(glm::inverse(this->m_viewMat *  this->m_projection));
            return matInverse.GetTranslate(); // return screen resolution, lol*/

            //auto matInverse = Math::Matrix4x4(glm::inverse(this->m_projection * this->m_viewMat));
            //return matInverse.GetTranslate();

            /*glm::mat4 matInverse = glm::inverse(this->m_viewMat *  this->m_projection); // see mul

            float in[4];
            float winZ = 1.0;

            in[0]= (2.0f*((float)(scr.x-0)/(this->m_cameraSize.x-0)))-1.0f,
                    in[1]=1.0f-(2.0f*((float)(scr.y-0)/(this->m_cameraSize.y-0)));
            in[2]=2.0* winZ -1.0;
            in[3]=1.0;

            glm::vec4 pos = glm::vec4(in[0], in[1], in[2], in[3]) * matInverse;

            pos.w = 1.0 / pos.w;

            pos.x *= pos.w;
            pos.y *= pos.w;
            pos.z *= pos.w;

            return glm::vec3(pos);*/
        }

        //[[nodiscard]] inline bool IsUse() const noexcept { return this->m_isUse; }
        //inline void SetUse(bool value) noexcept { this->m_isUse = value; }

        /*[[nodiscard]] inline glm::mat4 GetAlternativeView() const noexcept {
            glm::mat4 matrix(1.f);

            matrix = glm::rotate(matrix,
                                 m_pitch
                    , {1, 0, 0}
            );
            matrix = glm::rotate(matrix,
                                 m_yaw
                    , {0, 1, 0}

            );
            matrix = glm::rotate(matrix,
                                 m_roll
                    , {0, 0, 1}

            );

            return glm::translate(matrix, {
                    -m_pos.x,
                    -m_pos.y,
                    -m_pos.z
            });
        }*/
        [[nodiscard]] inline glm::mat4 GetView() const noexcept { return this->m_viewMat; }
        [[nodiscard]] inline glm::mat4 GetProjection() const noexcept { return this->m_projection; }
        Math::Vector2 GetSize() { return m_cameraSize; }
        PostProcessing* GetPostProcessing() { return m_postProcessing; }

        [[nodiscard]] inline glm::vec3 GetGLPosition() const noexcept { return this->m_pos; }
        void WaitCalculate() const {
            ret:
            if (!m_isCalculate) {
                goto ret;
            }
        }
        void WaitBuffersCalculate() const {
            ret:
            if (!m_isBuffCalculate) {
                goto ret;
            }
        }
        /**
         \brief Update shader parameters: proj-mat and view-mat.
         \warning Call after shader use, and before draw. */
        void UpdateShader(Shader* shader) noexcept;
        void UpdateShaderProjView(Shader* shader) noexcept;
    private:
        void UpdateView() noexcept;
        bool Calculate() noexcept;
    private:
        volatile bool               m_isCreate          = false;
        volatile bool               m_isCalculate       = false;
        volatile bool               m_isBuffCalculate   = false;
        volatile bool               m_needUpdate        = false;

        bool                        m_isEnableDirectOut = false;

        PostProcessing*             m_postProcessing    = nullptr;

        Window*			            m_window			= nullptr;
        glm::mat4		            m_projection		= glm::mat4(0);
        glm::mat4		            m_viewMat			= glm::mat4(0);
        glm::vec3		            m_pos				= {0,0,0};

        float                       m_far               = 8000.f;
        float                       m_near              = 0.1f;

        GUI::ICanvas*               m_canvas            = nullptr;

        glm::vec2                   m_cameraSize        = glm::vec2(0,0);

        //volatile bool               m_isUse             = false;

        volatile float	            m_yaw				= 0;
        volatile float	            m_pitch				= 0;
        volatile float	            m_roll				= 0;

        float			            m_dxx				= 0;
        float			            m_dxz				= 0;
        float			            m_dyy				= 0;
    };
}

#endif //GAMEENGINE_CAMERA_H
