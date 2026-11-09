//
// Created by Monika on 05.07.2022.
//

#include <Engine/GUI/SceneRunner.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Audio/SoundManager.h>

#include <Graphics/Overlay/ImGuiOverlay.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/TaskManager/TaskManager.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/FileSystem/VFS.h>

#include <Codegen/SceneRunner.generated.hpp>

namespace SR_CORE_NS::GUI {
    SceneRunner::SceneRunner()
        : SR_GRAPH_NS::GUI::Widget("Scene runner", SR_MATH_NS::IVector2(0, 60))
    { }

    void SceneRunner::Draw() {
        SR_TRACY_ZONE;

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        auto&& pOverlay = pEngine->GetRenderContext()->GetPipeline()->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui);
        auto&& pFont = pOverlay.DynamicCast<SR_GRAPH_NS::ImGuiOverlay>()->GetIconFont();
        float_t iconSize = SR_UTILS_NS::StoreUtils::User::GetFloat("EditorFontSize", SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE) * 4.0f;
        int32_t framePadding = 3;

        auto&& pScene = pEngine->GetScene();

        if (!pFont) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.0f, 0.25f, 0.25f, 1.0f), "Failed to get icon font!");
            return;
        }

        bool locked = false;

        if (pScene) {
            m_isActive = pEngine->IsActive();
            m_isPaused = pEngine->IsPaused();
            m_lastPath = pScene->GetPath();
            locked = true;
        }

        bool active = m_isActive;
        bool paused = m_isPaused;

        SR_IMMEDIATE_GUI_NS::PushFont(pFont);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameBorderSize, 0.0f);

        SR_IMMEDIATE_GUI_NS::Separator();

        const EditorIcon playIcon = active ? EditorIcon::Stop : EditorIcon::Play;
        if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(playIcon)) {
            if (SR_IMMEDIATE_GUI_NS::ImageButton("##imgScenePlayBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
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

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(paused ? EditorIcon::Pause : EditorIcon::PauseActive)) {
            if (SR_IMMEDIATE_GUI_NS::ImageButton("##imgScenePauseBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding)) {
                /// SR_AUDIO_NS::SoundManager::Instance().Play("Editor/Audio/Heavy-popping.wav");
                paused = !paused;
            }
        }

        if (paused && active) {
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::FrameSkip)) {
                if (SR_IMMEDIATE_GUI_NS::ImageButton("##imgFrameSkipBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
                    pEngine->SetOneFramePauseSkip(true);
                }
            }
        }

        if (!pScene->IsPrefab()) {
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Game)) {
                if (SR_IMMEDIATE_GUI_NS::ImageButton("##imgSceneGameBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding) && locked) {
                    if (!active) {
                        active = PlayScene();
                    }

                    pEngine->SetGameMode(true);
                }
            }
        }

        if (pScene->IsPrefab()) {
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (auto&& pDescriptor = GetEditor()->GetIconDescriptor(EditorIcon::Back)) {
                if (SR_IMMEDIATE_GUI_NS::ImageButton("##imgSceneBackBtn", pDescriptor, SR_MATH_NS::FVector2(iconSize), framePadding)) {
                    pScene->SaveScene();

                    auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();
                    if (auto&& pPrefab = resourcesManager.Find<SR_UTILS_NS::Prefab>(pScene->GetPath(), nullptr)) {
                        pPrefab->Reload();
                    }

                    pEngine->SetActive((active = false));
                    pEngine->GetEditor()->LoadSceneFromCachedPath();
                }
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        SR_IMMEDIATE_GUI_NS::PopFont();
        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::Text("%s", m_isActive ? m_scenePath.CStr() : m_lastPath.CStr());

        SR_IMMEDIATE_GUI_NS::Separator();

        if (locked) {
            pEngine->SetActive((m_isActive = active));
            pEngine->SetPaused((m_isPaused = paused));
        }

        const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;
        const int32_t widgetSize = (framePadding * 2 + iconSize) + lineHeight + 10;
        SetSize(SR_MATH_NS::IVector2(0, widgetSize));
    }

    bool SceneRunner::PlayScene() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        auto&& pScene = pEngine->GetScene();
        if (!pScene) {
            return false;
        }

        if (!pScene->SaveScene()) {
            SR_ERROR("SceneRunner::PlayScene() : failed to save scene!");
            return false;
        }

        if (m_lastPath.IsEmpty() && pScene) {
            m_lastPath = pScene->GetPath();
        }

        if (m_lastPath.IsEmpty()) {
            SRHalt("SceneRunner::PlayScene() : scene path is empty!");
            return false;
        }

        SR_LOG("SceneRunner::PlayScene() : playing scene \"" + m_lastPath.ToString() + "\"");

        pEngine->RunSceneGameMode(m_lastPath, false);
        m_scenePath = m_lastPath;
        return true;
    }

    void SceneRunner::ReturnScene() {
        SR_TRACY_ZONE;
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
