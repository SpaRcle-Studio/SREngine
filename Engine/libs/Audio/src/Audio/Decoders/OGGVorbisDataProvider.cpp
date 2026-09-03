//
// Created by Monika on 09.12.2025.
//

#include <Audio/Decoders/OGGVorbisDataProvider.h>

#include <Utils/Common/AssertFwd.h>

#ifdef SR_AUDIO_USE_VORBIS

#include <vorbis/vorbisfile.h>

namespace SR_AUDIO_NS {
    OGGVorbisDataProvider::OGGVorbisDataProvider(const RawSoundDataPtr& pData)
        : Super()
        , m_data(pData)
    {
        m_vorbisFile = new OggVorbis_File();

        ov_callbacks callbacks;
        std::memset(&callbacks, 0, sizeof(callbacks));

        callbacks.read_func  = OGGReadFunc;
        callbacks.seek_func  = OGGSeekFunc;
        callbacks.close_func = OGGCloseFunc;
        callbacks.tell_func  = OGGTellFunc;

        const auto ret = ov_open_callbacks(this, m_vorbisFile.Get(), nullptr, 0, callbacks);
        switch (ret) {
            case 0: break; // success
            case OV_EREAD: SR_ERROR("OGGDataProvider::OGGDataProvider() : a read from media returned an error."); return;
            case OV_EFAULT: SR_ERROR("OGGDataProvider::OGGDataProvider() : internal logic fault (bug or heap/stack corruption)."); return;
            case OV_EIMPL: SR_ERROR("OGGDataProvider::OGGDataProvider() : feature not implemented."); return;
            case OV_EINVAL: SR_ERROR("OGGDataProvider::OGGDataProvider() : invalid argument."); return;
            case OV_ENOTVORBIS: SR_ERROR("OGGDataProvider::OGGDataProvider() : bitstream is not Vorbis data."); return;
            case OV_EBADHEADER: SR_ERROR("OGGDataProvider::OGGDataProvider() : invalid Vorbis bitstream header."); return;
            case OV_EVERSION: SR_ERROR("OGGDataProvider::OGGDataProvider() : Vorbis version mismatch."); return;
            case OV_ENOTAUDIO: SR_ERROR("OGGDataProvider::OGGDataProvider() : bitstream does not contain audio data."); return;
            case OV_EBADPACKET: SR_ERROR("OGGDataProvider::OGGDataProvider() : corrupt Vorbis packet or invalid Ogg bitstream."); return;
            case OV_EBADLINK: SR_ERROR("OGGDataProvider::OGGDataProvider() : invalid stream section supplied to libvorbisfile."); return;
            case OV_ENOSEEK: SR_ERROR("OGGDataProvider::OGGDataProvider() : bitstream is not seekable."); return;
            default:
                SR_ERROR("OGGDataProvider::OGGDataProvider() : unknown error code {}.", ret);
                return;
        }

        if (vorbis_info* pVorbisInfo = ov_info(m_vorbisFile.Get(), -1)) {
            m_format.m_numChannels      = pVorbisInfo->channels;
            m_format.m_samplesPerSecond = pVorbisInfo->rate;
            m_format.m_bitsPerSample    = 16;
        }
        else {
            SR_ERROR("OGGDataProvider::OGGDataProvider() : failed to get vorbis info!");
            return;
        }

        // Размер PCM заранее известен.
        const ogg_int64_t totalSamples = ov_pcm_total(m_vorbisFile.Get(), -1);

        if (totalSamples <= 0) {
            SR_ERROR("OGGVorbisDataProvider : invalid PCM sample count.");
            return;
        }

        const size_t bytesPerSample = static_cast<size_t>(m_format.m_bitsPerSample / 8);
        const size_t totalBytes = static_cast<size_t>(totalSamples) * static_cast<size_t>(m_format.m_numChannels) * bytesPerSample;

        m_decodingBuffer.resize(totalBytes);

        size_t bytesRead = 0;

        while (bytesRead < totalBytes) {
            const long ret = ov_read(
                m_vorbisFile.Get(),
                reinterpret_cast<char*>(m_decodingBuffer.data() + bytesRead),
                static_cast<int>(std::min(
                        totalBytes - bytesRead,
                        static_cast<size_t>(std::numeric_limits<int>::max())
                )),
                0, // little endian
                2, // 16-bit
                1, // signed
                &m_currentSection
            );

            if (ret > 0) {
                bytesRead += static_cast<size_t>(ret);
                continue;
            }

            if (ret == 0) {
                break;
            }

            if (ret == OV_HOLE) {
                continue;
            }

            SR_ERROR("OGGVorbisDataProvider : ov_read() failed: {}.", ret);
            break;
        }

        m_bufferUsed = bytesRead;
        m_decodingBuffer.resize(bytesRead);
    }

    OGGVorbisDataProvider::~OGGVorbisDataProvider() {
        ov_clear(m_vorbisFile.Get());
    }

    const uint8_t* OGGVorbisDataProvider::GetWaveData() const {
        return m_decodingBuffer.data();
    }

