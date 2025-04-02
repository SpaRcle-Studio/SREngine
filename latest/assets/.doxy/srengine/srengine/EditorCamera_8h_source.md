

# File EditorCamera.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**EditorCamera.h**](EditorCamera_8h.md)

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
        SR_NODISCARD bool IsEditorCamera() const noexcept override { return true; }

        SR_NODISCARD SR_MATH_NS::FPoint GetMousePos() const override;

    private:
        SceneViewer* m_sceneViewer = nullptr;

    };
}

#endif //SR_ENGINE_EDITORCAMERA_H
```


