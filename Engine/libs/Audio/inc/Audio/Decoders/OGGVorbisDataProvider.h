//
// Created by Monika on 09.12.2025.
//

#ifndef SR_ENGINE_AUDIO_OGG_DATA_PROVIDER_H
#define SR_ENGINE_AUDIO_OGG_DATA_PROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

#include <Utils/Types/RawPointerHolder.h>

#ifdef SR_AUDIO_USE_VORBIS

struct OggVorbis_File;

namespace SR_AUDIO_NS {
    class OGGVorbisDataProvider: public IWaveDataProvider {
        using Super = IWaveDataProvider;
    public:
        explicit OGGVorbisDataProvider(const RawSoundDataPtr& pData);

        ~OGGVorbisDataProvider() override;

        SR_NODISCARD const WaveDataFormat& GetWaveDataFormat() const override { return m_format; }
        SR_NODISCARD const uint8_t* GetWaveData() const override;
        SR_NODISCARD size_t GetWaveDataSize() const override;
        SR_NODISCARD bool IsStreaming() const override { return true; }
        SR_NODISCARD bool IsEndOfStream() const override { return m_isEndOfStream; }
        void Seek(float_t seconds) override;
        size_t StreamWaveData(size_t size) override;

    private:
        int32_t DecodeFromFile(size_t size, size_t bytesRead);
        static size_t OGGReadFunc(void* ptr, size_t size, size_t numMemBlocks, void* pUserData);
        static int32_t OGGSeekFunc(void* pUserData, int64_t offset, int32_t whence);
        static int32_t OGGCloseFunc(void* pUserData);
        static long OGGTellFunc(void* pUserData);

    private:
        RawSoundDataPtr m_data;
        WaveDataFormat m_format;

        std::vector<uint8_t> m_decodingBuffer;
        size_t m_bufferUsed = 0;

        bool m_isEndOfStream = false;

        // Vorbis stuff
        SR_UTILS_NS::RawPointerHolder<OggVorbis_File> m_vorbisFile;
        int64_t m_rawPosition = 0;
        int m_currentSection = 0;
    };
}

#endif

#endif //SR_ENGINE_AUDIO_OGG_DATA_PROVIDER_H
