//
// Created by Monika on 07.07.2022.
//

#include <Audio/Decoders/MP3DataProvider.h>

#define MINIMP3_IMPLEMENTATION 1
#include <minimp3/minimp3_ex.h>

namespace SR_AUDIO_NS {
    struct DecoderData
    {
        mp3dec_ex_t mp3d;
    };

    MP3DataProvider::MP3DataProvider(const RawSoundDataPtr& data)
            : m_data(data)
            , m_format()
            , m_decodingBuffer(MINIMP3_MAX_SAMPLES_PER_FRAME * 16 )
            , m_bufferUsed(0)
            , m_streamPos(0)
            , m_initialStreamPos(0)
            , m_isEndOfStream(false)
            , m_decoderData(new DecoderData())
    {
        if (mp3dec_ex_open_buf(&m_decoderData->mp3d, data->data(), data->size(), MP3D_SEEK_TO_SAMPLE)) {
            SR_ERROR("MP3DataProvider::MP3DataProvider() : failed to load a buffer!");
            return;
        }

        /** dec.samples, dec.info.hz, dec.info.layer, dec.info.channels should be filled */
        if (mp3dec_ex_seek(&m_decoderData->mp3d, 0))
        {
            SR_ERROR("MP3DataProvider::MP3DataProvider() : failed to seek a buffer!");
            return;
        }

        m_decodingBuffer.resize(m_decoderData->mp3d.samples * sizeof(mp3d_sample_t));

        m_bufferUsed = mp3dec_ex_read(&m_decoderData->mp3d, (mp3d_sample_t*)m_decodingBuffer.data(), m_decoderData->mp3d.samples);
        if (m_bufferUsed != m_decoderData->mp3d.samples) /* normal eof or error condition */
        {
            if (m_decoderData->mp3d.last_error)
            {
                /// TODO
            }

            SR_ERROR("MP3DataProvider::MP3DataProvider() : samples count is different!");
            return;
        }

        m_format.m_numChannels = m_decoderData->mp3d.info.channels;
        m_format.m_samplesPerSecond = m_decoderData->mp3d.info.hz;
        m_format.m_bitsPerSample = 16;
    }

    MP3DataProvider::~MP3DataProvider() {
        if (m_decoderData) {
            mp3dec_ex_close(&m_decoderData->mp3d);
            delete m_decoderData;
            m_decoderData = nullptr;
        }
    }

    const uint8_t* MP3DataProvider::GetWaveData() const
    {
        return m_decodingBuffer.data();
    }

    size_t MP3DataProvider::GetWaveDataSize() const
    {
        return m_bufferUsed;
    }

    void MP3DataProvider::Seek(float_t seconds)
    {

    }

    size_t MP3DataProvider::StreamWaveData(size_t size) {
        return IWaveDataProvider::StreamWaveData(size);
    }
}