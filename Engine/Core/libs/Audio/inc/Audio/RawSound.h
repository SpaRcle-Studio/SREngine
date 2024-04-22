//
// Created by Monika on 06.07.2022.
//

#ifndef SR_ENGINE_RAWSOUND_H
#define SR_ENGINE_RAWSOUND_H

#include <Utils/Resources/IResource.h>
#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    class SR_DLL_EXPORT RawSound : public SR_UTILS_NS::IResource {
    private:
        RawSound();
        ~RawSound() override;

    public:
        static RawSound* Load(const SR_UTILS_NS::Path& rawPath);

    public:
        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };
        SR_NODISCARD uint64_t GetBufferSize() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
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
        IWaveDataProvider::Ptr m_dataProvider;

    };
}

#endif //SR_ENGINE_RAWSOUND_H
