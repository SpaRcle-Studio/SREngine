//
// Created by Monika on 07.07.2022.
//

#ifndef SRENGINE_WAVDATAPROVIDER_H
#define SRENGINE_WAVDATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    /// a Microsoft WAVE decoder
    class WAVDataProvider : public IWaveDataProvider {
    public:
        explicit WAVDataProvider(const RawSoundDataPtr& data);

        SR_NODISCARD virtual const WaveDataFormat &GetWaveDataFormat() const override { return m_format; }

        SR_NODISCARD virtual const uint8_t *GetWaveData() const override;
        SR_NODISCARD virtual size_t GetWaveDataSize() const override;
        SR_NODISCARD virtual size_t StreamWaveData(size_t Size) override;

        virtual void Seek(float Seconds) override;

    private:
        RawSoundDataPtr m_data;
        size_t m_dataSize;
        WaveDataFormat m_format;

    };

    RawSoundDataPtr TryMP3InsideWAV(const RawSoundDataPtr& data);
}

#endif //SRENGINE_WAVDATAPROVIDER_H
