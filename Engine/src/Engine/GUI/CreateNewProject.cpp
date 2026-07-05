//
// Created by Monika on 23.09.2025.
//

#include <Engine/GUI/CreateNewProject.h>
#include <Engine/Settings/ProjectSettings.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>

#include <Codegen/CreateNewProject.generated.hpp>

namespace SR_CORE_GUI_NS {
    CreateNewProject::CreateNewProject()
        : Super("Create New Project")
    {
        SetDefaultSize({ 400, 300 });
        ResetSettings();
    }

    bool CreateNewProject::CreateProject() {
        auto&& settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
        ProjectSettings::Ptr pSettings = SRNew<ProjectSettings>();
        pSettings->projectName = m_projectName;

        SR_UTILS_NS::SRASerializer serializer;
        serializer.SetUseTabs(true);
        pSettings->Save(serializer);
        if (!serializer.SaveToFile(settingsPath)) {
            SR_ERROR("CreateNewProject::Draw() : failed to save project settings!\n\tPath: ", settingsPath);
            pSettings->DeleteResource();
            return false;
        }
        pSettings->DeleteResource();

        m_projectFinalPath.Concat("Resources").CreateIfNotExists();

        SR_INFO("CreateNewProject::Draw() : project created successfully!\n\tPath: ", m_projectFinalPath);

        return true;
    }

    void CreateNewProject::ResetSettings() {
        m_projectName = "New Project";
        m_projectPath = SR_UTILS_NS::ResourceManager::Instance().GetResPathRef();
        m_projectPathInput = m_projectPath.ToString();
        m_projectFinalPath = m_projectPath.Concat(m_projectName);
    }

    void CreateNewProject::Draw() {
        auto&& size = SR_GRAPH_GUI_NS::Immediate::GetWindowSize();

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::FrameRounding, 0.0f);
        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        {
            SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            SR_GRAPH_GUI_NS::Immediate::Button("Project Name", SR_MATH_NS::FVector2(size.x * 0.3f, 0));
            SR_GRAPH_GUI_NS::Immediate::EndDisabled();

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(size.x * 0.7f);
            {
                if (SR_GRAPH_GUI_NS::Immediate::InputText("##name", &m_projectName)) {
                    m_projectFinalPath = m_projectPath.Concat(m_projectName);
                }
            }
            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
        }

        {
            SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            SR_GRAPH_GUI_NS::Immediate::Button("Location", SR_MATH_NS::FVector2(size.x * 0.2f, 0));
            SR_GRAPH_GUI_NS::Immediate::EndDisabled();

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (SR_GRAPH_GUI_NS::Immediate::Button("...", SR_MATH_NS::FVector2(size.x * 0.1f, 0))) {
                auto path = SR_UTILS_NS::FileDialog::Instance().PickFolder(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef());
                if (!path.IsEmpty()) {
                    m_projectPath = path;
                    m_projectPathInput = m_projectPath.ToString();
                    m_projectFinalPath = m_projectPath.Concat(m_projectName);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(size.x * 0.7f);
            if (SR_GRAPH_GUI_NS::Immediate::InputText("##path", &m_projectPathInput)) {
                m_projectPath = m_projectPathInput;
                m_projectFinalPath = m_projectPath.Concat(m_projectName);
            }
            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
        }

        /// bottom panes with create button
        {
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosY(size.y - 40);

            const bool isOk = !m_projectFinalPath.IsEmpty() && !m_projectName.empty()
                    && !m_projectFinalPath.IsFile() && m_projectFinalPath.GetFiles().empty()
                    && m_projectFinalPath.GetFolders().empty()
                    && m_projectFinalPath.IsAbs()
                    && m_projectFinalPath.IsValidPath();

            bool canOpen = false;
            if (isOk) {
                SR_GRAPH_GUI_NS::Immediate::Text("Project will be created at: ");
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Cyan(), m_projectFinalPath.empty() ?  "!! Invalid path !!" : m_projectFinalPath.c_str());
                SR_GRAPH_GUI_NS::Immediate::SameLine();
            }
            else {
                auto&& settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
                if (settingsPath.IsFile()) {
                    canOpen = true;
                    SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Green(), "You can open project at: ");
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "Invalid project name or path, or directory is not empty!");
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }
            }

            if (isOk || canOpen) {
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, SR_MATH_NS::FColor(0.0f, 0.5f, 0.0f, 1.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0.0f, 0.6f, 0.0f, 1.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, SR_MATH_NS::FColor(0.0f, 0.7f, 0.0f, 1.0f));
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, SR_MATH_NS::FColor(0.5f, 0.0f, 0.0f, 1.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0.6f, 0.0f, 0.0f, 1.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, SR_MATH_NS::FColor(0.7f, 0.0f, 0.0f, 1.0f));
            }

            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(size.x - 110);

            if (!isOk && !canOpen) {
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            }

            if (canOpen) {
                if (SR_GRAPH_GUI_NS::Immediate::Button("Open", SR_MATH_NS::FVector2(100, 30))) {
                    SaveLastProjectPath();
                    SR_UTILS_NS::CLIManager::Instance().SetProjectPath(m_projectFinalPath);
                    dynamic_cast<EditorGUI*>(GetManager())->GetEngine()->Reload();
                }
            }
            else if (SR_GRAPH_GUI_NS::Immediate::Button("Create", SR_MATH_NS::FVector2(100, 30)) && isOk) {
                CreateProject();
                SaveLastProjectPath();
            }

            if (!isOk && !canOpen) {
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }

            SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar(2);
    }

    void CreateNewProject::OnOpen() {
        ResetSettings();

        m_projectName = SR_UTILS_NS::StoreUtils::User::GetString("LastCreatedProjectName", m_projectName);
        m_projectPath = SR_UTILS_NS::StoreUtils::User::GetString("LastCreatedProjectPath", m_projectPath.ToString());
        if (m_projectName.empty() || m_projectPath.empty()) {
            ResetSettings();
        }
        else {
            m_projectFinalPath = m_projectPath.Concat(m_projectName);
        }

        Super::OnOpen();
    }

    void CreateNewProject::SaveLastProjectPath() {
        SR_UTILS_NS::StoreUtils::User::SetString("LastCreatedProjectName", m_projectName);
        SR_UTILS_NS::StoreUtils::User::SetString("LastCreatedProjectPath", m_projectPath.ToString());
        SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
    }
}
