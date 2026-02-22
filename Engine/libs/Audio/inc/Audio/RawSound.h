//
// Created by Monika on 06.07.2022.
//

#ifndef SR_ENGINE_RAWSOUND_H
#define SR_ENGINE_RAWSOUND_H

#include <Audio/macros.h>

#include <Utils/Resources/IResource.h>

namespace SR_AUDIO_NS {
    class IWaveDataProvider;

    class RawSound : public SR_UTILS_NS::IResource {
        SR_CLASS()
        using Super = SR_UTILS_NS::IResource;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<RawSound>;

    public:
        RawSound();
        ~RawSound() override;

    public:
        SR_NODISCARD uint64_t GetBufferSize() const;
        SR_NODISCARD const uint8_t* GetBufferData() const;
        SR_NODISCARD uint8_t GetChannels() const;
        SR_NODISCARD uint8_t GetBitsPerSample() const;
        SR_NODISCARD uint32_t GetSampleRate() const;
        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

    protected:
        bool Unload() override;
        bool Load() override;
        bool Reload() override;

    private:
        std::shared_ptr<IWaveDataProvider> m_dataProvider;

    };
}

#endif //SR_ENGINE_RAWSOUND_H
