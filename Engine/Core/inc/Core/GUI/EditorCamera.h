//
// Created by Monika on 13.08.2022.
//

#ifndef SRENGINE_EDITORCAMERA_H
#define SRENGINE_EDITORCAMERA_H

#include <Types/Camera.h>

namespace SR_CORE_NS::GUI {
    class EditorCamera : public SR_GTYPES_NS::Camera {
        SR_ENTITY_SET_VERSION(1000);
    public:
        explicit EditorCamera(uint32_t width = 0, uint32_t height = 0);
        ~EditorCamera() override = default;

    public:
        SR_NODISCARD bool ExecuteInEditMode() const override;

    };
}

namespace SR_CORE_NS::GUI {
    EditorCamera::EditorCamera(uint32_t width, uint32_t height)
        : Camera(width, height)
    { }

    bool EditorCamera::ExecuteInEditMode() const {
        return true;
    }
}

#endif //SRENGINE_EDITORCAMERA_H
