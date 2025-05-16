//
// Created by Monika on 05.07.2022.
//

#include <Engine/GUI/SceneRunner.h>
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
        float_t iconSize = SR_UTILS_NS::StoreUtils::User::GetFloat("ImGuiIconFontSize", 32.f);
        int32_t framePadding = 3;

        if (!pFont) {
            return;
        }

        bool locked = false;

        if (m_scene.TryRecursiveLockIfValid()) {
            m_isActive = pEngine->IsActive();
            m_isPaused = pEngine->IsPaused();
            m_lastPath = std::move(m_scene->GetPath());
            locked = true;
        }

        bool active = m_isActive;
        bool paused = m_isPaused;

        SR_GRAPH_GUI_NS::Immediate::PushFont(pFont);
        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::FrameBorderSize, 0.0f);

        SR_GRAPH_GUI_NS::Immediate::Separator();

        const EditorIcon playIcon = active ? EditorIcon::Stop : EditorIcon::Play;
        if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(playIcon)) {
            if (SR_GRAPH_GUI_NS::Immediate::ImageButton("##imgScenePlayBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
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

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(paused ? EditorIcon::Pause : EditorIcon::PauseActive)) {
            if (SR_GRAPH_GUI_NS::Immediate::ImageButton("##imgScenePauseBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding)) {
                /// SR_AUDIO_NS::SoundManager::Instance().Play("Editor/Audio/Heavy-popping.wav");
                paused = !paused;
            }
        }

        if (paused && active) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::FrameSkip)) {
                if (SR_GRAPH_GUI_NS::Immediate::ImageButton("##imgFrameSkipBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
                    pEngine->SetOneFramePauseSkip(true);
                }
            }
        }

        if (!m_scene->IsPrefab()) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Game)) {
                if (SR_GRAPH_GUI_NS::Immediate::ImageButton("##imgSceneGameBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
                    if (!active) {
                        active = PlayScene();
                    }

                    pEngine->SetGameMode(true);
                }
            }
        }

        if (m_scene->IsPrefab()) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Back)) {
                if (SR_GRAPH_GUI_NS::Immediate::ImageButton("##imgSceneBackBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding)) {
                    pEngine->SetActive((active = false));
                    pEngine->GetEditor()->LoadSceneFromCachedPath();
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_GRAPH_GUI_NS::Immediate::PopFont();
        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::Text("%s", m_isActive ? m_scenePath.CStr() : m_lastPath.CStr());

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (locked) {
            pEngine->SetActive((m_isActive = active));
            pEngine->SetPaused((m_isPaused = paused));
            m_scene.Unlock();
        }

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        const int32_t widgetSize = (framePadding * 2 + iconSize) + lineHeight + 10;
        SetSize(SR_MATH_NS::IVector2(0, widgetSize));
    }

    bool SceneRunner::PlayScene() {
        SR_LOCK_GUARD;

        SR_LOG("SceneRunner::PlayScene() : playing scene \"" + m_lastPath.ToString() + "\"");

        if (!m_scene->SaveScene()) {
            SR_ERROR("SceneRunner::PlayScene() : failed to save scene!");
            return false;
        }

        m_scenePath = m_lastPath;

        const std::string extension = m_scene->GetPath().GetExtension();

        auto&& runtimePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(SR_UTILS_NS::Path(SR_WORLD_NS::Scene::RuntimeScenePath).ConcatExt(extension));
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (runtimePath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            if (!SR_PLATFORM_NS::Delete(runtimePath)) {
                SR_ERROR("SceneRunner::PlayScene() : failed to delete cached scene!");
                return false;
            }
        }

        SR_LOG("SceneRunner::PlayScene() : copying scene: \n\tFrom: " + m_scene->GetAbsPath().ToString() + "\n\tTo: " + runtimePath.ToString());

        if (!runtimePath.Create()) {
            SR_ERROR("SceneRunner::PlayScene() : failed to create runtime scene folder!");
            return false;
        }

        if (!m_scene->GetAbsPath().Copy(runtimePath)) {
            SR_ERROR("SceneRunner::PlayScene() : failed to copy scene!\n\tSource: "
                + m_scene->GetPath().ToString() + "\n\tDestination: " + runtimePath.ToString());
            return false;
        }

        if (auto&& runtimeScene = SR_WORLD_NS::Scene::LoadScene(SR_UTILS_NS::Path(SR_WORLD_NS::Scene::RuntimeScenePath).ConcatExt(extension))) {
            pEngine->AddSceneToQueue(runtimeScene);
            return true;
        }
        return false;
    }

    void SceneRunner::ReturnScene() {
        SR_LOG("SceneRunner::ReturnScene() : stopping scene \"" + m_lastPath.ToString() + "\"");

        auto&& originalScene = SR_WORLD_NS::Scene::LoadScene(m_scenePath);
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        pEngine->AddSceneToQueue(originalScene);
    }

    EditorGUI* SceneRunner::GetEditor() const {
        if (auto&& pEditor = dynamic_cast<EditorGUI*>(GetManager())) {
            return pEditor;
        }

        SRHalt0();

        return nullptr;
    }

}
