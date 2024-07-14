//
// Created by Monika on 05.07.2022.
//

#include <Core/GUI/SceneRunner.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Audio/SoundManager.h>
#include <Graphics/Overlay/ImGuiOverlay.h>

namespace SR_CORE_NS::GUI {
    SceneRunner::SceneRunner()
        : SR_GRAPH_NS::GUI::Widget("Scene runner", SR_MATH_NS::IVector2(0, 60))
    { }

    void SceneRunner::SetScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        SR_LOCK_GUARD;
        m_scene = scene;
    }

    void SceneRunner::Draw() {
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        auto&& pOverlay = pEngine->GetRenderContext()->GetPipeline()->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui);
        auto&& pFont = pOverlay.DynamicCast<SR_GRAPH_NS::ImGuiOverlay>()->GetIconFont();

        if (!pFont) {
            return;
        }

        float_t scale = pFont->Scale;
        pFont->Scale /= 3;

        bool locked = false;

        if (m_scene.TryRecursiveLockIfValid()) {
            m_isActive = pEngine->IsActive();
            m_isPaused = pEngine->IsPaused();
            m_lastPath = std::move(m_scene->GetPath());
            locked = true;
        }

        bool active = m_isActive;
        bool paused = m_isPaused;

        ImGui::PushFont(pFont);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

        ImGui::Separator();

        const EditorIcon playIcon = active ? EditorIcon::Stop : EditorIcon::Play;
        if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(playIcon)) {
            if (SR_GRAPH_GUI_NS::ImageButton("##imgScenePlayBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3) && locked) {
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
            if (SR_GRAPH_GUI_NS::ImageButton("##imgScenePauseBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3)) {
                /// SR_AUDIO_NS::SoundManager::Instance().Play("Editor/Audio/Heavy-popping.wav");
                paused = !paused;
            }
        }

        if (paused && active) {
            ImGui::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::FrameSkip)) {
                if (SR_GRAPH_GUI_NS::ImageButton("##imgFrameSkipBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3) && locked) {
                    pEngine->SetOneFramePauseSkip(true);
                }
            }
        }

        if (!m_scene->IsPrefab()) {
            ImGui::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Game)) {
                if (SR_GRAPH_GUI_NS::ImageButton("##imgSceneGameBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3) && locked) {
                    if (!active) {
                        active = PlayScene();
                    }

                    pEngine->SetGameMode(true);
                }
            }
        }

        if (m_scene->IsPrefab()) {
            ImGui::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Back)) {
                if (SR_GRAPH_GUI_NS::ImageButton("##imgSceneBackBtn", pDescriptor, SR_MATH_NS::IVector2(32), 3)) {
                    pEngine->SetActive((active = false));
                    pEngine->GetEditor()->LoadSceneFromCachedPath();
                }
            }
        }

        ImGui::Separator();

        ImGui::PopFont();
        ImGui::PopStyleVar();

        pFont->Scale = scale;

        ImGui::Text("%s", m_isActive ? m_scenePath.CStr() : m_lastPath.CStr());

        ImGui::Separator();

        if (locked) {
            pEngine->SetActive((m_isActive = active));
            pEngine->SetPaused((m_isPaused = paused));
            m_scene.Unlock();
        }
    }

    bool SceneRunner::PlayScene() {
        SR_LOCK_GUARD;

        SR_LOG("SceneRunner::PlayScene() : playing scene \"" + m_lastPath.ToString() + "\"");

        if (!m_scene->Save()) {
            SR_ERROR("SceneRunner::PlayScene() : failed to save scene!");
            return false;
        }

        m_scenePath = m_lastPath;

        const std::string extension = m_scene->GetPath().GetExtension();

        auto&& runtimePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(SR_WORLD_NS::Scene::RuntimeScenePath.ConcatExt(extension));
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (runtimePath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            if (!SR_PLATFORM_NS::Delete(runtimePath)) {
                SR_ERROR("SceneRunner::PlayScene() : failed to delete cached scene!");
                return false;
            }
        }

        SR_LOG("SceneRunner::PlayScene() : copying scene: \n\tFrom: " + m_scene->GetAbsPath().ToString() + "\n\tTo: " + runtimePath.ToString());

        if (m_scene->IsPrefab()) {
            if (!m_scene->GetAbsPath().Copy(runtimePath)) {
                SR_ERROR("SceneRunner::PlayScene() : failed to copy scene!\n\tSource: "
                    + m_scene->GetPath().ToString() + "\n\tDestination: " + runtimePath.ToString());
                return false;
            }
        }
        else {
            if (!m_scene->GetAbsPath().GetFolder().Copy(runtimePath)) {
                SR_ERROR("SceneRunner::PlayScene() : failed to copy scene!\n\tSource: "
                    + m_scene->GetPath().ToString() + "\n\tDestination: " + runtimePath.ToString());
                return false;
            }
        }

        if (auto&& runtimeScene = SR_WORLD_NS::Scene::Load(SR_WORLD_NS::Scene::RuntimeScenePath.ConcatExt(extension))) {
            return pEngine->SetScene(runtimeScene);
        }
        else {
            return false;
        }
    }

    void SceneRunner::ReturnScene() {
        SR_LOG("SceneRunner::ReturnScene() : stopping scene \"" + m_lastPath.ToString() + "\"");

        auto&& originalScene = SR_WORLD_NS::Scene::Load(m_scenePath);
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        pEngine->SetScene(originalScene);
    }

    EditorGUI* SceneRunner::GetEditor() const {
        if (auto&& pEditor = dynamic_cast<EditorGUI*>(GetManager())) {
            return pEditor;
        }

        SRHalt0();

        return nullptr;
    }

}