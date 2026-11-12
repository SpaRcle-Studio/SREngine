//
// Created by OpenAI Codex on 12.11.2026.
//

#include <Engine/GUI/GameBuildExporter.h>
#include <Engine/GUI/GameBuildUI.h>
#include <Utils/Platform/Process.h>
#include <Utils/Resources/ResourceManager.h>

namespace SR_CORE_GUI_NS {
    void GameBuildExporter::DrawLaunch(const GameBuildRuntime::Status& runtime) {
        if (!m_devicesScanned && runtime.toolsReady && !runtime.busy) {
            m_runtime.RefreshDevices();
            m_devicesScanned = true;
        }
        const auto profile = GetActiveProfile();
        if (!profile) {
            SR_IMMEDIATE_GUI_NS::TextWrapped("No active build profile.");
            return;
        }
        const auto resources = CoreResLoader::GetResPath();
        if (m_androidSystemImage.empty()) {
            m_androidSystemImage = runtime.selectedSystemImage;
        }
        SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy);
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Desktop", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            const auto platform = SR_PLATFORM_NS::GetDesktopPlatformName();
            if (!platform.empty()) {
                BuildField("Platform", [&]() {
                    SR_IMMEDIATE_GUI_NS::Text("%s", platform.c_str());
                });
                BuildField("Game", [&]() {
                    const bool portable = profile->desktopPackageMode == DesktopBuildPackageMode::PortableZip;
                    const auto suffix = portable ? SR_UTILS_NS::String(".zip") : SR_PLATFORM_NS::GetExecutableName("");
                    if (SR_IMMEDIATE_GUI_NS::Button("Run desktop build", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                        m_runtime.RunDesktop(GetArtifactPath(platform, suffix), portable, resources);
                    }
                });
            }
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Browser", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            BuildField("Web preview", [&]() {
                SR_IMMEDIATE_GUI_NS::BeginDisabled(!profile->enableWebPreview);
                if (SR_IMMEDIATE_GUI_NS::Button("Run browser build")) {
                    m_runtime.RunWeb(GetArtifactPath("Emscripten", ".zip"), resources);
                }
                SR_IMMEDIATE_GUI_NS::EndDisabled();
                if (!runtime.webUrl.empty()) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                    if (SR_IMMEDIATE_GUI_NS::Button("Open")) {
                        m_runtime.OpenWeb();
                    }
                }
            });
            if (!profile->enableWebPreview) {
                SR_IMMEDIATE_GUI_NS::TextWrapped("Enable web preview in Export > Advanced.");
            }
            if (!runtime.webUrl.empty()) {
                BuildField("Address", [&]() {
                    SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.webUrl.c_str());
                });
            }
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Android", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            if (!runtime.toolsReady) {
                SR_IMMEDIATE_GUI_NS::TextWrapped("Install Android support in the Tools tab.");
            }
            SR_IMMEDIATE_GUI_NS::BeginDisabled(!runtime.toolsReady);
            BuildField("Devices", [&]() {
                if (SR_IMMEDIATE_GUI_NS::Button("Refresh devices")) {
                    m_runtime.RefreshDevices();
                }
            });
            BuildField("Device", [&]() {
                const char* selected = m_androidSerial.empty() ? "Select a device" : m_androidSerial.c_str();
                if (SR_IMMEDIATE_GUI_NS::BeginCombo("##device", selected)) {
                    if (runtime.emulatorReady) {
                        const auto label = "Managed emulator: {}##managed"_format(runtime.selectedSystemImage);
                        if (SR_IMMEDIATE_GUI_NS::Selectable(label.c_str(), m_androidSerial == "emulator-5580")) {
                            m_androidSerial = "emulator-5580";
                        }
                    }
                    for (const auto& device : runtime.devices) {
                        SR_IMMEDIATE_GUI_NS::BeginDisabled(device.state != "device");
                        if (SR_IMMEDIATE_GUI_NS::Selectable(device.description.c_str(), device.serial == m_androidSerial)) {
                            m_androidSerial = device.serial;
                        }
                        SR_IMMEDIATE_GUI_NS::EndDisabled();
                    }
                    SR_IMMEDIATE_GUI_NS::EndCombo();
                }
            });
            if (m_androidSerial == "emulator-5580") {
                BuildField("Emulator image", [&]() {
                    SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.selectedSystemImage.c_str());
                });
                BuildField("Emulator", [&]() {
                    SR_IMMEDIATE_GUI_NS::BeginDisabled(!runtime.emulatorReady || runtime.emulatorRunning);
                    if (SR_IMMEDIATE_GUI_NS::Button("Start managed emulator (emulator-5580)")) {
                        m_runtime.StartEmulator(runtime.selectedSystemImage);
                    }
                    SR_IMMEDIATE_GUI_NS::EndDisabled();
                });
            }
            bool authorized = false;
            for (const auto& device : runtime.devices) {
                if (device.serial == m_androidSerial && device.state == "device") {
                    authorized = true;
                }
            }
            BuildField("Application", [&]() {
                SR_IMMEDIATE_GUI_NS::BeginDisabled(!authorized);
                if (SR_IMMEDIATE_GUI_NS::Button("Install and run", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    const auto arm64 = GetArtifactPath("Android", "-arm64-v8a.apk");
                    const auto x64 = GetArtifactPath("Android", "-x86_64.apk");
                    if (arm64.empty() || x64.empty()) {
                        m_runtime.Report("Cannot resolve APK paths. Check the project name and output directory in the active profile.", true);
                    }
                    else {
                        m_runtime.RunAndroid(m_androidSerial, arm64, x64, resources);
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            });
            SR_IMMEDIATE_GUI_NS::EndDisabled();
        }
        SR_IMMEDIATE_GUI_NS::Separator();
        if (SR_IMMEDIATE_GUI_NS::Button("Stop local previews", SR_MATH_NS::FVector2(-1.f, 0.f))) {
            m_runtime.Stop();
        }
        SR_IMMEDIATE_GUI_NS::TextWrapped("Run uses the last exported build of the active configuration.");
        SR_IMMEDIATE_GUI_NS::EndDisabled();
    }

    void GameBuildExporter::DrawTools(const GameBuildRuntime::Status& runtime) {
        if (!m_imagesScanned && runtime.toolsReady && !runtime.busy) {
            m_runtime.RefreshSystemImages();
            m_imagesScanned = true;
        }
        if (m_androidSystemImage.empty()) {
            m_androidSystemImage = runtime.selectedSystemImage;
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Android support", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            BuildField("SDK tools", [&]() {
                SR_IMMEDIATE_GUI_NS::Text("%s", runtime.toolsReady ? "Installed" : "Not installed");
            });
            BuildField("License", [&]() {
                SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy);
                if (SR_IMMEDIATE_GUI_NS::Button("Read terms")) {
                    m_runtime.OpenAndroidTerms();
                }
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            });
            BuildField("Agreement", [&]() {
                SR_IMMEDIATE_GUI_NS::Checkbox("I accept the SDK terms", &m_androidLicenseAccepted);
            });
            BuildField("Installation", [&]() {
                SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy || !m_androidLicenseAccepted);
                if (SR_IMMEDIATE_GUI_NS::Button("Install / repair tools", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    m_runtime.InstallAndroid(false, m_androidLicenseAccepted);
                }
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            });
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Android virtual device", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::DefaultOpen)) {
            BuildField("System image", [&]() {
                if (SR_IMMEDIATE_GUI_NS::BeginCombo("##image", m_androidSystemImage.empty() ? "Choose an image" : m_androidSystemImage.c_str())) {
                    for (const auto& image : runtime.systemImages) {
                        const auto label = "{}{} ({})"_format(image.installed ? "[Installed] " : "", image.description, image.package);
                        if (image.installed) {
                            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(0.45f, 0.85f, 0.55f, 1.f));
                        }
                        if (SR_IMMEDIATE_GUI_NS::Selectable(label.c_str(), image.package == m_androidSystemImage)) {
                            m_androidSystemImage = image.package;
                        }
                        if (image.installed) {
                            SR_IMMEDIATE_GUI_NS::PopStyleColor();
                        }
                    }
                    SR_IMMEDIATE_GUI_NS::EndCombo();
                }
            });
            SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy || !runtime.toolsReady);
            BuildField("Catalogue", [&]() {
                if (SR_IMMEDIATE_GUI_NS::Button("Refresh system images", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    m_runtime.RefreshSystemImages();
                }
            });
            BuildField("Virtual device", [&]() {
                SR_IMMEDIATE_GUI_NS::BeginDisabled(!m_androidLicenseAccepted || m_androidSystemImage.empty());
                if (SR_IMMEDIATE_GUI_NS::Button("Install / repair selected emulator", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    m_runtime.InstallAndroid(true, m_androidLicenseAccepted, m_androidSystemImage);
                }
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            });
            SR_IMMEDIATE_GUI_NS::EndDisabled();
            SR_IMMEDIATE_GUI_NS::TextWrapped("Compatible x86_64 images from the Android SDK. Configure WHPX / KVM on the host.");
        }
        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Storage and diagnostics")) {
            BuildField("Tools directory", [&]() {
                SR_IMMEDIATE_GUI_NS::TextWrapped("%s", GameBuildRuntime::GetToolsPath().c_str());
            });
            SR_IMMEDIATE_GUI_NS::BeginDisabled(runtime.busy);
            BuildField("Diagnostics", [&]() {
                if (SR_IMMEDIATE_GUI_NS::Button("Open folder")) {
                    m_runtime.OpenToolsFolder();
                }
                SR_IMMEDIATE_GUI_NS::SameLine();
                if (SR_IMMEDIATE_GUI_NS::Button("Open log")) {
                    m_runtime.OpenLog();
                }
            });
            BuildField("Engine cache", [&]() {
                if (SR_IMMEDIATE_GUI_NS::Button("Clear downloaded artifacts", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    m_runtime.ClearEngineCache(GetBuildCachePath());
                }
            });
            BuildField("Tools state", [&]() {
                if (SR_IMMEDIATE_GUI_NS::Button("Refresh", SR_MATH_NS::FVector2(-1.f, 0.f))) {
                    m_runtime.RefreshTools();
                }
            });
            SR_IMMEDIATE_GUI_NS::EndDisabled();
        }
    }
}
