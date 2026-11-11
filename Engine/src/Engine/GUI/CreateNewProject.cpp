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
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Platform/Platform.h>

#include <Codegen/CreateNewProject.generated.hpp>

namespace SR_CORE_GUI_NS {
    CreateNewProject::CreateNewProject()
        : Super("Create New Project")
    {
        SetDefaultSize({ 400, 300 });
        ResetSettings();
    }

    CreateNewProject::~CreateNewProject() {
        if (m_pVFSBackend) {
            SR_UTILS_NS::VFS::Instance().Unmount(m_pVFSBackend);
            delete m_pVFSBackend;
        }
    }

    bool CreateNewProject::CreateProject() {
        auto&& settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
        ProjectSettings::Ptr pSettings = SRNew<ProjectSettings>();
        pSettings->projectName = m_projectName;

        if (!pSettings->SaveAsset(settingsPath)) {
            SR_ERROR("CreateNewProject::Draw() : failed to save project settings!\n\tPath: ", settingsPath);
            pSettings->DeleteResource();
            return false;
        }
        pSettings->DeleteResource();

        m_projectFinalPath.Concat("Resources").CreateDirectories();

        SR_INFO("CreateNewProject::Draw() : project created successfully!\n\tPath: ", m_projectFinalPath);

        return true;
    }

    void CreateNewProject::ResetSettings() {
        m_projectName = "New Project";
        SetProjectPath(SR_PLATFORM_NS::GetApplicationUserDataDirectory().Concat("Projects"));
        m_projectPathInput = m_projectPath.ToString();
        m_projectFinalPath = m_projectPath.Concat(m_projectName);
        m_settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
    }