    size_t OGGVorbisDataProvider::GetWaveDataSize() const {
        return m_bufferUsed;
    }

    void OGGVorbisDataProvider::Seek(const float_t seconds) {
        m_isEndOfStream = false;
        ov_time_seek(m_vorbisFile.Get(), static_cast<double_t>(seconds));
    }

    size_t OGGVorbisDataProvider::StreamWaveData(const size_t size) {
        if (m_isEndOfStream) {
            return 0;
        }

        const size_t oldSize = m_decodingBuffer.size();

        if (size > oldSize) {
            m_decodingBuffer.resize(size, 0);
        }

        size_t bytesRead = 0;

        while (bytesRead < size) {
            int Ret = DecodeFromFile(size, bytesRead);

            if (Ret > 0) {
                bytesRead += Ret;
            }
            else if (Ret == 0) {
                m_isEndOfStream = true;
                break;
            }
            else {
                // there is no audio data in this frame, just skip it
                break;
            }
        }

        m_bufferUsed = bytesRead;

        return m_bufferUsed;
    }

    int32_t OGGVorbisDataProvider::DecodeFromFile(size_t size, size_t bytesRead) {
        if (m_isEndOfStream) {
            return 0;
        }

        return static_cast<int>(
            ov_read(
                m_vorbisFile.Get(),
                reinterpret_cast<char*>(m_decodingBuffer.data() + bytesRead),
                static_cast<int32_t>(static_cast<int64_t>(size) - static_cast<int64_t>(bytesRead)),
                0, // LITTLE_ENDIAN
                m_format.m_bitsPerSample >> 3,
                1,
                &m_currentSection
            )
        );
    }

    size_t OGGVorbisDataProvider::OGGReadFunc(void* ptr, const size_t size, const size_t numMemBlocks, void* pUserData) {
        /*auto&& pProvider = static_cast<OGGVorbisDataProvider*>(pUserData);

        const size_t dataSize = pProvider->m_data ? pProvider->m_data->size() : 0;
        const size_t bytesSize = size * numMemBlocks;

        size_t bytesRead = dataSize - pProvider->m_rawPosition;

        if (bytesSize < bytesRead) {
            bytesRead = bytesSize;
        }

        if (pProvider->m_data) {
            memcpy(ptr, pProvider->m_data->data() + pProvider->m_rawPosition, bytesRead);
        }

        pProvider->m_rawPosition += bytesRead;

        return bytesRead;*/

        auto* p = static_cast<OGGVorbisDataProvider*>(pUserData);
        if (!p || !p->m_data) return 0;

        const size_t dataSize = p->m_data->size();
        if (static_cast<size_t>(p->m_rawPosition) >= dataSize) return 0;

        const size_t req = size * numMemBlocks;
        const size_t avail = dataSize - p->m_rawPosition;
        const size_t toRead = req < avail ? req : avail;

        if (toRead > 0) {
            std::memcpy(ptr, p->m_data->data() + p->m_rawPosition, toRead);
            p->m_rawPosition += toRead;
        }
        return toRead;
    }

    int32_t OGGVorbisDataProvider::OGGSeekFunc(void* pUserData, const int64_t offset, const int32_t whence) {
        /*auto&& pProvider = static_cast<OGGVorbisDataProvider*>(pUserData);

        uint64_t dataSize = pProvider->m_data ? pProvider->m_data->size() : 0;

        if (whence == SEEK_SET) {
            pProvider->m_rawPosition = offset;
        }
        else if (whence == SEEK_CUR) {
            pProvider->m_rawPosition += offset;
        }
        else if (whence == SEEK_END) {
            pProvider->m_rawPosition = dataSize + offset;
        }

        if (pProvider->m_rawPosition > dataSize) {
            pProvider->m_rawPosition = dataSize;
        }

        return static_cast<int32_t>(pProvider->m_rawPosition);*/

        auto* p = static_cast<OGGVorbisDataProvider*>(pUserData);
        if (!p || !p->m_data) return -1;

        const int64_t size = static_cast<int64_t>(p->m_data->size());
        int64_t newPos = (int64_t)p->m_rawPosition;

        switch (whence) {
            case SEEK_SET: newPos = offset; break;
            case SEEK_CUR: newPos += offset; break;
            case SEEK_END: newPos = size + offset; break;
            default: return -1;
        }

        if (newPos < 0) newPos = 0;
        if (newPos > size) newPos = size;
        p->m_rawPosition = static_cast<size_t>(newPos);
        return 0;
    }

    int OGGVorbisDataProvider::OGGCloseFunc(void* /* pUserData */) {
        return 0;
    }

    long OGGVorbisDataProvider::OGGTellFunc(void* pUserData) {
        //auto&& pProvider = static_cast<OGGVorbisDataProvider*>(pUserData);
        //return pProvider->m_rawPosition;

        auto* p = static_cast<OGGVorbisDataProvider*>(pUserData);
        return p ? static_cast<long>(p->m_rawPosition) : 0;
    }
}

#endif