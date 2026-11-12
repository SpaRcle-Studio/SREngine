#include <Engine/GUI/GameBuildRuntimeState.h>

namespace SR_CORE_GUI_NS {
    void GameBuildRuntime::State::UpdateDevices() {
        SR_UTILS_NS::Vector<Device> devices;
        if (android.GetDevices(devices)) {
            std::lock_guard lock(mutex);
            status.devices = std::move(devices);
        }
    }

    void GameBuildRuntime::State::UpdateSystemImages() {
        SR_UTILS_NS::Vector<SR_PLATFORM_NS::AndroidSDK::SystemImage> images;
        if (android.ListSystemImages(images)) {
            std::lock_guard lock(mutex);
            status.systemImages = std::move(images);
        }
    }

    void GameBuildRuntime::InstallAndroid(bool emulator, bool acceptedLicense, SR_UTILS_NS::String image) {
        m_state->Task([this, emulator, acceptedLicense, image = std::move(image)]() {
            if (!m_state->android.Install(emulator, acceptedLicense, image)) {
                return;
            }
            if (!emulator) {
                m_state->UpdateSystemImages();
            }
            const auto selected = m_state->android.GetSelectedImage();
            SR_UTILS_NS::Vector<SR_PLATFORM_NS::AndroidSDK::SystemImage> images;
            {
                std::lock_guard lock(m_state->mutex);
                images = m_state->status.systemImages;
            }
            for (auto& systemImage : images) {
                systemImage.installed = m_state->android.IsSystemImageInstalled(systemImage.package);
            }
            std::lock_guard lock(m_state->mutex);
            m_state->status.selectedSystemImage = selected;
            m_state->status.systemImages = std::move(images);
        });
    }

    void GameBuildRuntime::RefreshSystemImages() {
        m_state->Task([this]() {
            m_state->UpdateSystemImages();
        });
    }

    void GameBuildRuntime::RefreshDevices() {
        m_state->Task([this]() {
            m_state->UpdateDevices();
        });
    }

    void GameBuildRuntime::StartEmulator(SR_UTILS_NS::String image) {
        m_state->Task([this, image = std::move(image)]() {
            const SR_UTILS_NS::String selected = image.empty() ? m_state->android.GetSelectedImage() : image;
            if (m_state->android.StartEmulator(m_state->emulator, selected)) {
                m_state->UpdateDevices();
            }
            const bool running = m_state->emulator.IsRunning();
            std::lock_guard lock(m_state->mutex);
            m_state->status.emulatorRunning = running;
        });
    }

    void GameBuildRuntime::RunAndroid(SR_UTILS_NS::String serial, SR_UTILS_NS::Path arm64Apk, SR_UTILS_NS::Path x64Apk, SR_UTILS_NS::Path resources) {
        m_state->Task([this, serial = std::move(serial), arm64Apk, x64Apk, resources]() {
            m_state->android.InstallAndRun(serial, ResolveArtifact(arm64Apk, resources), ResolveArtifact(x64Apk, resources));
            std::lock_guard lock(m_state->mutex);
            m_state->status.androidPackage = m_state->android.GetLastPackage();
        });
    }
}