    void CreateNewProject::Draw() {
        auto&& size = SR_IMMEDIATE_GUI_NS::GetWindowSize();

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        {
            SR_IMMEDIATE_GUI_NS::BeginDisabled();
            SR_IMMEDIATE_GUI_NS::Button("Project Name", SR_MATH_NS::FVector2(size.x * 0.3f, 0));
            SR_IMMEDIATE_GUI_NS::EndDisabled();

            SR_IMMEDIATE_GUI_NS::SameLine();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(size.x * 0.7f);
            {
                if (SR_IMMEDIATE_GUI_NS::InputText("##name", &m_projectName)) {
                    m_projectFinalPath = m_projectPath.Concat(m_projectName);
                    m_settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
                }
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }

        {
            SR_IMMEDIATE_GUI_NS::BeginDisabled();
            SR_IMMEDIATE_GUI_NS::Button("Location", SR_MATH_NS::FVector2(size.x * 0.2f, 0));
            SR_IMMEDIATE_GUI_NS::EndDisabled();

            SR_IMMEDIATE_GUI_NS::SameLine();

            if (SR_IMMEDIATE_GUI_NS::Button("...", SR_MATH_NS::FVector2(size.x * 0.1f, 0))) {
                auto path = SR_UTILS_NS::FileDialog::Instance().PickFolder(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef());
                if (!path.IsEmpty()) {
                    SetProjectPath(path);
                    m_projectPathInput = m_projectPath.ToString();
                    m_projectFinalPath = m_projectPath.Concat(m_projectName);
                    m_settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
                }
            }

            SR_IMMEDIATE_GUI_NS::SameLine();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(size.x * 0.7f);
            if (SR_IMMEDIATE_GUI_NS::InputText("##path", &m_projectPathInput)) {
                SetProjectPath(m_projectPathInput);
                m_projectFinalPath = m_projectPath.Concat(m_projectName);
                m_settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }

        /// bottom panes with create button
        {
            SR_IMMEDIATE_GUI_NS::SetCursorPosY(size.y - 40);

            const bool isOk = !m_projectFinalPath.IsEmpty() && !m_projectName.empty()
                    && !m_projectFinalPath.IsFile()
                    && m_projectFinalPath.IsDirectoryEmpty()
                    && m_projectFinalPath.IsAbs()
                    && m_projectFinalPath.IsValidPath();

            bool canOpen = false;
            if (isOk) {
                SR_IMMEDIATE_GUI_NS::Text("Project will be created at: ");
                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Cyan(), m_projectFinalPath.empty() ?  "!! Invalid path !!" : m_projectFinalPath.c_str());
                SR_IMMEDIATE_GUI_NS::SameLine();
            }
            else {
                if (m_settingsPath.IsFile()) {
                    canOpen = true;
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Green(), "You can open project at: ");
                    SR_IMMEDIATE_GUI_NS::SameLine();
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Cyan(), m_projectFinalPath.empty() ?  "!! Invalid path !!" : m_projectFinalPath.c_str());
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
                else {
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Red(), "Invalid project name or path, or directory is not empty!");
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
            }

            if (isOk || canOpen) {
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, SR_MATH_NS::FColor(0.0f, 0.5f, 0.0f, 1.0f));
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0.0f, 0.6f, 0.0f, 1.0f));
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, SR_MATH_NS::FColor(0.0f, 0.7f, 0.0f, 1.0f));
            }
            else {
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, SR_MATH_NS::FColor(0.5f, 0.0f, 0.0f, 1.0f));
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0.6f, 0.0f, 0.0f, 1.0f));
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, SR_MATH_NS::FColor(0.7f, 0.0f, 0.0f, 1.0f));
            }

            SR_IMMEDIATE_GUI_NS::SetCursorPosX(size.x - 110);

            if (!isOk && !canOpen) {
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
            }

            if (canOpen) {
                if (SR_IMMEDIATE_GUI_NS::Button("Open", SR_MATH_NS::FVector2(100, 30))) {
                    SaveLastProjectPath();
                    SR_UTILS_NS::CLIManager::Instance().SetProjectPath(m_projectFinalPath);
                    dynamic_cast<EditorGUI*>(GetManager())->GetEngine()->Reload();
                }
            }
            else if (SR_IMMEDIATE_GUI_NS::Button("Create", SR_MATH_NS::FVector2(100, 30)) && isOk) {
                CreateProject();
                SaveLastProjectPath();
            }

            if (!isOk && !canOpen) {
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }

            SR_IMMEDIATE_GUI_NS::PopStyleColor(3);
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar(2);
    }

    void CreateNewProject::OnOpen() {
        ResetSettings();

        m_projectName = SR_UTILS_NS::StoreUtils::User::GetString("LastCreatedProjectName", m_projectName);
        SetProjectPath(SR_UTILS_NS::StoreUtils::User::GetString("LastCreatedProjectPath", m_projectPath.ToString()));
        if (m_projectName.empty() || m_projectPath.empty()) {
            ResetSettings();
        }
        else {
            m_projectFinalPath = m_projectPath.Concat(m_projectName);
            m_settingsPath = m_projectFinalPath.Concat(".{}"_format(ProjectSettings::GetMetaStatic()->GetExtension()));
        }

        Super::OnOpen();
    }

    void CreateNewProject::SaveLastProjectPath() {
        SR_UTILS_NS::StoreUtils::User::SetString("LastCreatedProjectName", m_projectName);
        SR_UTILS_NS::StoreUtils::User::SetString("LastCreatedProjectPath", m_projectPath.ToString());
        SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
    }

    void CreateNewProject::SetProjectPath(const SR_UTILS_NS::Path& path) {
        if (m_lastProjectPath != path) {
            m_lastProjectPath = path;
            m_projectPathInput = path.ToStringView();
            m_projectPath = path;
            SR_LOG("CreateNewProject::SetProjectPath() : new project path \"{}\"", path);
            if (m_pVFSBackend) {
                SR_UTILS_NS::VFS::Instance().Unmount(m_pVFSBackend);
                delete m_pVFSBackend;
            }
            m_pVFSBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_projectPath);
            SR_UTILS_NS::VFS::Instance().Mount(m_projectPath, m_pVFSBackend, -10000);
        }
    }
}
