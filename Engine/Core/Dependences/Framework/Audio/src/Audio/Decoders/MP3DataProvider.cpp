//
// Created by Monika on 07.07.2022.
//

#include <Audio/Decoders/MP3DataProvider.h>

#define MINIMP3_IMPLEMENTATION 1
#include <minimp3/minimp3.h>

namespace SR_AUDIO_NS {
    struct DecoderData
    {
        mp3dec_t m_Decoder;
        mp3dec_frame_info_t m_Info;
    };

    MP3DataProvider::MP3DataProvider(const SoundData& data)
            : m_data(data)
            , m_format()
            , m_decodingBuffer(MINIMP3_MAX_SAMPLES_PER_FRAME * 16 )
            , m_bufferUsed(0)
            , m_streamPos(0)
            , m_initialStreamPos(0)
            , m_isEndOfStream(false)
            , m_decoderData(new DecoderData())
    {
        mp3dec_init(&m_decoderData->m_Decoder);

        LoadMP3Info();

        m_format.m_numChannels      = m_decoderData->m_Info.channels;
        m_format.m_samplesPerSecond = m_decoderData->m_Info.hz;
        m_format.m_bitsPerSample    = 16;
    }

    MP3DataProvider::~MP3DataProvider() {
        delete(m_decoderData);
    }

    void MP3DataProvider::LoadMP3Info()
    {
        int Samples = 0;

        do
        {
            Samples = mp3dec_decode_frame(
                    &m_decoderData->m_Decoder,
                    m_data ? const_cast<uint8_t*>(m_data->data() + m_streamPos) : nullptr,
                    m_data ? m_data->size() - m_streamPos: 0,
                    (signed short*)m_decodingBuffer.data(),
                    &m_decoderData->m_Info
            );

            m_streamPos += m_decoderData->m_Info.frame_bytes;
        }
        while (Samples == 0 && m_decoderData->m_Info.frame_bytes > 0);

        m_initialStreamPos = m_streamPos;
    }

    const uint8_t* MP3DataProvider::GetWaveData() const
    {
        return m_decodingBuffer.data();
    }

    size_t MP3DataProvider::GetWaveDataSize() const
    {
        return m_bufferUsed;
    }

    int MP3DataProvider::DecodeFromFile(size_t BytesRead)
    {
        if (m_isEndOfStream || !m_data )
        {
            return 0;
        }

        int Samples = 0;

        do
        {
            Samples = mp3dec_decode_frame(
                    &m_decoderData->m_Decoder,
                    const_cast<uint8_t*>( m_data->data() + m_streamPos ),
                    m_data->size() - m_streamPos,
                    (signed short*)( m_decodingBuffer.data() + BytesRead ),
                    &m_decoderData->m_Info
            );
            m_streamPos += m_decoderData->m_Info.frame_bytes;
        }
        while (Samples == 0 && m_decoderData->m_Info.frame_bytes > 0);

        m_format.m_numChannels      = m_decoderData->m_Info.channels;
        m_format.m_samplesPerSecond = m_decoderData->m_Info.hz;

        if (m_streamPos >= m_data->size() || !Samples)
        {
            m_isEndOfStream = true;
        }

        return Samples * m_decoderData->m_Info.channels * 2;
    }

    size_t MP3DataProvider::StreamWaveData( size_t Size )
    {
        if (m_isEndOfStream)
        {
            return 0;
        }

        size_t OldSize = m_decodingBuffer.size();

        if ( Size > OldSize )
        {
            m_decodingBuffer.resize( Size, 0 );
        }

        size_t BytesRead = 0;

        while ( BytesRead + MINIMP3_MAX_SAMPLES_PER_FRAME * 2 < Size )
        {
            int Ret = DecodeFromFile( BytesRead );

            if ( Ret > 0 )
            {
                BytesRead += Ret;
            }
            else if ( Ret == 0 )
            {
                m_isEndOfStream = true;
                break;
            }
            else
            {
                // there is no audio data in this frame, just skip it
            }
        }

        m_bufferUsed = BytesRead;

        return m_bufferUsed;
    }

    void MP3DataProvider::Seek(float_t seconds)
    {
        mp3dec_init(&m_decoderData->m_Decoder);

        m_streamPos = 0;
        m_isEndOfStream = false;

        LoadMP3Info();
    }
}