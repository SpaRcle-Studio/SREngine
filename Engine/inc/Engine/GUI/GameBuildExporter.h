//
// Created by OpenAI Codex on 09.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_EXPORTER_H
#define SR_ENGINE_GAME_BUILD_EXPORTER_H

#include <Engine/Settings/ProjectSettings.h>

#include <Graphics/GUI/Widget.h>

#include <Utils/Resources/ResourceRef.h>
#include <Utils/Types/SortedVector.h>

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
        bool ExportPlatform(SR_UTILS_NS::StringView platformName, SR_UTILS_NS::StringView assetName);
        bool CollectBuildResources(SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path>& paths) const;
        bool RepackDesktop(const SR_UTILS_NS::Path& artifactPath);
        bool RepackAndroid(const SR_UTILS_NS::Path& artifactPath);
        bool RepackEmscripten(const SR_UTILS_NS::Path& artifactPath);
        SR_NODISCARD SR_UTILS_NS::Path GetBuildCachePath() const;
        SR_NODISCARD SR_UTILS_NS::String GetReleaseTag() const;
        SR_NODISCARD GameBuildProfile* GetActiveProfile() const;
        void SetStatus(SR_UTILS_NS::String status, bool error = false);

    private:
        SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path> m_resourcePaths;
        mutable SR_UTILS_NS::ResourceRef<ProjectSettings> m_pProjectSettings;
        SR_UTILS_NS::String m_status;
        SR_UTILS_NS::String m_desktopPackedBinary;
        bool m_statusError = false;
        bool m_cppScriptsFound = false;
        SR_UTILS_NS::Path m_outputRoot;
    };
}

#endif //SR_ENGINE_GAME_BUILD_EXPORTER_H
