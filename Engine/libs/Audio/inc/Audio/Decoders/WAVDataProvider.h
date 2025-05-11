//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_WAVDATAPROVIDER_H
#define SR_ENGINE_WAVDATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    /// a Microsoft WAVE decoder
    class WAVDataProvider : public IWaveDataProvider {
    public:
        explicit WAVDataProvider(const RawSoundDataPtr& data);

        SR_NODISCARD const WaveDataFormat &GetWaveDataFormat() const override { return m_format; }

        SR_NODISCARD const uint8_t *GetWaveData() const override;
        SR_NODISCARD size_t GetWaveDataSize() const override;
        SR_NODISCARD size_t StreamWaveData(size_t Size) override;

        void Seek(float Seconds) override;

    private:
        RawSoundDataPtr m_data;
        size_t m_dataSize;
        WaveDataFormat m_format;

    };

    RawSoundDataPtr TryMP3InsideWAV(const RawSoundDataPtr& data);
}

#endif //SR_ENGINE_WAVDATAPROVIDER_H
