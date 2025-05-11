

# File WAVDataProvider.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Decoders**](dir_d6420aac584bfe507791c41fd230d9ac.md) **>** [**WAVDataProvider.h**](WAVDataProvider_8h.md)

[Go to the documentation of this file](WAVDataProvider_8h.md)


```C++
//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_WAVDATAPROVIDER_H
#define SR_ENGINE_WAVDATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
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
```


