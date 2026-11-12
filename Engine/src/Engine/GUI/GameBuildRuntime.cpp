//
// Created by OpenAI Codex on 12.11.2026.
//

#include <Engine/GUI/GameBuildRuntimeState.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Network/Download.h>

namespace SR_CORE_GUI_NS {
    GameBuildRuntime::State::State()
        : android(GameBuildRuntime::GetToolsPath())
    {
        android.isCancelled = [this]() {
            return cancel.load();
        };
        android.onMessage = [this](SR_UTILS_NS::String text, bool error) {
            Message(std::move(text), error);
        };
        android.onCommandOutput = [this](SR_UTILS_NS::String text) {
            std::lock_guard lock(mutex);
            status.log = std::move(text);
        };
        android.onProgress = [this](float_t progress) {
            std::lock_guard lock(mutex);
            status.progress = progress;
        };
        android.onDownloadProgress = [this](uint64_t completed, uint64_t total) {
            std::lock_guard lock(mutex);
            status.downloadedBytes = completed;
            status.totalBytes = total;
            status.progress = total > 0 ? static_cast<float_t>(completed) / total : -1.f;
        };
    }

    GameBuildRuntime::State::~State() {
        cancel = true;
        {
            std::lock_guard lock(jobMutex);
            exiting = true;
        }
        workAvailable.notify_one();
        if (worker) {
            worker->Join();
            worker->Free();
        }
        StopPreviews();
    }

    void GameBuildRuntime::State::Message(SR_UTILS_NS::String text, bool error) {
        std::lock_guard lock(mutex);
        status.message = std::move(text);
        status.error = error;
        status.progress = -1.f;
        status.downloadedBytes = 0;
        status.totalBytes = 0;
    }

    bool GameBuildRuntime::State::Task(SR_HTYPES_NS::Function<void()> job, bool quiet) {
        if (!worker && SR_PLATFORM_NS::IsSupportThreads()) {
            SR_HTYPES_NS::Thread::Factory::Instance().Create(worker, [this]() {
                Work();
                return false;
            });
        }
        if (!worker) {
            Message("Background operations require a desktop editor.", true);
            return false;
        }
        if (busy.exchange(true)) {
            return false;
        }
        cancel = false;
        if (quiet) {
            std::lock_guard lock(mutex);
            status.logcatRefreshing = true;
        }
        if (!quiet) {
            std::lock_guard lock(mutex);
            status.error = false;
            status.log.clear();
            status.message = "Working...";
            status.progress = -1.f;
            status.downloadedBytes = 0;
            status.totalBytes = 0;
        }
        {
            std::lock_guard lock(jobMutex);
            pendingJob = std::move(job);
        }
        workAvailable.notify_one();
        return true;
    }

    void GameBuildRuntime::State::Work() {
        while (true) {
            SR_HTYPES_NS::Function<void()> job;
            {
                std::unique_lock lock(jobMutex);
                workAvailable.wait(lock, [this]() {
                    return exiting || pendingJob;
                });
                if (exiting) {
                    return;
                }
                job = std::move(pendingJob);
                pendingJob = nullptr;
            }
            try {
                job();
                job = nullptr;
                if (cancel) {
                    StopPreviews();
                    Message("Operation cancelled.");
                }
                const bool ready = android.HasTools();
                const auto selected = android.GetSelectedImage();
                const bool emulatorReady = android.HasEmulator(selected);
                {
                    std::lock_guard lock(mutex);
                    status.toolsReady = ready;
                    status.emulatorReady = emulatorReady;
                    status.selectedSystemImage = selected;
                }
            }
            catch (...) {
                job = nullptr;
                Message("Runtime operation failed. See the engine log.", true);
            }
            artifactBackend.Reset();
            artifactDirectory.clear();
            {
                std::lock_guard lock(mutex);
                status.logcatRefreshing = false;
                busy = false;
            }
        }
    }

