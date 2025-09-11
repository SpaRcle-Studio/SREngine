

# File EditorCamera.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**EditorCamera.h**](EditorCamera_8h.md)

[Go to the documentation of this file](EditorCamera_8h.md)


```C++
//
// Created by Monika on 13.08.2022.
//

#ifndef SR_ENGINE_EDITOR_CAMERA_H
#define SR_ENGINE_EDITOR_CAMERA_H

#include <Graphics/Types/Camera.h>

namespace SR_CORE_GUI_NS {
    class SceneViewer;

    class EditorCamera : public SR_GTYPES_NS::Camera {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EditorCamera>;

    public:
        void SetSceneViewer(SceneViewer* pSceneViewer) { m_sceneViewer = pSceneViewer; }

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        SR_NODISCARD SR_MATH_NS::FPoint GetMousePos() const override;

    private:
        SceneViewer* m_sceneViewer = nullptr;

    };
}

#endif //SR_ENGINE_EDITORCAMERA_H
```


