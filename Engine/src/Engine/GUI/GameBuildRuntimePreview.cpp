#include <Engine/GUI/GameBuildRuntimeState.h>
#include <Utils/FileSystem/ArchiveExtract.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/IVFSBackend.h>
#include <Utils/Platform/Platform.h>

namespace SR_CORE_GUI_NS {
    void GameBuildRuntime::RunDesktop(const SR_UTILS_NS::Path& path, bool portable, SR_UTILS_NS::Path resources) {
        m_state->Task([this, path, portable, resources]() {
            const auto artifact = ResolveArtifact(path, resources);
            if (!artifact.IsFile()) {
                m_state->Message("Desktop build not found: {}. Export this target first."_format(artifact), true);
                return;
            }
            SR_UTILS_NS::Path executable = artifact;
            if (portable) {
                const auto directory = GetToolsPath().Concat("RunCache/{:016x}"_format(artifact.GetFileHash()));
                if (!SR_UTILS_NS::ExtractZip(artifact, directory)) {
                    m_state->Message("Failed to unpack desktop build.", true);
                    return;
                }
                executable = directory.Concat(SR_PLATFORM_NS::GetExecutableName(artifact.GetBaseNameView()));
            }
            SR_PLATFORM_NS::CopyPermissions(SR_PLATFORM_NS::GetApplicationPath(), executable);
            SR_PLATFORM_NS::ProcessInfo info;
            info.executable = executable;
            info.workingDirectory = executable.GetPrevious();
            info.output = GetToolsPath().Concat("desktop.log");
            info.ownProcessTree = true;
            if (!m_state->desktop.Start(std::move(info))) {
                m_state->Message("Cannot start desktop build.", true);
                return;
            }
            for (uint32_t i = 0; i < 5 && m_state->desktop.IsRunning(); ++i) {
                SR_HTYPES_NS::Thread::Sleep(100);
            }
            const bool running = m_state->desktop.IsRunning();
            {
                std::lock_guard lock(m_state->mutex);
                m_state->status.desktopRunning = running;
            }
            m_state->Message(running ? "Desktop game started. See RuntimeTools/desktop.log."
                : "Desktop game exited. See RuntimeTools/desktop.log.", !running && m_state->desktop.GetExitCode() != 0);
        });
    }

    void GameBuildRuntime::RunWeb(const SR_UTILS_NS::Path& path, SR_UTILS_NS::Path resources) {
        m_state->Task([this, path, resources]() {
            const auto artifact = ResolveArtifact(path, resources);
            if (!artifact.IsFile()) {
                m_state->Message("Browser build not found: {}. Export this target first."_format(artifact), true);
                return;
            }
            m_state->web.Stop();
            const auto directory = GetToolsPath().Concat("RunCache/web-{:016x}"_format(artifact.GetFileHash()));
            if (!SR_UTILS_NS::ExtractZip(artifact, directory)) {
                m_state->Message("Failed to unpack browser build.", true);
                return;
            }
            SR_UTILS_NS::Path page;
            SR_UTILS_NS::VFS::Instance().Enumerate(directory.ToStringView(), [&page](const SR_UTILS_NS::VFSEntry& entry) {
                if (entry.type != SR_UTILS_NS::FSItemType::File) {
                    return;
                }
                if (entry.name == "index.html" || (page.empty() && entry.name == "SREngine.html")) {
                    page = SR_UTILS_NS::Path(entry.fullPath);
                }
            }, true);
            if (page.empty()) {
                m_state->Message("Browser archive has no index.html or SREngine.html: {}"_format(artifact), true);
                return;
            }
            if (!m_state->web.Start(page.GetPrevious(), SR_UTILS_NS::String(page.GetBaseNameAndExtView()))) {
                m_state->Message("Cannot start the local browser preview server.", true);
                return;
            }
            const auto url = m_state->web.GetURL();
            {
                std::lock_guard lock(m_state->mutex);
                m_state->status.webUrl = url;
            }
            m_state->Message("Browser preview is running at {}"_format(url));
            if (!SR_PLATFORM_NS::OpenAssociated(url)) {
                m_state->Message("Preview server is ready. Open {} manually."_format(url));
            }
        });
    }
}
