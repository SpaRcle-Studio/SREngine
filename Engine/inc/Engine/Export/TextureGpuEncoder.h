//
// Created by OpenAI Codex on 22.11.2026.
//

#ifndef SR_ENGINE_EXPORT_TEXTURE_GPU_ENCODER_H
#define SR_ENGINE_EXPORT_TEXTURE_GPU_ENCODER_H

#include <Graphics/Loaders/TextureContainer.h>

#include <Utils/Types/Function.h>

namespace SR_CORE_NS {
    class TextureGpuEncoder : public SR_UTILS_NS::NonCopyable {
    public:
        TextureGpuEncoder();
        ~TextureGpuEncoder() override;

        bool Encode(uint32_t width, uint32_t height, const SR_UTILS_NS::Vector<float_t>& rgba,
            SR_GRAPH_NS::TextureCompression compression, float_t quality, float_t cutoff, SR_UTILS_NS::Vector<uint8_t>& output,
            const SR_HTYPES_NS::Function<bool()>& cancelled, const SR_HTYPES_NS::Function<void(float_t)>& progress);

        SR_UTILS_NS::String GetIdentity() const;

    private:
        struct State;
        State* m_pState = nullptr;
    };
}

#endif //SR_ENGINE_EXPORT_TEXTURE_GPU_ENCODER_H
