//
// Created by OpenAI Codex on 12.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_RUNTIME_H
#define SR_ENGINE_GAME_BUILD_RUNTIME_H

#include <Engine/macros.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/RawPointerHolder.h>
#include <Utils/Platform/AndroidSDK.h>

namespace SR_CORE_GUI_NS {
    class GameBuildRuntime : public SR_UTILS_NS::NonCopyable {
    public:
        using Device = SR_PLATFORM_NS::AndroidSDK::Device;

        struct Status {
            SR_UTILS_NS::String message;
            SR_UTILS_NS::String log;
            SR_UTILS_NS::String webUrl;
            SR_UTILS_NS::String logcat;
            SR_UTILS_NS::String logcatMessage;
            SR_UTILS_NS::String androidPackage;
            bool logcatError = false;
            bool logcatRefreshing = false;
            SR_UTILS_NS::Vector<Device> devices;
            SR_UTILS_NS::Vector<SR_PLATFORM_NS::AndroidSDK::SystemImage> systemImages;
            SR_UTILS_NS::String selectedSystemImage;
            float_t progress = -1.f;
            uint64_t downloadedBytes = 0;
            uint64_t totalBytes = 0;
            bool toolsReady = false;
            bool emulatorReady = false;
            bool cppScriptsFound = false;
            bool error = false;
            bool busy = false;
            bool desktopRunning = false;
            bool emulatorRunning = false;
        };

        GameBuildRuntime();
        ~GameBuildRuntime() override;

        Status GetStatus() const;
        bool Submit(SR_HTYPES_NS::Function<void()> job);
        bool IsCancelled() const;
        void Report(SR_UTILS_NS::String message, bool error = false);
        void ReportProgress(float_t progress);
        void ReportDownload(uint64_t downloaded, uint64_t total);
        void RefreshTools(SR_UTILS_NS::Path resources = {}, SR_UTILS_NS::String image = {});
        void ClearEngineCache(SR_UTILS_NS::Path path);
        static SR_UTILS_NS::Path GetToolsPath();
        static SR_UTILS_NS::Path GetJavaPath(SR_UTILS_NS::StringView tool);
        static bool HasAndroidTools();
        static bool HasEmulator(SR_UTILS_NS::StringView image = {});
        static bool SignAndroid(const SR_UTILS_NS::Path& apk, const SR_UTILS_NS::Path& keyStore, SR_UTILS_NS::String& error);
        static bool DownloadArtifact(SR_UTILS_NS::StringView url, const SR_UTILS_NS::Path& destination);

        void RunDesktop(const SR_UTILS_NS::Path& artifact, bool portable, SR_UTILS_NS::Path resources = {});
        void RunWeb(const SR_UTILS_NS::Path& artifact, SR_UTILS_NS::Path resources = {});
        void InstallAndroid(bool emulator, bool acceptedLicense, SR_UTILS_NS::String image = {});
        void RefreshSystemImages();
        void RefreshDevices();
        void RefreshLogcat(SR_UTILS_NS::String serial, SR_UTILS_NS::String package, SR_UTILS_NS::String priority, SR_UTILS_NS::String buffer);
        void ClearLogcat(SR_UTILS_NS::String serial);
        void OpenLogcat();
        void StartEmulator(SR_UTILS_NS::String image = {});
        void RunAndroid(SR_UTILS_NS::String serial, SR_UTILS_NS::Path arm64Apk, SR_UTILS_NS::Path x64Apk, SR_UTILS_NS::Path resources = {});
        void Stop();
        void OpenToolsFolder();
        void OpenLog();
        void OpenWeb();
        void OpenAndroidTerms();

    private:
        struct State;
        SR_UTILS_NS::Path ResolveArtifact(SR_UTILS_NS::Path artifact, SR_UTILS_NS::Path resources);
        SR_UTILS_NS::RawPointerHolder<State> m_state;
    };
}

#endif
