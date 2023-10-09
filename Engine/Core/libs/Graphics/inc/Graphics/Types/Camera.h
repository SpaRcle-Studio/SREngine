//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

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
        SR_INITIALIZE_COMPONENT(Camera);
        struct RenderTechniqueInfo {
            SR_UTILS_NS::Path path;
            RenderTechnique* pTechnique = nullptr;
        };
        using Ptr = SR_HTYPES_NS::SharedPtr<Camera>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using Super = SR_UTILS_NS::Component;
    public:
        explicit Camera(uint32_t width = 0, uint32_t height = 0);
        ~Camera() override;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void OnMatrixDirty() override;
        void OnAttached() override;
        void UpdateProjection(uint32_t w, uint32_t h);

        SR_NODISCARD virtual bool IsEditorCamera() const noexcept { return false; }

        SR_NODISCARD Component* CopyComponent() const override;

    public:
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetViewRef() const noexcept { return m_viewMat; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetOrthogonalRef() const noexcept { return m_orthogonal; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetViewTranslateRef() const noexcept { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::Matrix4x4 GetViewTranslate() const { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::Matrix4x4 GetProjection() const { return m_projection; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetProjectionRef() const noexcept { return m_projection; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Quaternion& GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::UVector2 GetSize() const { return m_viewportSize; }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 GetViewPosition() const;
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 GetPosition() const { return m_position; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::FVector3& GetPositionRef() const { return m_position; }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetGLPosition() const { return m_position.ToGLM(); }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFar() const { return m_far; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetNear() const { return m_near; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFOV() const { return m_FOV; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetAspect() const { return m_aspect; }
        SR_NODISCARD SR_FORCE_INLINE int32_t GetPriority() const { return m_priority; }

        SR_NODISCARD SR_MATH_NS::Matrix4x4 GetImGuizmoView() const noexcept;
        SR_NODISCARD const SR_MATH_NS::FVector3& GetViewDirection() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetViewDirection(const SR_MATH_NS::FVector3& pos) const noexcept;

        SR_NODISCARD RenderTechnique* GetRenderTechnique();
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD RenderScenePtr TryGetRenderScene() const;

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

        void SetFar(float_t value);
        void SetNear(float_t value);
        void SetFOV(float_t value);
        void SetPriority(int32_t priority);

        void SetRenderTechnique(const SR_UTILS_NS::Path& path);

    protected:
        void UpdateProjection();

        void UpdateView() noexcept;

        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;

    private:
        /** >= 0 - одна главная камера, < 0 - закадровые камеры, которые рендерятся в RenderTexture.
         * Выбирается та камера, что ближе к нулю */
        int32_t m_priority = 0;

        float_t m_far      = 750.f;
        float_t m_near     = 0.01f;
        float_t m_aspect   = 1.f;
        float_t m_FOV      = 90.f;

        SR_MATH_NS::Matrix4x4 m_projection;
        SR_MATH_NS::Matrix4x4 m_viewTranslateMat;
        SR_MATH_NS::Matrix4x4 m_viewMat;
        SR_MATH_NS::Matrix4x4 m_orthogonal;

        SR_MATH_NS::Quaternion m_rotation;

        SR_MATH_NS::FVector3 m_viewDirection;
        SR_MATH_NS::FVector3 m_position;
        SR_MATH_NS::UVector2 m_viewportSize;

        RenderTechniqueInfo m_renderTechnique = { };

    };
}

#endif //GAMEENGINE_CAMERA_H
