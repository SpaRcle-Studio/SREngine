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
        explicit MP3DataProvider(const SoundData& data);
        ~MP3DataProvider() override;

        virtual const WaveDataFormat& GetWaveDataFormat() const override { return m_format; }

        virtual const uint8_t* GetWaveData() const override;
        virtual size_t GetWaveDataSize() const override;

        virtual size_t StreamWaveData(size_t size) override;
        virtual bool IsStreaming() const override { return true; }
        virtual bool IsEndOfStream() const override { return m_isEndOfStream; }
        virtual void Seek(float_t seconds) override;

    private:
        int DecodeFromFile(size_t bytesRead);
        void LoadMP3Info();

    private:
        SoundData m_data;
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
