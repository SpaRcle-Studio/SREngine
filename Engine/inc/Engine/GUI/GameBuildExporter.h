//
// Created by OpenAI Codex on 09.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_EXPORTER_H
#define SR_ENGINE_GAME_BUILD_EXPORTER_H

#include <Engine/Settings/ProjectSettings.h>
#include <Engine/GUI/GameBuildRuntime.h>

#include <Graphics/GUI/Widget.h>

#include <Utils/Types/SortedVector.h>
#include <chrono>

namespace SR_CORE_GUI_NS {
    class GameBuildExporter : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        GameBuildExporter();
        ~GameBuildExporter() override;

    protected:
        void Draw() override;
        void OnOpen() override;

    private:
        bool LoadProjectSettings();
        bool Build();
        SR_NODISCARD SR_UTILS_NS::Path GetBuildCachePath() const;
        SR_NODISCARD SR_UTILS_NS::String GetReleaseTag() const;
        SR_NODISCARD GameBuildProfile* GetActiveProfile() const;
        SR_UTILS_NS::Path GetOutputPath() const;
        SR_UTILS_NS::Path GetArtifactPath(SR_UTILS_NS::StringView platform, SR_UTILS_NS::StringView suffix) const;
        void DrawExport(const GameBuildRuntime::Status& runtime);
        void DrawLaunch(const GameBuildRuntime::Status& runtime);
        void DrawTools(const GameBuildRuntime::Status& runtime);
        void DrawLogcat(const GameBuildRuntime::Status& runtime);

    private:
        SR_UTILS_NS::RawPointerHolder<ProjectSettings> m_pProjectSettings;
        std::atomic<bool> m_projectReady = false;
        bool m_toolsScanned = false;
        bool m_devicesScanned = false;
        bool m_imagesScanned = false;
        bool m_logcatLive = true;
        bool m_logcatFollow = true;
        bool m_logcatAppOnly = true;
        bool m_logcatPackageInitialized = false;
        bool m_logcatRefreshRequested = false;
        bool m_logcatClearRequested = false;
        bool m_logcatOpenRequested = false;
        SR_UTILS_NS::String m_logcatVisibleLog;
        SR_UTILS_NS::String m_logcatPackage;
        SR_UTILS_NS::String m_logcatInclude;
        SR_UTILS_NS::String m_logcatExclude;
        SR_UTILS_NS::String m_logcatPriority = "V";
        SR_UTILS_NS::String m_logcatBuffer = "main + system + crash";
        std::chrono::steady_clock::time_point m_logcatRefresh;
        GameBuildRuntime m_runtime;
        SR_UTILS_NS::String m_androidSerial;
        SR_UTILS_NS::String m_androidSystemImage;
        bool m_androidLicenseAccepted = false;
    };
}

#endif //SR_ENGINE_GAME_BUILD_EXPORTER_H
