

# File ModPlugDataProvider.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Decoders**](dir_16681fe1464e2912a23db58ce5093931.md) **>** [**ModPlugDataProvider.h**](ModPlugDataProvider_8h.md)

[Go to the documentation of this file](ModPlugDataProvider_8h.md)


```C++
//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_MODPLUGDATAPROVIDER_H
#define SR_ENGINE_MODPLUGDATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

#include <modplug.h>

namespace SR_AUDIO_NS {
    class ModPlugDataProvider : public IWaveDataProvider
    {
    public:
        explicit ModPlugDataProvider(const RawSoundDataPtr& data);
        ~ModPlugDataProvider() override;

        SR_NODISCARD const WaveDataFormat& GetWaveDataFormat() const override { return m_format; }

        const uint8_t* GetWaveData() const override;
        size_t GetWaveDataSize() const override;

        size_t StreamWaveData(size_t size) override;
        bool IsStreaming() const override { return true; }
        bool IsEndOfStream() const override { return m_isEndOfStream; }
        void Seek(float_t seconds) override;

    private:
        int DecodeFromFile(size_t size);

    private:
        RawSoundDataPtr m_data;
        WaveDataFormat m_format;

        std::vector<uint8_t> m_decodingBuffer;
        size_t m_bufferUsed;

        bool m_isEndOfStream;

        ModPlugFile* m_ModPlugFile;
    };
}

#endif //SR_ENGINE_MODPLUGDATAPROVIDER_H
```


