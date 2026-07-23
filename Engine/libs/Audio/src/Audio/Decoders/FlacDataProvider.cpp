//
// Created by Monika on 09.12.2025.
//

#include <Audio/Decoders/FlacDataProvider.h>

#include <Utils/Common/AssertFwd.h>

#ifdef SR_AUDIO_USE_FLAC

#include <FLAC/all.h>

namespace SR_AUDIO_NS {
    class FLACDecoderCallbacks {
    public:
        static FLAC__StreamDecoderReadStatus ReadCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            FLAC__byte buffer[],
            size_t* bytes,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            if (!pThis || !bytes || !buffer) return FLAC__STREAM_DECODER_READ_STATUS_ABORT;

            size_t remaining = pThis->m_data->size() - pThis->m_memoryPosition;
            size_t toRead = std::min(*bytes, remaining);

            if (toRead > 0) {
                std::memcpy(buffer, pThis->m_data->data() + pThis->m_memoryPosition, toRead);
                pThis->m_memoryPosition += toRead;
                *bytes = toRead;
                return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
            } else {
                *bytes = 0;
                return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
            }
        }

        static FLAC__StreamDecoderSeekStatus SeekCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            FLAC__uint64 offset,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            if (!pThis) return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;

            if (offset > pThis->m_data->size()) return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;
            pThis->m_memoryPosition = static_cast<size_t>(offset);
            return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
        }

        static FLAC__StreamDecoderTellStatus TellCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            FLAC__uint64* offset,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            if (!pThis || !offset) return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;
            *offset = pThis->m_memoryPosition;
            return FLAC__STREAM_DECODER_TELL_STATUS_OK;
        }

        static FLAC__StreamDecoderLengthStatus LengthCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            FLAC__uint64* length,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            if (!pThis || !length) return FLAC__STREAM_DECODER_LENGTH_STATUS_ERROR;
            *length = pThis->m_data->size();
            return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
        }

        static FLAC__bool EofCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            return static_cast<uint64_t>(pThis->m_memoryPosition) >= pThis->m_data->size();
        }

        static FLAC__StreamDecoderWriteStatus WriteCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            const FLAC__Frame* frame,
            const FLAC__int32* const buffer[],
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            size_t frameSize = frame->header.blocksize * frame->header.channels;

            // выделяем место
            size_t oldSize = pThis->m_decodingBuffer.size();
            pThis->m_decodingBuffer.resize(oldSize + frameSize * sizeof(int16_t));

            uint8_t* dst = pThis->m_decodingBuffer.data() + oldSize;

            for (unsigned ch = 0; ch < frame->header.channels; ++ch) {
                for (unsigned i = 0; i < frame->header.blocksize; ++i) {
                    int16_t sample = static_cast<int16_t>(buffer[ch][i]);
                    *dst++ = sample & 0xFF;
                    *dst++ = (sample >> 8) & 0xFF;
                }
            }

            return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
        }

        static void MetadataCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            const FLAC__StreamMetadata* metadata,
            void* client_data)
        {
            auto* pThis = static_cast<FlacDataProvider*>(client_data);
            if (!metadata || !pThis) {
                return;
            }

            if (metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
                // Берём количество каналов и частоту
                pThis->m_format.m_numChannels = metadata->data.stream_info.channels;
                pThis->m_format.m_samplesPerSecond = metadata->data.stream_info.sample_rate;
                pThis->m_format.m_bitsPerSample = metadata->data.stream_info.bits_per_sample;
            }
        }

        static void ErrorCallback(
            const FLAC__StreamDecoder* /*decoder*/,
            FLAC__StreamDecoderErrorStatus status,
            void* /*client_data*/)
        {
            if (status == FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC) {
                // Часто возникает при попытке декодирования не-FLAC данных
                return;
            }

            std::string msg;
            switch (status) {
                case FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC: msg = "Lost sync"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_BAD_HEADER: msg = "Bad header"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_FRAME_CRC_MISMATCH: msg = "Frame CRC mismatch"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM: msg = "Unparseable stream"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_BAD_METADATA: msg = "Bad metadata"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_OUT_OF_BOUNDS: msg = "Out of bounds"; break;
                case FLAC__STREAM_DECODER_ERROR_STATUS_MISSING_FRAME: msg = "Missing frame"; break;
                default:
                msg = "Unknown error";
                break;
            }
            SR_ERROR("FLACDecoderCallbacks::ErrorCallback() : decoder error occurred! Status: {}", msg);
        }
    };

    FlacDataProvider::FlacDataProvider(const RawSoundDataPtr& pData)
        : Super()
        , m_data(pData)
    {
        if (!m_data || m_data->empty()) {
            SR_ERROR("FlacDataProvider() : empty data!");
            return;
        }

        m_decoder = FLAC__stream_decoder_new();
        if (!m_decoder) {
            SR_ERROR("FlacDataProvider() : failed to create FLAC decoder!");
            return;
        }

        FLAC__stream_decoder_set_md5_checking((FLAC__StreamDecoder*)m_decoder, false);

        FLAC__StreamDecoderInitStatus status = FLAC__stream_decoder_init_stream(
            (FLAC__StreamDecoder*)m_decoder,
            &FLACDecoderCallbacks::ReadCallback,
            &FLACDecoderCallbacks::SeekCallback,
            &FLACDecoderCallbacks::TellCallback,
            &FLACDecoderCallbacks::LengthCallback,
            &FLACDecoderCallbacks::EofCallback,
            &FLACDecoderCallbacks::WriteCallback,
            &FLACDecoderCallbacks::MetadataCallback,
            &FLACDecoderCallbacks::ErrorCallback,
            this
        );

        if (status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
            SR_ERROR("FlacDataProvider() : failed to init decoder: {}", FLAC__StreamDecoderInitStatusString[status]);
            return;
        }

        if (!FLAC__stream_decoder_process_until_end_of_stream((FLAC__StreamDecoder*)m_decoder)) {
            SR_ERROR("FlacDataProvider() : failed to decode FLAC data!");
        }

        m_bufferUsed = m_decodingBuffer.size();
    }

    FlacDataProvider::~FlacDataProvider() {
        if (m_decoder) {
            FLAC__stream_decoder_finish((FLAC__StreamDecoder*)m_decoder);
            FLAC__stream_decoder_delete((FLAC__StreamDecoder*)m_decoder);
        }
    }

    const uint8_t* FlacDataProvider::GetWaveData() const {
        return m_decodingBuffer.data();
    }

    size_t FlacDataProvider::GetWaveDataSize() const {
        return m_bufferUsed;
    }

    void FlacDataProvider::Seek(const float_t /*seconds*/) {
        // можно реализовать через FLAC__stream_decoder_seek_absolute
    }

    size_t FlacDataProvider::StreamWaveData(const size_t /*size*/) {
        // для потоковой версии: декодировать кусками
        return m_bufferUsed;
    }
} // namespace SR_AUDIO_NS

#endif
