//
// Created by Monika on 16.02.2022.
//

#ifndef SR_ENGINE_GUIZMO_H
#define SR_ENGINE_GUIZMO_H

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Input/InputSystem.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_CORE_GUI_NS {
    enum class EditorSceneViewMode : uint8_t;

    class Guizmo : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using EnginePtr = SR_HTYPES_NS::SharedPtr<Engine>;
    public:
        explicit Guizmo(const EnginePtr& pEngine);
        ~Guizmo() override;

    public:
        void Draw(const GameObjectPtr& gameObject, const GameObjectPtr& camera);
        void DrawTools();

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD bool IsTranslate() const { return  m_operation == ImGuizmo::OPERATION::TRANSLATE; }
        SR_NODISCARD bool IsRotate() const { return m_operation == ImGuizmo::OPERATION::ROTATE; }
        SR_NODISCARD bool IsScale() const { return m_operation == ImGuizmo::OPERATION::SCALE; }
        SR_NODISCARD bool IsBounds() const { return m_operation == ImGuizmo::OPERATION::BOUNDS; }
        SR_NODISCARD bool IsUniversal() const { return m_operation == ImGuizmo::OPERATION::UNIVERSAL; }
        SR_NODISCARD bool IsLocal() const { return m_mode == ImGuizmo::MODE::LOCAL; }
        SR_NODISCARD bool IsCenter() const { return m_center; }
        SR_NODISCARD bool IsUse() const { return m_isUse; }

        void SetMode(ImGuizmo::MODE mode) {
            m_mode = mode;
            m_active = true;
        }

        void SetOperation(ImGuizmo::OPERATION operation) {
            m_operation = operation;
            m_active = true;
        }

        SR_NODISCARD EditorSceneViewMode GetViewMode() const noexcept { return m_viewMode; }
        SR_NODISCARD float_t GetCameraVelocityFactor() const noexcept { return m_cameraVelocityFactor; };

    private:
        glm::mat4 GetMatrix();
        void SetRect(SR_GRAPH_NS::Types::Camera* camera);
        void DrawManipulation(SR_GRAPH_NS::Types::Camera* camera);

    private:
        SR_HTYPES_NS::Marshal*    m_marshal       = nullptr;

        SR_UTILS_NS::Transform*   m_transform     = nullptr;

        bool                      m_isUse         = false;
        bool                      m_isEnabled     = true;

        float_t                   m_cameraVelocityFactor = 1.f;

        int32_t                   m_snapValue     = 100;
        float_t                   m_boundsSnap[3] = { 0.1f, 0.1f, 0.1f };
        float_t                   m_snap[3]       = { 1.f, 1.f, 1.f };
        float_t                   m_bounds[6]     = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };

        std::atomic<bool>         m_boundsActive  = false;
        std::atomic<bool>         m_snapActive    = false;
        std::atomic<bool>         m_center        = false;
        std::atomic<bool>         m_active        = true;

        SR_MATH_NS::FVector3      m_barycenter    = SR_MATH_NS::FVector3();
        ImGuizmo::OPERATION       m_operation     = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE            m_mode          = ImGuizmo::MODE::LOCAL;

        EditorSceneViewMode m_viewMode;

        EnginePtr m_engine;

    };
}

#endif //SR_ENGINE_GUIZMO_H
