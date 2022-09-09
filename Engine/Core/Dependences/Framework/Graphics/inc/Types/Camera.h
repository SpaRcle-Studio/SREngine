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
    class RenderTechnique;
    class RenderScene;
}

namespace SR_GTYPES_NS {
    class Camera : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1001);
        using RenderTechniquePtr = std::variant<SR_UTILS_NS::Path, RenderTechnique*>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    public:
        explicit Camera(uint32_t width = 0, uint32_t height = 0);
        ~Camera() override;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void OnMatrixDirty() override;
        void OnAttached() override;
        void UpdateProjection(uint32_t w, uint32_t h);

    public:
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetRotation() const { return { m_pitch, m_yaw, m_roll }; }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetViewRef() const noexcept { return m_viewMat; }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetOrthogonalRef() const noexcept { return m_orthogonal; }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetViewTranslateRef() const noexcept { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetViewTranslate() const { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 GetProjection() const { return m_projection;                    }
        SR_NODISCARD SR_FORCE_INLINE const glm::mat4& GetProjectionRef() const noexcept { return m_projection;          }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::IVector2 GetSize() const { return m_viewportSize;             }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 GetPosition() const { return m_position; }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetGLPosition() const { return m_position.ToGLM();              }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFar() const { return m_far;                                    }
        SR_NODISCARD SR_FORCE_INLINE float_t GetNear() const { return m_near;                                  }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFOV() const { return m_FOV;                                    }
        SR_NODISCARD SR_FORCE_INLINE int32_t GetPriority() const { return m_priority; }

        SR_NODISCARD glm::mat4 GetImGuizmoView() const noexcept;
        SR_NODISCARD glm::vec3 GetViewDirection() const;
        SR_NODISCARD glm::vec3 GetViewDirection(const SR_MATH_NS::FVector3& pos) const;

        SR_NODISCARD RenderTechnique* GetRenderTechnique();
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SR_UTILS_NS::SavableFlags flags) const override;

        void SetFar(float_t value);
        void SetNear(float_t value);
        void SetFOV(float_t value);
        void SetPriority(int32_t priority);

        void SetRenderTechnique(const SR_UTILS_NS::Path& path);

    private:
        void UpdateProjection();

        void UpdateView() noexcept;

        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;

    private:
        /** >= 0 - одна главная камера, < 0 - закадровые камеры, которые рендерятся в RenderTexture.
         * Выбирается та камера, что ближе к нулю */
        int32_t               m_priority          = 0;

        float_t               m_yaw               = 0;
        float_t               m_pitch             = 0;
        float_t               m_roll              = 0;

        float_t               m_far               = 2000.f;
        float_t               m_near              = 0.01f;
        float_t               m_aspect            = 1.f;
        float_t               m_FOV               = 60.f;

        glm::mat4	          m_projection        = glm::mat4(0);
        glm::mat4	          m_viewTranslateMat  = glm::mat4(0);
        glm::mat4	          m_viewMat           = glm::mat4(0);
        glm::mat4	          m_orthogonal        = glm::mat4(0);

        SR_MATH_NS::FVector3  m_position          = { 0, 0, 0 };
        SR_MATH_NS::IVector2  m_viewportSize      = { 0, 0 };

        RenderTechniquePtr    m_renderTechnique   = { };

    };
}

#endif //GAMEENGINE_CAMERA_H
