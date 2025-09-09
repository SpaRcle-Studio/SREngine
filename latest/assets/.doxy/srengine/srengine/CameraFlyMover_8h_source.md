

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
        void FixedUpdate() override;
        void OnDisable() override;

        void SetVelocityFactor(const float_t factor) { m_velocityFactor = factor; }
        void SetActive(const bool active) { m_active = active; }
        void SetExecuteInEditMode(bool enabled);
        void SetRightMouseButtonToRotate(const bool enabled) { m_rightMouseButtonToRotate = enabled; }

        SR_NODISCARD bool ExecuteInEditMode() const override { return m_executeInEditorMode; }

    private:
        std::optional<CursorLock> m_lock;

    private:
        bool m_active = true;
        bool m_lockCursor = false;
        bool m_rightMouseButtonToRotate = false;
        bool m_executeInEditorMode = false;
        float_t m_velocityDegree = 0.8f;
        float_t m_velocityFactor = 1.0f;
        float_t m_seekSpeed = 0.01f;
        float_t m_wheelSpeed = 0.4f;
        float_t m_rotateSpeed = 0.15f;
        float_t m_moveSpeed = 0.2f;
        float_t m_maxVelocity = 2.f;
        SR_MATH_NS::FVector3 m_velocity;

    };
}

#endif //SR_ENGINE_UTILS_CAMERA_FLY_MOVER_H
```


