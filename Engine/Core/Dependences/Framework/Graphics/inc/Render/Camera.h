//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <Environment/Environment.h>

#include <Utils/ECS/Component.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_GRAPH_NS {
    class Window;

    class Camera : public SR_UTILS_NS::Component {
    private:
        Camera();

    public:
        ~Camera() override = default;

    public:
        static Camera* Allocate(uint32_t width = 0, uint32_t height = 0);
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void OnRotate(const SR_MATH_NS::FVector3& newValue) override;
        void OnMove(const SR_MATH_NS::FVector3& newValue) override;

    public:
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetRotation() const { return { m_pitch, m_yaw, m_roll };        }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetView() const { return m_viewMat;                             }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetViewRef() const { return m_viewMat;                   }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetViewTranslateRef() const { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetViewTranslate() const { return m_viewTranslateMat;           }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetProjection() const { return m_projection;                    }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetProjectionRef() const { return m_projection;          }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::IVector2 GetSize() const { return m_viewportSize;             }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetGLPosition() const { return m_position.ToGLM();              }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFar() const { return m_far;                                    }
        SR_NODISCARD SR_FORCE_INLINE float_t GetNear() const { return m_near;                                  }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFOV() const { return m_FOV;                                    }

        SR_NODISCARD glm::mat4 GetImGuizmoView() const noexcept;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SR_UTILS_NS::SavableFlags flags) const override;

        void UpdateProjection(uint32_t w, uint32_t h);
        void UpdateProjection();

        void SetFar(float_t value);
        void SetNear(float_t value);
        void SetFOV(float_t value);

    private:
        void UpdateView() noexcept;

        void OnDestroy() override;
        void OnEnabled() override;
        void OnDisabled() override;

    private:
        float_t               m_yaw               = 0;
        float_t               m_pitch             = 0;
        float_t               m_roll              = 0;

        float_t               m_far               = 500.f;
        float_t               m_near              = 0.01f;
        float_t               m_aspect            = 1.f;
        float_t               m_FOV               = 60.f;

        const PipeLine        m_pipeline          = PipeLine::Unknown;

        glm::mat4	          m_projection        = glm::mat4(0);
        glm::mat4	          m_viewTranslateMat  = glm::mat4(0);
        glm::mat4	          m_viewMat           = glm::mat4(0);

        SR_MATH_NS::FVector3  m_position          = { 0, 0, 0 };
        SR_MATH_NS::IVector2  m_viewportSize      = { 0, 0 };

    };
}

#endif //GAMEENGINE_CAMERA_H
