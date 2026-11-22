//
// Created by OpenAI Codex on 22.11.2026.
//

#ifndef SR_ENGINE_EXPORT_TEXTURE_EXPORTER_H
#define SR_ENGINE_EXPORT_TEXTURE_EXPORTER_H

#include <Graphics/Utils/ImageMetaInfo.h>

#include <Utils/Types/Function.h>

namespace SR_CORE_NS {
    struct TextureBuildArtifact {
        SR_UTILS_NS::Path resourcePath;
        SR_UTILS_NS::Path buildPath;
    };

    class TextureExporter : public SR_UTILS_NS::NonCopyable {
    public:
        TextureExporter();
        ~TextureExporter() override;

        bool Prepare(const SR_UTILS_NS::Path& source, SR_GRAPH_NS::ImageMetaInfo& metadata,
            SR_GRAPH_NS::TextureExportProfile profile, const SR_UTILS_NS::Path& buildRoot,
            SR_UTILS_NS::Vector<TextureBuildArtifact>& artifacts);

        SR_HTYPES_NS::Function<bool()> isCancelled;
        SR_HTYPES_NS::Function<void(SR_UTILS_NS::String)> onStatus;
        SR_HTYPES_NS::Function<void(float_t)> onProgress;
        bool useGpu = true;
        bool useAstc = true;
        bool useEtc2 = true;
        uint32_t cpuUsagePercent = 80;
        bool requireBlockAlignedTextures = false;

    private:
        struct State;
        State* m_pState = nullptr;
    };
}

#endif //SR_ENGINE_EXPORT_TEXTURE_EXPORTER_H
