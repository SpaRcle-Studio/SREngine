//
// Created by OpenAI Codex on 12.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_JOB_H
#define SR_ENGINE_GAME_BUILD_JOB_H

#include <Engine/Settings/ProjectSettings.h>
#include <Engine/Export/TextureExporter.h>
#include <Utils/Types/SortedVector.h>
#include <Utils/Types/Function.h>
#include <Utils/Resources/ResourceRef.h>

namespace SR_CORE_GUI_NS {
    class GameBuildJob : public SR_UTILS_NS::NonCopyable {
    public:
        explicit GameBuildJob(const SR_UTILS_NS::ResourceRef<ProjectSettings>& settings);
        ~GameBuildJob() override;
        bool Build();
        bool ReinstallArtifacts();

        SR_HTYPES_NS::Function<void(SR_UTILS_NS::String, bool)> onStatus;
        SR_HTYPES_NS::Function<void(float_t)> onProgress;
        SR_HTYPES_NS::Function<void(float_t, float_t, SR_UTILS_NS::String)> onBuildProgress;
        SR_HTYPES_NS::Function<void(uint64_t, uint64_t)> onDownload;
        SR_HTYPES_NS::Function<bool()> isCancelled;

    private:
        GameBuildProfile* GetActiveProfile() const;
        SR_UTILS_NS::String GetReleaseTag() const;
        SR_UTILS_NS::Path GetBuildCachePath() const;
        SR_UTILS_NS::Path GetOutputPath() const;
        bool CollectBuildResources(SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path>& paths) const;
        bool PreparePlatformResources(SR_UTILS_NS::StringView platform);
        bool ReadBuildResource(const SR_UTILS_NS::Path& path, SR_UTILS_NS::String& data) const;
        bool PackDesktopResources();
        bool ProcessTargets(bool downloadOnly);
        bool ExportPlatform(SR_UTILS_NS::StringView platform, SR_UTILS_NS::StringView asset, bool downloadOnly);
        bool RepackDesktop(const SR_UTILS_NS::Path& path);
        bool RepackAndroid(const SR_UTILS_NS::Path& path);
        bool RepackEmscripten(const SR_UTILS_NS::Path& path);
        void SetStatus(SR_UTILS_NS::String status, bool error = false);
        void BeginStage(SR_UTILS_NS::String label, float_t start, float_t span);
        void SetProgress(float_t progress);
        void SetProgress(float_t progress, float_t detailProgress);
        static bool ReadBinary(SR_UTILS_NS::StringView data, SR_UTILS_NS::SizeType& position, void* value, SR_UTILS_NS::SizeType size);

        template<typename T> static void AppendBinary(SR_UTILS_NS::String& data, const T& value) {
            data.append(reinterpret_cast<const char*>(&value), sizeof(T));
        }

        static constexpr SR_UTILS_NS::StringView EngineRepository = "https://github.com/SpaRcle-Studio/SREngine";
        static constexpr SR_UTILS_NS::StringView PackedDataMagic = "MAGIC_ENGINE_MODULE_DATA";
        static constexpr SR_UTILS_NS::StringView ResourceDataMagic = "SR_ENGINE_VFS_RESOURCES_V1";
        SR_UTILS_NS::ResourceRef<ProjectSettings> m_pProjectSettings;
        SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path> m_resourcePaths;
        SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path> m_sourceResourcePaths;
        SR_UTILS_NS::Vector<TextureBuildArtifact> m_resourceOverrides;
        TextureExporter m_textureExporter;
        SR_UTILS_NS::String m_desktopPackedBinary;
        SR_UTILS_NS::Path m_outputRoot;
        SR_UTILS_NS::String m_stageLabel;
        float_t m_stageStart = 0.f;
        float_t m_stageSpan = 1.f;
        float_t m_lastProgress = 0.f;
        uint32_t m_targetIndex = 0;
        uint32_t m_targetCount = 1;
    };
}
#endif
