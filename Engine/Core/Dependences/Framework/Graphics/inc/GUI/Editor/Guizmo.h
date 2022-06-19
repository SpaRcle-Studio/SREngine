//
// Created by Monika on 16.02.2022.
//

#ifndef SRENGINE_GUIZMO_H
#define SRENGINE_GUIZMO_H

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Input/InputSystem.h>

namespace SR_GRAPH_NS {
    class Camera;
}

namespace SR_GRAPH_NS::GUI {
    class Guizmo : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        using GameObject = SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>;
    public:
        Guizmo() = default;
        ~Guizmo() override = default;

    public:
        void Draw(GameObject gameObject, GameObject camera);
        void DrawTools();

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD bool IsTranslate() const { return m_operation == ImGuizmo::OPERATION::TRANSLATE; }
        SR_NODISCARD bool IsRotate() const { return m_operation == ImGuizmo::OPERATION::ROTATE; }
        SR_NODISCARD bool IsScale() const { return m_operation == ImGuizmo::OPERATION::SCALE; }
        SR_NODISCARD bool IsBounds() const { return m_operation == ImGuizmo::OPERATION::BOUNDS; }
        SR_NODISCARD bool IsUniversal() const { return m_operation == ImGuizmo::OPERATION::UNIVERSAL; }
        SR_NODISCARD bool IsLocal() const { return m_mode == ImGuizmo::MODE::LOCAL; }
        SR_NODISCARD bool IsCenter() const { return m_center; }

        void SetMode(ImGuizmo::MODE mode) {
            m_mode = mode;
            m_active = true;
        }

        void SetOperation(ImGuizmo::OPERATION operation) {
            m_operation = operation;
            m_active = true;
        }

    private:
        glm::mat4 GetMatrix();
        void SetRect(SR_GRAPH_NS::Camera* camera);
        void DrawManipulation(SR_GRAPH_NS::Camera* camera);

    private:
        SR_UTILS_NS::Transform3D* m_transform     = nullptr;
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

    };
}

#endif //SRENGINE_GUIZMO_H
