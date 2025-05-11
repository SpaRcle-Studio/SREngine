

# File MP3DataProvider.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Decoders**](dir_d6420aac584bfe507791c41fd230d9ac.md) **>** [**MP3DataProvider.h**](MP3DataProvider_8h.md)

[Go to the documentation of this file](MP3DataProvider_8h.md)


```C++
//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_MP3DATAPROVIDER_H
#define SR_ENGINE_MP3DATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    class MP3DataProvider: public IWaveDataProvider
    {
    public:
        explicit MP3DataProvider(const RawSoundDataPtr& data);
        ~MP3DataProvider() override;

        SR_NODISCARD const WaveDataFormat& GetWaveDataFormat() const override { return m_format; }

        const uint8_t* GetWaveData() const override;
        size_t GetWaveDataSize() const override;

        size_t StreamWaveData(size_t size) override;
        bool IsStreaming() const override { return true; }
        bool IsEndOfStream() const override { return m_isEndOfStream; }
        void Seek(float_t seconds) override;

    private:
        RawSoundDataPtr m_data;
        WaveDataFormat m_format;

        std::vector<uint8_t> m_decodingBuffer;
        size_t m_bufferUsed;

        size_t m_streamPos;
        size_t m_initialStreamPos;
        bool m_isEndOfStream;

        // minimp3 stuff
        struct DecoderData* m_decoderData;

    };
}

#endif //SR_ENGINE_MP3DATAPROVIDER_H
```


