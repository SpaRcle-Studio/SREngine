//
// Created by OpenAI Codex on 09.11.2026.
//

#include <Engine/GUI/GameBuildExporter.h>
#include <Engine/GUI/GameBuildJob.h>

#include <Engine/GUI/GameBuildUI.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Resources/ResourceRef.h>

#include <Codegen/GameBuildExporter.generated.hpp>

namespace SR_CORE_GUI_NS {
    GameBuildExporter::GameBuildExporter()
        : Super("Game Build Exporter")
    {
        SetDefaultSize(SR_MATH_NS::IVector2(780, 760));
    }

    GameBuildExporter::~GameBuildExporter() = default;

    void GameBuildExporter::OnOpen() {
        if (!m_projectReady) {
            m_runtime.Submit([this]() {
                const bool ready = LoadProjectSettings();
                m_projectReady.store(ready, std::memory_order_release);
                if (ready) {
                    m_runtime.Report("Project settings loaded.");
                }
            });
        }
        m_toolsScanned = false;
        m_devicesScanned = false;
        m_imagesScanned = false;
    }

    bool GameBuildExporter::LoadProjectSettings() {
        if (m_pProjectSettings) {
            return true;
        }

        SR_UTILS_NS::RawPointerHolder<ProjectSettings> snapshot;
        SR_UTILS_NS::ResourceManager::Instance().Execute([&snapshot]() {
            const SR_UTILS_NS::ResourceRef<ProjectSettings> source = CoreResLoader::Load<ProjectSettings>(".srproject");
            if (!source) {
                return;
            }
            snapshot = SRNew<ProjectSettings>();
            snapshot.SetDeleter([](ProjectSettings* settings) {
                settings->DeleteResource();
            });
            snapshot->projectName = source->projectName;
            snapshot->mainScene = source->mainScene;
            snapshot->version = source->version;
            snapshot->packages = source->packages;
            snapshot->buildProfiles = source->buildProfiles;
            snapshot->enableCppScripts = source->enableCppScripts;
            snapshot->activeBuildProfile = source->activeBuildProfile;
        });
        if (!snapshot) {
            m_runtime.Report("Project settings were not found.", true);
            return false;
        }
        m_pProjectSettings = std::move(snapshot);

        if (m_pProjectSettings->buildProfiles.empty()) {
            m_pProjectSettings->buildProfiles.emplace_back();
            m_pProjectSettings->activeBuildProfile = 0;
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
        return SR_PLATFORM_NS::GetApplicationUserDataDirectory().Concat("BuildCache")
            .Concat(GetReleaseTag() == "dev-latest" ? "latest" : SR_ENGINE_VERSION);
    }

    SR_UTILS_NS::Path GameBuildExporter::GetOutputPath() const {
        const auto profile = GetActiveProfile();
        if (!profile) {
            return {};
        }
        return profile->outputPath;
    }

    SR_UTILS_NS::Path GameBuildExporter::GetArtifactPath(SR_UTILS_NS::StringView platform, SR_UTILS_NS::StringView suffix) const {
        const auto settings = m_pProjectSettings.Get();
        if (!settings || settings->activeBuildProfile >= settings->buildProfiles.size()) {
            return {};
        }
        const auto output = settings->buildProfiles[settings->activeBuildProfile].outputPath;
        if (output.empty() || settings->projectName.empty() || platform.empty()) {
            return {};
        }
        const SR_UTILS_NS::Path projectName(settings->projectName.ToStringView());
        SR_UTILS_NS::String fileName = projectName.ConvertToFileName();
        fileName += suffix;
        const auto directory = output.Concat(platform);
        return directory.Concat(fileName);
    }

    bool GameBuildExporter::Build() {
        if (!m_projectReady || !m_pProjectSettings || !GetActiveProfile()) {
            m_runtime.Report("No active build profile.", true);
            return false;
        }
        SR_HTYPES_NS::SharedPtr<GameBuildJob> job = new GameBuildJob(*m_pProjectSettings);
        job->onStatus = [this](SR_UTILS_NS::String text, bool error) {
            m_runtime.Report(std::move(text), error);
        };
        job->onProgress = [this](float_t progress) {
            m_runtime.ReportProgress(progress);
        };
        job->onDownload = [this](uint64_t completed, uint64_t total) {
            m_runtime.ReportDownload(completed, total);
        };
        job->isCancelled = [this]() {
            return m_runtime.IsCancelled();
        };
        return m_runtime.Submit([job]() {
            job->Build();
        });
    }

    void GameBuildExporter::Draw() {
        auto runtime = m_runtime.GetStatus();
        if (!m_projectReady.load(std::memory_order_acquire)) {
            if (runtime.busy) {
                SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.f);
                SR_IMMEDIATE_GUI_NS::ProgressBar(-1.f, SR_MATH_NS::FVector2(-1.f, 0.f), "Loading project...");
                SR_IMMEDIATE_GUI_NS::PopStyleVar();
            }
            else {
                SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.message.empty() ? "Open a project to configure its builds." : runtime.message.c_str());
                if (SR_IMMEDIATE_GUI_NS::Button("Reload project settings")) {
                    OnOpen();
                }
            }
            return;
        }
        if (!m_toolsScanned && !runtime.busy) {
            m_runtime.RefreshTools(CoreResLoader::GetResPath());
            m_toolsScanned = true;
            runtime = m_runtime.GetStatus();
        }
        auto profile = GetActiveProfile();
        if (!profile) {
            SR_IMMEDIATE_GUI_NS::TextWrapped("No active build profile.");
            return;
        }

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ChildRounding, 0.f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::PopupRounding, 0.f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::TabRounding, 0.f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::GrabRounding, 0.f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ScrollbarRounding, 0.f);

        SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy && !runtime.logcatRefreshing);
        BuildField("Configuration", [&]() {
            if (SR_IMMEDIATE_GUI_NS::BeginCombo("##configuration", profile->name.c_str())) {
                for (uint32_t i = 0; i < m_pProjectSettings->buildProfiles.size(); ++i) {
                    SR_IMMEDIATE_GUI_NS::PushID(static_cast<int32_t>(i));
                    if (SR_IMMEDIATE_GUI_NS::Selectable(m_pProjectSettings->buildProfiles[i].name.c_str(),
                        i == m_pProjectSettings->activeBuildProfile)) {
                        m_pProjectSettings->activeBuildProfile = i;
                        profile = GetActiveProfile();
                    }
                    SR_IMMEDIATE_GUI_NS::PopID();
                }
                SR_IMMEDIATE_GUI_NS::EndCombo();
            }
        });
        BuildField("Profiles", [&]() {
            if (SR_IMMEDIATE_GUI_NS::Button("New")) {
                auto copy = *profile;
                copy.name = "New configuration";
                m_pProjectSettings->buildProfiles.emplace_back(copy);
                m_pProjectSettings->activeBuildProfile = m_pProjectSettings->buildProfiles.size() - 1;
                profile = GetActiveProfile();
            }
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::BeginDisabled(m_pProjectSettings->buildProfiles.size() <= 1);
            if (SR_IMMEDIATE_GUI_NS::Button("Delete")) {
                m_pProjectSettings->buildProfiles.erase(m_pProjectSettings->buildProfiles.begin() + m_pProjectSettings->activeBuildProfile);
                m_pProjectSettings->activeBuildProfile = 0;
            }
            SR_IMMEDIATE_GUI_NS::EndDisabled();
        });
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginTabBar("BuildAndRunTabs")) {
            if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Export")) {
                DrawExport(runtime);
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }
            if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Run")) {
                DrawLaunch(runtime);
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }
            if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Tools")) {
                DrawTools(runtime);
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }
            if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Logcat")) {
                DrawLogcat(runtime);
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }
            SR_IMMEDIATE_GUI_NS::EndTabBar();
        }

        SR_IMMEDIATE_GUI_NS::Separator();
        if (runtime.busy && !runtime.logcatRefreshing) {
            const auto overlay = runtime.progress >= 0.f
                ? "{:.0f}%"_format(runtime.progress * 100.f) : SR_UTILS_NS::String("Working...");
            SR_IMMEDIATE_GUI_NS::ProgressBar(runtime.progress, SR_MATH_NS::FVector2(-1.f, 0.f), overlay.c_str());
            if (runtime.downloadedBytes > 0) {
                if (runtime.totalBytes > 0) {
                    SR_IMMEDIATE_GUI_NS::Text("%.1f / %.1f MB", runtime.downloadedBytes / 1048576.0, runtime.totalBytes / 1048576.0);
                }
                else {
                    SR_IMMEDIATE_GUI_NS::Text("%.1f MB downloaded", runtime.downloadedBytes / 1048576.0);
                }
            }
            if (SR_IMMEDIATE_GUI_NS::Button("Cancel operation")) {
                m_runtime.Stop();
            }
        }
        if (!runtime.message.empty()) {
            if (runtime.error) {
                SR_IMMEDIATE_GUI_NS::WarningBox(runtime.message.c_str());
            }
            else {
                SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.message.c_str());
            }
        }
        if (!runtime.log.empty() && SR_IMMEDIATE_GUI_NS::CollapsingHeader("Command output")) {
            if (SR_IMMEDIATE_GUI_NS::BeginChild("RuntimeOutput", SR_MATH_NS::FVector2(0.f, 140.f))) {
                SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.log.c_str());
            }
            SR_IMMEDIATE_GUI_NS::EndChild();
        }
        SR_IMMEDIATE_GUI_NS::PopStyleVar(6);
    }

    void GameBuildExporter::DrawExport(const GameBuildRuntime::Status& runtime) {
        auto profile = GetActiveProfile();
        SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy);
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Project", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            BuildField("Name", [&]() {
                SR_IMMEDIATE_GUI_NS::InputText("##value", &profile->name);
            });
            BuildField("Organization", [&]() {
                SR_IMMEDIATE_GUI_NS::InputText("##value", &profile->organization);
            });
            BuildField("Output directory", [&]() {
                SR_IMMEDIATE_GUI_NS::InputText("##value", &profile->outputPath.GetInternalUnsafeString());
            });
            BuildField("Start scene", [&]() {
                SR_IMMEDIATE_GUI_NS::InputText("##value", &m_pProjectSettings->mainScene.GetInternalUnsafeString());
            });
            BuildField("Build type", [&]() {
                int32_t configuration = static_cast<int32_t>(profile->configuration);
                if (SR_IMMEDIATE_GUI_NS::Combo("##value", &configuration, "Release\0Debug\0")) {
                    profile->configuration = static_cast<GameBuildConfiguration>(configuration);
                }
            });
            BuildField("Desktop package", [&]() {
                int32_t mode = static_cast<int32_t>(profile->desktopPackageMode);
                if (SR_IMMEDIATE_GUI_NS::Combo("##value", &mode, "Monolithic\0Portable ZIP\0")) {
                    profile->desktopPackageMode = static_cast<DesktopBuildPackageMode>(mode);
                }
            });
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Platforms", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            BuildField("Windows", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->windows);
            });
            BuildField("Linux", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->linux);
            });
            BuildField("Browser / WebGPU", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->emscripten);
            });
            BuildField("Android arm64-v8a", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->androidArm64);
            });
            BuildField("Android x86_64", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->androidX64);
            });
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Advanced")) {
            BuildField("Web preview", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->enableWebPreview);
            });
            BuildField("Include editor", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("##enabled", &profile->packEditor);
            });
            BuildField("Release source", [&]() {
                SR_IMMEDIATE_GUI_NS::Text("%s", GetReleaseTag().c_str());
            });
            SR_IMMEDIATE_GUI_NS::TextWrapped("Prebuilt Android APKs retain the template package ID and version.");
        }
        SR_IMMEDIATE_GUI_NS::Separator();
        if (runtime.cppScriptsFound) {
            SR_IMMEDIATE_GUI_NS::WarningBox("C++ scripts are excluded from exported builds.");
        }
        const bool noTargets = !profile->windows && !profile->linux && !profile->emscripten && !profile->androidArm64 && !profile->androidX64;
        if (m_pProjectSettings->mainScene.empty()) {
            SR_IMMEDIATE_GUI_NS::WarningBox("Select a start scene.");
        }
        SR_IMMEDIATE_GUI_NS::BeginDisabled(m_pProjectSettings->mainScene.empty() || noTargets);
        if (SR_IMMEDIATE_GUI_NS::Button("Export selected platforms", SR_MATH_NS::FVector2(-1.f, 0.f))) {
            Build();
        }
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        SR_IMMEDIATE_GUI_NS::EndDisabled();
    }
}
