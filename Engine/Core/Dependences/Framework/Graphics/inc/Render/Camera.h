//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <Render/Shader.h>
#include <EntityComponentSystem/Component.h>
#include <Render/PostProcessing.h>
#include <Environment/Environment.h>
#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>
#include <Types/Uniforms.h>
#include <Events/EventManager.h>

namespace SR_GRAPH_NS {
    class Window;

    /// TODO: TO_REFACTORING
    class Camera : public SR_UTILS_NS::Component {
    private:
        Camera();
        ~Camera() override = default;

    public:
        static Camera* Allocate(uint32_t width = 0, uint32_t height = 0);
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

    public:
        bool Create(Window* window);

        /// \warning Call only from window class!
        bool Free();

        void OnRotate(const SR_MATH_NS::FVector3& newValue) override;
        void OnMove(const SR_MATH_NS::FVector3& newValue) override;
        void OnReady(bool ready) override;

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsAllowUpdateProjection() const { return m_allowUpdateProj;      }
        SR_NODISCARD SR_FORCE_INLINE bool IsDirectOutput() const { return m_isEnableDirectOut.first;       }
        SR_NODISCARD SR_FORCE_INLINE bool IsNeedUpdate() const { return m_needUpdate;                      }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetRotation() const { return { m_pitch, m_yaw, m_roll };    }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetView() const { return m_viewMat;                         }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetViewTranslate() const { return m_viewTranslateMat;       }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetProjection() const { return m_projection;                }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::IVector2 GetSize() const { return m_cameraSize;           }
        SR_NODISCARD SR_FORCE_INLINE PostProcessing* GetPostProcessing() const { return m_postProcessing;  }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetGLPosition() const { return m_position.ToGLM();          }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFar() const { return m_far;                                }
        SR_NODISCARD SR_FORCE_INLINE float_t GetNear() const { return m_near;                              }
        SR_NODISCARD SR_FORCE_INLINE Window* GetWindow() const { return m_window;                          }

        SR_NODISCARD glm::mat4 GetImGuizmoView() const noexcept;

        void WaitCalculate() const;
        void WaitBuffersCalculate() const;
        bool CompleteResize();
        void PoolEvents();

        /**
         \brief Update shader parameters: proj-mat and view-mat.
         \warning Call after shader use, and before draw. */
        template <typename T> void UpdateShader(Shader* shader) noexcept {
            if (!m_isCreate) {
                SR_WARN("Camera::UpdateShader() : camera is not create! Something went wrong...");
                return;
            }

            if (!shader->Complete())
                return;

            if (m_needUpdate) {
                if (!CompleteResize()) {
                    SR_ERROR("Camera::UpdateShader() : failed to complete resize!");
                    return;
                }
            }

            if (m_pipeline == PipeLine::OpenGL) {
                if constexpr (std::is_same<T, ProjViewUBO>::value)
                    shader->SetMat4("PVmat", this->m_projection * this->m_viewTranslateMat);
                else if constexpr (std::is_same<T, SkyboxUBO>::value)
                    shader->SetMat4("PVmat", this->m_projection * this->m_viewMat);
            }
            else {
                if constexpr (std::is_same<T, ProjViewUBO>::value) {
                    ProjViewUBO ubo = {};
                    ubo.view = this->m_viewTranslateMat;
                    ubo.proj = this->m_projection;
                    m_env->UpdateUBO(shader->GetUBO(0), &ubo, sizeof(ProjViewUBO));
                }
                else if constexpr (std::is_same<T, SkyboxUBO>::value) {
                    SkyboxUBO ubo = {};
                    ubo.PVMat = m_projection * m_viewMat;
                    m_env->UpdateUBO(shader->GetUBO(0), &ubo, sizeof(SkyboxUBO));
                }
            }
        }

        void UpdateShaderProjView(Shader* shader) noexcept;

        void UpdateProjection(uint32_t w, uint32_t h);
        void UpdateProjection();

        void SetDirectOutput(bool value);
        void SetFar(float_t value);
        void SetNear(float_t value);

    private:
        void UpdateView() noexcept;
        bool Calculate() noexcept;
        void OnRemoveComponent() override;
        void OnDestroyGameObject() override;

    private:
        std::atomic<bool>     m_isCreate          = false;
        std::atomic<bool>     m_isCalculate       = false;
        std::atomic<bool>     m_isBuffCalculate   = false;
        std::atomic<bool>     m_needUpdate        = false;
        std::atomic<bool>     m_allowUpdateProj   = true;

        volatile float_t      m_yaw               = 0;
        volatile float_t      m_pitch             = 0;
        volatile float_t      m_roll              = 0;

        std::atomic<float_t>  m_far               = 500.f;
        std::atomic<float_t>  m_near              = 0.01f;

        const PipeLine        m_pipeline          = PipeLine::Unknown;

        Window*		          m_window	     	  = nullptr;
        Environment*          m_env               = nullptr;
        PostProcessing*       m_postProcessing    = nullptr;

        glm::mat4	          m_projection        = glm::mat4(0);
        glm::mat4	          m_viewTranslateMat  = glm::mat4(0);
        glm::mat4	          m_viewMat           = glm::mat4(0);

        // 1 - current, 2 - new
        std::pair<bool, bool> m_isEnableDirectOut = { false, false };

        SR_MATH_NS::FVector3  m_position          = { 0, 0, 0 };
        SR_MATH_NS::IVector2  m_cameraSize        = { 0, 0 };
    };
}

#endif //GAMEENGINE_CAMERA_H
