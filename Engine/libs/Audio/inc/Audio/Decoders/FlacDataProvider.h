//
// Created by Monika on 09.12.2025.
//

#ifndef SR_ENGINE_AUDIO_FLAC_DATA_PROVIDER_H
#define SR_ENGINE_AUDIO_FLAC_DATA_PROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

#include <Utils/Types/RawPointerHolder.h>

#ifdef SR_AUDIO_USE_FLAC

namespace SR_AUDIO_NS {
    class FLACDecoderCallbacks;

    class FlacDataProvider : public IWaveDataProvider {
        friend FLACDecoderCallbacks;
        using Super = IWaveDataProvider;
    public:
        explicit FlacDataProvider(const RawSoundDataPtr& pData);

        ~FlacDataProvider() override;

        SR_NODISCARD const WaveDataFormat& GetWaveDataFormat() const override { return m_format; }
        SR_NODISCARD const uint8_t* GetWaveData() const override;
        SR_NODISCARD size_t GetWaveDataSize() const override;
        SR_NODISCARD bool IsStreaming() const override { return true; }
        void Seek(float_t seconds) override;
        size_t StreamWaveData(size_t size) override;

    private:
        RawSoundDataPtr m_data;
        WaveDataFormat m_format;

        void* m_decoder = nullptr;

        std::vector<uint8_t> m_decodingBuffer;
        size_t m_bufferUsed = 0;

        int64_t m_memoryPosition = 0;
    };
}

#endif

#endif // SR_ENGINE_AUDIO_FLAC_DATA_PROVIDER_H
