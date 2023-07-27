//
// Created by Monika on 05.07.2022.
//

#include <Core/GUI/SceneRunner.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Audio/SoundManager.h>

namespace SR_CORE_NS::GUI {
    SceneRunner::SceneRunner()
        : SR_GRAPH_NS::GUI::Widget("Scene runner", SR_MATH_NS::IVector2(0, 60))
    { }

    void SceneRunner::SetScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        SR_LOCK_GUARD
        m_scene = scene;
    }

    void SceneRunner::Draw() {
        auto&& engine = Engine::Instance();

        auto&& font = SR_GRAPH_NS::Environment::Get()->GetIconFont();
        float_t scale = font->Scale;
        font->Scale /= 3;

        bool locked = false;

        if (m_scene.TryRecursiveLockIfValid()) {
            m_isActive = engine.IsActive();
            m_isPaused = engine.IsPaused();
            m_lastPath = std::move(m_scene->GetPath());
            locked = true;
        }

        bool active = m_isActive;
        bool paused = m_isPaused;

        ImGui::PushFont(font);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

        ImGui::Separator();

        if (m_scene->IsPrefab())
        {
            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Back)) {
                if (GUISystem::Instance().ImageButton("##imgSceneBackBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3)) {
                    Engine::Instance().GetEditor()->LoadSceneFromCachedPath();
                }
            }
        }
        else 
        {
            const EditorIcon playIcon = active ? EditorIcon::Stop : EditorIcon::Play;
            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(playIcon)) {
                if (GUISystem::Instance().ImageButton("##imgScenePlayBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3) && locked) {
                    active = !active;

                    if (active) {
                        active = PlayScene();
                    }
                    else {
                        paused = false;
                        ReturnScene();
                    }
                }
            }

            ImGui::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(paused ? EditorIcon::Pause : EditorIcon::PauseActive)) {
                if (GUISystem::Instance().ImageButton("##imgScenePauseBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3)) {
                    SR_AUDIO_NS::SoundManager::Instance().Play("Editor/Audio/Heavy-popping.wav");
                    paused = !paused;
                }
            }

            ImGui::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Game)) {
                if (GUISystem::Instance().ImageButton("##imgSceneGameBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3) && locked) {
                    if (!active) {
                        active = PlayScene();
                    }

                    Engine::Instance().SetGameMode(true);
                }
            }
        }

        ImGui::Separator();

        ImGui::PopFont();
        ImGui::PopStyleVar();

        font->Scale = scale;

        ImGui::Text("%s", m_isActive ? m_scenePath.CStr() : m_lastPath.CStr());

        ImGui::Separator();

        if (locked) {
            engine.SetActive((m_isActive = active));
            engine.SetPaused((m_isPaused = paused));
            m_scene.Unlock();
        }
    }

    bool SceneRunner::PlayScene() {
        SR_LOCK_GUARD

        SR_LOG("SceneRunner::PlayScene() : play scene \"" + m_lastPath.ToString() + "\"");

        if (!m_scene->Save()) {
            SR_ERROR("SceneRunner::PlayScene() : failed to save scene!");
            return false;
        }

        m_scenePath = m_lastPath;

        auto&& runtimePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(SR_WORLD_NS::Scene::RuntimeScenePath.ConcatExt("scene"));

        if (runtimePath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            if (!SR_PLATFORM_NS::Delete(runtimePath)) {
                SR_ERROR("SceneRunner::PlayScene() : failed to delete cached scene!");
                return false;
            }
        }

        SR_LOG("SceneRunner::PlayScene() : copy scene: \n\tFrom: " + m_scene->GetPath().ToString() + "\n\tTo: " + runtimePath.ToString());

        if (!m_scene->GetAbsPath().GetFolder().Copy(runtimePath)) {
            SR_ERROR("SceneRunner::PlayScene() : failed to copy scene!\n\tSource: "
                + m_scene->GetPath().ToString() + "\n\tDestination: " + runtimePath.ToString());
            return false;
        }

        if (auto&& runtimeScene = SR_WORLD_NS::Scene::Load(SR_WORLD_NS::Scene::RuntimeScenePath.ConcatExt("scene"))) {
            return Engine::Instance().SetScene(runtimeScene);
        }
        else {
            return false;
        }
    }

    void SceneRunner::ReturnScene() {
        SR_LOG("SceneRunner::ReturnScene() : stop scene \"" + m_lastPath.ToString() + "\"");

        auto&& originalScene = SR_WORLD_NS::Scene::Load(m_scenePath);
        Engine::Instance().SetScene(originalScene);
    }

    EditorGUI *SceneRunner::GetEditor() const {
        if (auto&& pEditor = dynamic_cast<EditorGUI*>(GetManager())) {
            return pEditor;
        }

        SRHalt0();

        return nullptr;
    }

}