    void GameBuildRuntime::State::StopPreviews() {
        desktop.Stop();
        emulator.Stop();
        web.Stop();
        std::lock_guard lock(mutex);
        status.webUrl.clear();
        status.desktopRunning = false;
        status.emulatorRunning = false;
    }

    GameBuildRuntime::GameBuildRuntime()
        : m_state(new State())
    { }

    GameBuildRuntime::~GameBuildRuntime() = default;

    SR_UTILS_NS::Path GameBuildRuntime::GetToolsPath() {
        return SR_PLATFORM_NS::GetApplicationUserDataDirectory().Concat("RuntimeTools");
    }

    SR_UTILS_NS::Path GameBuildRuntime::GetJavaPath(SR_UTILS_NS::StringView tool) {
        return SR_PLATFORM_NS::AndroidSDK(GetToolsPath()).GetJavaPath(tool);
    }

    bool GameBuildRuntime::HasAndroidTools() {
        return SR_PLATFORM_NS::AndroidSDK(GetToolsPath()).HasTools();
    }

    bool GameBuildRuntime::HasEmulator(SR_UTILS_NS::StringView image) {
        SR_PLATFORM_NS::AndroidSDK sdk(GetToolsPath());
        const SR_UTILS_NS::String selected = image.empty() ? sdk.GetSelectedImage() : SR_UTILS_NS::String(image);
        return sdk.HasEmulator(selected);
    }

    bool GameBuildRuntime::SignAndroid(const SR_UTILS_NS::Path& apk, const SR_UTILS_NS::Path& keyStore, SR_UTILS_NS::String& error) {
        SR_PLATFORM_NS::AndroidSDK sdk(GetToolsPath());
        sdk.onMessage = [&error](SR_UTILS_NS::String text, bool failed) {
            if (failed) {
                error = std::move(text);
            }
        };
        return sdk.Sign(apk, keyStore);
    }

    bool GameBuildRuntime::DownloadArtifact(SR_UTILS_NS::StringView url, const SR_UTILS_NS::Path& destination) {
        SR_NETWORK_NS::DownloadRequest request;
        request.url = url;
        request.destination = destination;
        return SR_NETWORK_NS::Download(request);
    }

    GameBuildRuntime::Status GameBuildRuntime::GetStatus() const {
        std::lock_guard lock(m_state->mutex);
        Status result = m_state->status;
        result.busy = m_state->busy;
        return result;
    }

    void GameBuildRuntime::Stop() {
        m_state->cancel = true;
        if (m_state->busy) {
            m_state->Message("Cancelling operation...");
            return;
        }
        m_state->Task([this]() {
            m_state->StopPreviews();
            m_state->Message("Local previews stopped.");
        });
    }

    void GameBuildRuntime::OpenToolsFolder() {
        m_state->Task([this]() {
            SR_UTILS_NS::VFS::Instance().CreateDirectories(GetToolsPath().ToStringView());
            if (!SR_PLATFORM_NS::OpenAssociated(GetToolsPath().ToStringView())) {
                m_state->Message("Cannot open tools folder.", true);
            }
        });
    }

    void GameBuildRuntime::OpenLog() {
        m_state->Task([this]() {
            if (!SR_PLATFORM_NS::OpenAssociated(m_state->android.GetLogPath().ToStringView())) {
                m_state->Message("Cannot open command log.", true);
            }
        });
    }

    void GameBuildRuntime::OpenAndroidTerms() {
        m_state->Task([this]() {
            if (!SR_PLATFORM_NS::OpenAssociated("https://developer.android.com/studio#terms-and-conditions")) {
                m_state->Message("Cannot open Android SDK terms.", true);
            }
        });
    }

    void GameBuildRuntime::OpenWeb() {
        const auto snapshot = GetStatus();
        if (snapshot.webUrl.empty()) {
            return;
        }
        m_state->Task([this, url = snapshot.webUrl]() {
            if (!SR_PLATFORM_NS::OpenAssociated(url)) {
                m_state->Message("Cannot open browser. Open the preview URL manually.", true);
            }
        });
    }
}
