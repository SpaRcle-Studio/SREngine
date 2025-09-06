

# File Camera.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Camera.h**](Camera_8h.md)

[Go to the documentation of this file](Camera_8h.md)


```C++
//
// Created by Nikita on 18.11.2020.
//

#ifndef SR_ENGINE_CAMERA_H
#define SR_ENGINE_CAMERA_H

#include <Graphics/macros.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_GRAPH_NS {
    class Window;
    class IRenderTechnique;
    class RenderScene;
}

namespace SR_GTYPES_NS {
    SR_ENUM_NS_CLASS_T(CameraType, uint8_t,
        Main,
        Offscreen,
        Editor,
        EditorPrefab
    );

    class Camera : public SR_UTILS_NS::Component {
        SR_CLASS()
        struct RenderTechniqueInfo {
            SR_UTILS_NS::Path path;
            SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::IRenderTechnique> pTechnique;
        };
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using Super = SR_UTILS_NS::Component;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Camera>;

    public:
        Camera();
        ~Camera() override;

    public:
        void Start() override;
        void OnMatrixDirty() override;
        void OnAttached() override;
        void UpdateProjection(uint32_t w, uint32_t h);
        void Update(float_t dt) override;

        SR_NODISCARD virtual bool IsEditorCamera() const noexcept { return false; }

    public:
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetView() const noexcept { return m_viewMat; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetOrthogonal() const noexcept { return m_orthogonal; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetViewTranslate() const noexcept { return m_viewTranslateMat; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetProjection() const noexcept { return m_projection; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4& GetProjectionNoFOV() const noexcept { return m_projectionNoFOV; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Quaternion& GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::UVector2 GetSize() const { return m_viewportSize; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetViewPosition() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCameraEye() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCameraDir() const;
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::FVector3& GetPosition() const { return m_position; }
        SR_NODISCARD SR_FORCE_INLINE glm::vec3 GetGLPosition() const { return m_position.ToGLM(); }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFar() const { return m_far; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetNear() const { return m_near; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetFOV() const { return m_FOV; }
        SR_NODISCARD SR_FORCE_INLINE float_t GetAspect() const { return m_aspect; }
        SR_NODISCARD SR_FORCE_INLINE int32_t GetPriority() const { return m_priority; }
        SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::UVector2& GetViewportSize() const { return m_viewportSize; }

        SR_NODISCARD SR_MATH_NS::Matrix4x4 GetImGuizmoView() const noexcept;
        SR_NODISCARD const SR_MATH_NS::FVector3& GetViewDirection() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetViewDirection(const SR_MATH_NS::FVector3& pos) const noexcept;

        SR_NODISCARD IRenderTechnique* GetRenderTechnique();
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD RenderScenePtr TryGetRenderScene() const;
        SR_NODISCARD const SR_UTILS_NS::Path& GetRenderTechniquePath();

        SR_NODISCARD virtual SR_MATH_NS::FPoint GetMousePos() const;

        SR_NODISCARD float_t CalculateScreenFactor(const SR_MATH_NS::Matrix4x4& modelMatrix, float_t sizeClipSpace, bool orthogonal) const;
        SR_NODISCARD float_t CalculateScreenFactor(const SR_MATH_NS::Matrix4x4& modelMatrix, const SR_MATH_NS::Matrix4x4& viewMatrix, float_t sizeClipSpace, bool orthogonal) const;

        SR_NODISCARD SR_MATH_NS::Ray GetScreenRay(const SR_MATH_NS::FPoint& screenPos, bool orthogonal) const;
        SR_NODISCARD SR_MATH_NS::Ray GetScreenRay(float_t x, float_t y, bool orthogonal) const;
        SR_NODISCARD SR_MATH_NS::FVector3 ScreenToWorldPoint(const SR_MATH_NS::FVector3& screenPos) const;
        SR_NODISCARD SR_MATH_NS::FVector3 ScreenToWorldPoint(const SR_MATH_NS::FVector2& screenPos) const;
        SR_NODISCARD SR_MATH_NS::FVector3 ScreenToWorldPoint(const SR_MATH_NS::FVector2& screenPos, float_t depth) const;

        void SetFar(float_t value);
        void SetNear(float_t value);
        void SetFOV(float_t value);
        void SetPriority(int32_t priority);
        void SetCameraType(CameraType type);

        void SetRenderTechnique(const SR_UTILS_NS::Path& path);

    protected:
        void UpdateProjection();

        void UpdateView() noexcept;

        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;

    private:
        void RemoveTechnique();

    private:
        int32_t m_priority = 0;

        float_t m_far = 750.f;
        float_t m_near = 0.01f;
        float_t m_FOV = 70.f;

        SR_VIRTUAL_PROPERTY

        float_t m_aspect = 1.f;
        bool m_hasErrors = false;
        bool m_isRegistered = false;
        CameraType m_type = CameraType::Main;

        SR_UTILS_NS::Subscription m_onRenderSettingsChanged;

        SR_MATH_NS::Matrix4x4 m_projection;
        SR_MATH_NS::Matrix4x4 m_projectionNoFOV;
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

#endif //SR_ENGINE_CAMERA_H
```


