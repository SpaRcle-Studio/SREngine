

# File WAVDataProvider.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Decoders**](dir_16681fe1464e2912a23db58ce5093931.md) **>** [**WAVDataProvider.h**](WAVDataProvider_8h.md)

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


