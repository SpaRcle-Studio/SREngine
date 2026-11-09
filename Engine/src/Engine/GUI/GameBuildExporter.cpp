//
// Created by OpenAI Codex on 09.11.2026.
//

#include <Engine/GUI/GameBuildExporter.h>

#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Resources/ResourceManager.h>

#include <Codegen/GameBuildExporter.generated.hpp>

namespace SR_CORE_GUI_NS {
    static constexpr SR_UTILS_NS::StringView EngineRepository = "https://github.com/SpaRcle-Studio/SREngine";

    GameBuildExporter::GameBuildExporter()
        : Super("Game Build Exporter", SR_MATH_NS::IVector2(680, 720))
    { }

    GameBuildExporter::~GameBuildExporter() = default;

    void GameBuildExporter::OnOpen() {
        if (LoadProjectSettings()) {
            m_cppScriptsFound = false;
            SR_UTILS_NS::VFS::Instance().Enumerate(
                SR_UTILS_NS::ResourceManager::Instance().GetResPath(),
                [this](const SR_UTILS_NS::VFSEntry& entry) {
                    if (entry.extension == "cpp" || entry.extension == "h" || entry.extension == "hpp") {
                        m_cppScriptsFound = true;
                    }
                },
                true
            );
        }
    }

    bool GameBuildExporter::LoadProjectSettings() {
        if (!SR_UTILS_NS::VFS::Instance().IsExists(".srproject")) {
            return true;
        }

        if (m_pProjectSettings) {
            return true;
        }

        m_pProjectSettings = CoreResLoader::Load<ProjectSettings>(".srproject");
        if (!m_pProjectSettings) {
            SetStatus("Project settings were not found.", true);
            return false;
        }

        if (m_pProjectSettings->buildProfiles.empty()) {
            m_pProjectSettings->buildProfiles.emplace_back();
            m_pProjectSettings->activeBuildProfile = 0;
        }
        auto&& defaultProfile = m_pProjectSettings->buildProfiles.front();
        if (defaultProfile.productName == "Game") {
            defaultProfile.productName = m_pProjectSettings->projectName.ToString();
        }
        if (defaultProfile.startScene.IsEmpty()) {
            defaultProfile.startScene = m_pProjectSettings->mainScene;
        }
        return true;
    }

    GameBuildProfile* GameBuildExporter::GetActiveProfile() const {
        if (!m_pProjectSettings || m_pProjectSettings->buildProfiles.empty()) {
            return nullptr;
        }
        if (m_pProjectSettings->activeBuildProfile >= m_pProjectSettings->buildProfiles.size()) {
            m_pProjectSettings->activeBuildProfile = 0;
        }
        return &m_pProjectSettings->buildProfiles[m_pProjectSettings->activeBuildProfile];
    }

    SR_UTILS_NS::String GameBuildExporter::GetReleaseTag() const {
        const SR_UTILS_NS::StringView branch = SR_ENGINE_BRANCH;
        if (branch.starts_with("release/")) {
            return "v{}"_format(SR_ENGINE_VERSION);
        }
        return "dev-latest";
    }

