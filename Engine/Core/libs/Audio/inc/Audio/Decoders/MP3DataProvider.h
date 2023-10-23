//
// Created by Monika on 07.07.2022.
//

#ifndef SRENGINE_MP3DATAPROVIDER_H
#define SRENGINE_MP3DATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    /// MPEG Layer-III decoder
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

#endif //SRENGINE_MP3DATAPROVIDER_H
