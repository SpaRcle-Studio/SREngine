//
// Created by Monika on 13.08.2022.
//

#ifndef SR_ENGINE_EDITOR_CAMERA_H
#define SR_ENGINE_EDITOR_CAMERA_H

#include <Graphics/Types/Camera.h>

namespace SR_CORE_GUI_NS {
    class SceneViewer;

    /// @category(Editor)
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
