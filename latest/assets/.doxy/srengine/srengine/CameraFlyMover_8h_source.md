

# File CameraFlyMover.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Game**](dir_8f1885d18d834cf9a317dd74a37ec10b.md) **>** [**CameraFlyMover.h**](CameraFlyMover_8h.md)

[Go to the documentation of this file](CameraFlyMover_8h.md)


```C++
//
// Created by Monika on 05.03.2025.
//

#ifndef SR_ENGINE_UTILS_CAMERA_FLY_MOVER_H
#define SR_ENGINE_UTILS_CAMERA_FLY_MOVER_H

#include <Utils/ECS/Component.h>

namespace SR_UTILS_NS {
    class CameraFlyMover : public Component {
        SR_CLASS()
        using Super = Component;
    public:
        void FixedUpdate() override {
            m_velocity *= m_velocityDegree;

            if (!m_velocity.Empty()) {
                GetTransform()->Translate(m_velocity);
            }

            if (!m_active) {
                return;
            }

            const float_t velocitySpeed = m_moveSpeed * m_velocityFactor;
            auto&& dir = SR_UTILS_NS::Input::Instance().GetMouseDrag();
            auto&& wheel = SR_UTILS_NS::Input::Instance().GetMouseWheel() * m_wheelSpeed * m_velocityFactor;

            if (!SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl)) {
                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                    m_velocity += SR_UTILS_NS::Transform3D::FORWARD * velocitySpeed;
                }

                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::S)) {
                    m_velocity -= SR_UTILS_NS::Transform3D::FORWARD * velocitySpeed;
                }

                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::A)) {
                    m_velocity -= SR_UTILS_NS::Transform3D::RIGHT * velocitySpeed;
                }

                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::D)) {
                    m_velocity += SR_UTILS_NS::Transform3D::RIGHT * velocitySpeed;
                }
            }

            if (wheel != 0) {
                GetTransform()->Translate(SR_UTILS_NS::Transform3D::FORWARD * wheel);
            }

            if (!m_rightMouseButtonToRotate || SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseRight)) {
                GetTransform()->GlobalRotate(dir.y * m_rotateSpeed, dir.x * m_rotateSpeed, 0.0);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseMiddle)) {
                auto right = SR_UTILS_NS::Transform3D::RIGHT * m_seekSpeed;
                auto up = SR_UTILS_NS::Transform3D::UP * m_seekSpeed;

                GetTransform()->Translate((up * dir.y) + (right * -dir.x));
            }
        }

        void SetVelocityFactor(const float_t factor) { m_velocityFactor = factor; }
        void SetActive(const bool active) { m_active = active; }
        void SetExecuteInEditMode(bool enabled);
        void SetRightMouseButtonToRotate(const bool enabled) { m_rightMouseButtonToRotate = enabled; }

        SR_NODISCARD bool ExecuteInEditMode() const override { return m_executeInEditorMode; }

    private:
        bool m_active = true;
        bool m_rightMouseButtonToRotate = false;
        bool m_executeInEditorMode = false;
        float_t m_velocityDegree = 0.8f;
        float_t m_velocityFactor = 1.0f;
        float_t m_seekSpeed = 0.01f;
        float_t m_wheelSpeed = 0.4f;
        float_t m_rotateSpeed = 0.15f;
        float_t m_moveSpeed = 0.2f;
        SR_MATH_NS::FVector3 m_velocity;

    };
}

#endif //SR_ENGINE_UTILS_CAMERA_FLY_MOVER_H
```