    SR_UTILS_NS::Path GameBuildExporter::GetBuildCachePath() const {
        return SR_PLATFORM_NS::GetUserDataDirectory()
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().organization)
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().name)
            .Concat("BuildCache")
            .Concat(GetReleaseTag() == "dev-latest" ? "latest" : SR_ENGINE_VERSION);
    }

    void GameBuildExporter::SetStatus(SR_UTILS_NS::String status, bool error) {
        m_status = std::move(status);
        m_statusError = error;
        if (error) {
            SR_ERROR("GameBuildExporter::SetStatus() : {}", m_status);
        }
        else {
            SR_INFO("GameBuildExporter::SetStatus() : {}", m_status);
        }
    }

    bool GameBuildExporter::ExportPlatform(SR_UTILS_NS::StringView platformName, SR_UTILS_NS::StringView assetName) {
        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            return false;
        }

        const auto cachePath = GetBuildCachePath();
        if (!cachePath.CreateDirectories()) {
            SetStatus("Failed to create engine build cache.", true);
            return false;
        }

        const auto cachedArtifact = cachePath.Concat(assetName);
        if (!cachedArtifact.IsFile()) {
            const auto url = "{}/releases/download/{}/{}"_format(EngineRepository, GetReleaseTag(), assetName);
            SetStatus("Downloading {}..."_format(platformName));
            if (!SR_PLATFORM_NS::DownloadFile(url.c_str(), cachedArtifact)) {
                SetStatus("Failed to download {} build."_format(platformName), true);
                return false;
            }
        }

        auto outputPath = m_outputRoot.Concat(platformName);
        if (!outputPath.CreateDirectories()) {
            SetStatus("Failed to create output directory for {}."_format(platformName), true);
            return false;
        }

        if (!cachedArtifact.Copy(outputPath.Concat(assetName))) {
            SetStatus("Failed to stage {} build."_format(platformName), true);
            return false;
        }

        return true;
    }

    bool GameBuildExporter::Build() {
        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            SetStatus("No active build profile.", true);
            return false;
        }

        const auto version = SR_UTILS_NS::String(SR_ENGINE_VERSION);
        const bool latest = GetReleaseTag() == "dev-latest";
        const auto suffix = latest ? "-dev" : "";

        m_outputRoot = CoreResLoader::GetResPath();
        SR_UTILS_NS::VFS::Instance().ResolvePath(m_outputRoot, SR_UTILS_NS::FileMode::Write);
        m_outputRoot = m_outputRoot.GetPrevious().Concat(pProfile->outputPath);

        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> pBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_outputRoot);
        SR_UTILS_NS::VFS::Instance().Mount(m_outputRoot, pBackend.Get(), 0);
        pBackend.SetDeleter([](SR_UTILS_NS::IVFSBackend* pVFS) {
            SR_UTILS_NS::VFS::Instance().Unmount(pVFS);
            delete pVFS;
        });

        SR_UTILS_NS::EnumReflector::ForEach<SR_UTILS_NS::PlatformType>([&](SR_UTILS_NS::PlatformType platform) {
            const auto platformPath = m_outputRoot.Concat(SR_UTILS_NS::EnumReflector::ToStringAtom(platform));
            if (platformPath.IsDir()) {
                SR_UTILS_NS::VFS::Instance().Delete(platformPath);
            }
        });

        bool success = true;
        if (pProfile->windows) {
            success &= ExportPlatform("Windows", "SREngine_v{}{}_windows.x86_64.exe"_format(version, suffix));
        }
        if (pProfile->linux) {
            success &= ExportPlatform("Linux", "SREngine_v{}{}_linux.x86_64"_format(version, suffix));
        }
        if (pProfile->androidArm64) {
            success &= ExportPlatform("Android", "SREngine_v{}{}_android.arm64-v8a.apk"_format(version, suffix));
        }
        if (pProfile->androidX64) {
            success &= ExportPlatform("Android", "SREngine_v{}{}_android.x86_64.apk"_format(version, suffix));
        }
        if (pProfile->emscripten) {
            success &= ExportPlatform("Emscripten", "SREngine_v{}{}_emscripten.zip"_format(version, suffix));
        }

        if (success) {
            if (!m_pProjectSettings->SaveAsset()) {
                SetStatus("Builds were exported, but project settings could not be saved.", true);
                return false;
            }
            SetStatus("Build completed.");
        }
        return success;
    }

    void GameBuildExporter::Draw() {
        if (!LoadProjectSettings()) {
            SR_IMMEDIATE_GUI_NS::TextWrapped("%s", m_status.c_str());
            return;
        }

        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            SR_IMMEDIATE_GUI_NS::Text("Is not a valid project. Please check the .srproject file.");
            return;
        }

        SR_IMMEDIATE_GUI_NS::Text("Engine branch: %s", SR_ENGINE_BRANCH);
        SR_IMMEDIATE_GUI_NS::Text("Release source: %s", GetReleaseTag().c_str());
        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginCombo("Configuration", pProfile->name.c_str())) {
            for (uint32_t i = 0; i < m_pProjectSettings->buildProfiles.size(); ++i) {
                if (SR_IMMEDIATE_GUI_NS::Selectable(
                    m_pProjectSettings->buildProfiles[i].name.c_str(),
                    i == m_pProjectSettings->activeBuildProfile
                )) {
                    m_pProjectSettings->activeBuildProfile = i;
                    pProfile = GetActiveProfile();
                }
            }
            SR_IMMEDIATE_GUI_NS::EndCombo();
        }
        if (SR_IMMEDIATE_GUI_NS::Button("New configuration")) {
            auto copy = *pProfile;
            copy.name = "New configuration";
            m_pProjectSettings->buildProfiles.emplace_back(copy);
            m_pProjectSettings->activeBuildProfile = m_pProjectSettings->buildProfiles.size() - 1;
            pProfile = GetActiveProfile();
        }
        SR_IMMEDIATE_GUI_NS::SameLine();
        if (m_pProjectSettings->buildProfiles.size() > 1 && SR_IMMEDIATE_GUI_NS::Button("Delete configuration")) {
            m_pProjectSettings->buildProfiles.erase(
                m_pProjectSettings->buildProfiles.begin() + m_pProjectSettings->activeBuildProfile
            );
            m_pProjectSettings->activeBuildProfile = 0;
            pProfile = GetActiveProfile();
        }

        SR_IMMEDIATE_GUI_NS::InputText("Profile", &pProfile->name);
        SR_IMMEDIATE_GUI_NS::InputText("Product", &pProfile->productName);
        SR_IMMEDIATE_GUI_NS::InputText("Organization", &pProfile->organization);
        SR_IMMEDIATE_GUI_NS::InputText("Output", &pProfile->outputPath.GetInternalUnsafeString());
        SR_IMMEDIATE_GUI_NS::InputText("Start scene", &pProfile->startScene.GetInternalUnsafeString());
        int32_t buildConfiguration = static_cast<int32_t>(pProfile->configuration);
        if (SR_IMMEDIATE_GUI_NS::Combo("Build type", &buildConfiguration, "Release\0Debug\0")) {
            pProfile->configuration = static_cast<GameBuildConfiguration>(buildConfiguration);
        }
        int32_t desktopPackageMode = static_cast<int32_t>(pProfile->desktopPackageMode);
        if (SR_IMMEDIATE_GUI_NS::Combo("Desktop package", &desktopPackageMode, "Monolithic\0Portable ZIP\0")) {
            pProfile->desktopPackageMode = static_cast<DesktopBuildPackageMode>(desktopPackageMode);
        }
        SR_IMMEDIATE_GUI_NS::Checkbox("Windows", &pProfile->windows);
        SR_IMMEDIATE_GUI_NS::Checkbox("Linux", &pProfile->linux);
        SR_IMMEDIATE_GUI_NS::Checkbox("Android arm64-v8a", &pProfile->androidArm64);
        SR_IMMEDIATE_GUI_NS::Checkbox("Android x86_64", &pProfile->androidX64);
        SR_IMMEDIATE_GUI_NS::Checkbox("Emscripten", &pProfile->emscripten);
        SR_IMMEDIATE_GUI_NS::InputText("Android package ID", &pProfile->androidPackageId);
        SR_IMMEDIATE_GUI_NS::InputText("Android version", &pProfile->androidVersionName);
        int32_t versionCode = static_cast<int32_t>(pProfile->androidVersionCode);
        if (SR_IMMEDIATE_GUI_NS::InputInt("Android version code", &versionCode)) {
            pProfile->androidVersionCode = static_cast<uint32_t>(versionCode > 0 ? versionCode : 1);
        }
        SR_IMMEDIATE_GUI_NS::Checkbox("Create platform archives", &pProfile->createPlatformArchives);
        SR_IMMEDIATE_GUI_NS::Checkbox("Enable web preview", &pProfile->enableWebPreview);
        SR_IMMEDIATE_GUI_NS::Separator();

        if (m_cppScriptsFound) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.7f, 0.f, 1.f), "C++ scripts are not supported and will be excluded.");
        }

        if (SR_IMMEDIATE_GUI_NS::Button("Build", SR_MATH_NS::FVector2(160.f, 36.f))) {
            Build();
        }

        if (!m_status.empty()) {
            const auto color = m_statusError
                ? SR_MATH_NS::FColor(1.f, 0.25f, 0.25f, 1.f)
                : SR_MATH_NS::FColor(0.35f, 1.f, 0.45f, 1.f);
            SR_IMMEDIATE_GUI_NS::TextColored(color, "%s", m_status.c_str());
        }
    }
}
