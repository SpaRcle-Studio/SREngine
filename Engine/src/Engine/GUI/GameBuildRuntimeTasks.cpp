#include <Engine/GUI/GameBuildRuntimeState.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/IVFSBackend.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>

namespace SR_CORE_GUI_NS {
    bool GameBuildRuntime::Submit(SR_HTYPES_NS::Function<void()> job) {
        return m_state->Task(std::move(job));
    }

    bool GameBuildRuntime::IsCancelled() const {
        return m_state->cancel;
    }

    void GameBuildRuntime::Report(SR_UTILS_NS::String message, bool error) {
        m_state->Message(std::move(message), error);
    }

    void GameBuildRuntime::ReportProgress(float_t progress) {
        std::lock_guard lock(m_state->mutex);
        m_state->status.progress = progress;
    }

    void GameBuildRuntime::ReportDownload(uint64_t downloaded, uint64_t total) {
        std::lock_guard lock(m_state->mutex);
        m_state->status.downloadedBytes = downloaded;
        m_state->status.totalBytes = total;
        m_state->status.progress = total > 0 ? static_cast<float_t>(downloaded) / total : -1.f;
    }

    SR_UTILS_NS::Path GameBuildRuntime::ResolveArtifact(SR_UTILS_NS::Path artifact, SR_UTILS_NS::Path resources) {
        auto&& vfs = SR_UTILS_NS::VFS::Instance();
        if (!artifact.IsAbs() && !resources.empty()) {
            if (!vfs.ResolvePath(resources, SR_UTILS_NS::FileMode::Write)) {
                return {};
            }
            artifact = resources.GetPrevious().Concat(artifact);
        }
        if (artifact.IsAbs()) {
            const auto directory = artifact.GetPrevious();
            if (!m_state->artifactBackend || m_state->artifactDirectory != directory) {
                SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> backend = new SR_UTILS_NS::ReadOnlyDirectoryVFSBackend(directory.ToStringView());
                vfs.Mount(directory.ToStringView(), backend.Get(), 0);
                backend.SetDeleter([](SR_UTILS_NS::IVFSBackend* value) {
                    SR_UTILS_NS::VFS::Instance().Unmount(value);
                    delete value;
                });
                m_state->artifactBackend = std::move(backend);
                m_state->artifactDirectory = directory;
            }
        }
        return artifact;
    }

    void GameBuildRuntime::RefreshTools(SR_UTILS_NS::Path resources, SR_UTILS_NS::String image) {
        m_state->Task([this, resources, image = std::move(image)]() {
            const auto selected = image.empty() ? m_state->android.GetSelectedImage() : image;
            const bool ready = m_state->android.HasTools();
            const bool emulator = m_state->android.HasEmulator(selected);
            bool cppScripts = false;
            if (!resources.empty()) {
                SR_UTILS_NS::VFS::Instance().Enumerate(resources.ToStringView(), [&cppScripts](const SR_UTILS_NS::VFSEntry& entry) {
                    if (entry.extension == "cpp" || entry.extension == "h" || entry.extension == "hpp") {
                        cppScripts = true;
                    }
                }, true);
            }
            {
                std::lock_guard lock(m_state->mutex);
                m_state->status.toolsReady = ready;
                m_state->status.emulatorReady = emulator;
                m_state->status.cppScriptsFound = cppScripts;
            }
            m_state->Message("Ready.");
        });
    }

    void GameBuildRuntime::ClearEngineCache(SR_UTILS_NS::Path path) {
        m_state->Task([this, path]() {
            m_state->Message("Clearing downloaded engine artifacts...");
            SR_UTILS_NS::VFS::Instance().Delete(path.ToStringView());
            m_state->Message("Engine download cache cleared.");
        });
    }
}
