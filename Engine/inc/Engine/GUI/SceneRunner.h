//
// Created by Monika on 05.07.2022.
//

#ifndef SR_ENGINE_SCENERUNNER_H
#define SR_ENGINE_SCENERUNNER_H

#include <Graphics/GUI/Widget.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>

/**
 * Construct a SceneRunner widget.
 */

/**
 * Destroy the SceneRunner.
 */

/**
 * Assigns a scene to be managed and displayed by this SceneRunner.
 * @param scene Shared pointer to the scene to manage. May be null to clear the current scene.
 */

/**
 * Render the SceneRunner widget and its controls.
 */

/**
 * Start or resume playback of the currently assigned scene.
 * @returns `true` if playback was started or resumed, `false` if there is no scene or playback could not be started.
 */

/**
 * Stop playback and return the editor to its non-playing state.
 */

/**
 * Retrieve the owning EditorGUI instance for this widget.
 * @returns Pointer to the EditorGUI that contains this widget, or `nullptr` if not attached to an editor.
 */
namespace SR_CORE_GUI_NS {
    class EditorGUI;

    class SceneRunner : public SR_GRAPH_NS::GUI::Widget {
    public:
        SceneRunner();
        ~SceneRunner() override = default;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr &scene);

    private:
        void Draw() override;

        bool PlayScene();
        void ReturnScene();

        SR_NODISCARD EditorGUI* GetEditor() const;

    private:
        bool m_isActive = false;
        bool m_isPaused = false;

        SR_WORLD_NS::Scene::Ptr m_scene;
        SR_UTILS_NS::Path m_lastPath;
        SR_UTILS_NS::Path m_scenePath;

    };
}

#endif //SR_ENGINE_SCENERUNNER_H