//
// Created by Monika on 07.07.2022.
//

#ifndef SRENGINE_IWAVEDATAPROVIDER_H
#define SRENGINE_IWAVEDATAPROVIDER_H

#include <Utils/macros.h>

namespace SR_AUDIO_NS {
    typedef std::shared_ptr<std::vector<uint8_t>> SoundData;

    class WaveDataFormat : public SR_UTILS_NS::NonCopyable
    {
    public:
        WaveDataFormat()
            : m_numChannels(0)
            , m_samplesPerSecond(0)
            , m_bitsPerSample(0)
        { }

        ~WaveDataFormat() override = default;

    public:
        int32_t m_numChannels;
        int32_t m_samplesPerSecond;
        int32_t m_bitsPerSample;
    };

    class IWaveDataProvider : public SR_UTILS_NS::NonCopyable
    {
    public:
        using Ptr = std::shared_ptr<IWaveDataProvider>;

    public:
        ~IWaveDataProvider() override = default;

        SR_NODISCARD virtual const WaveDataFormat& GetWaveDataFormat() const = 0;

        SR_NODISCARD virtual const uint8_t* GetWaveData() const = 0;
        SR_NODISCARD virtual size_t GetWaveDataSize() const = 0;

        SR_NODISCARD virtual bool IsStreaming() const { return false; }
        SR_NODISCARD virtual bool IsEndOfStream() const { return false; }
        virtual void Seek(float_t seconds) { }
        virtual size_t StreamWaveData(size_t size) { return 0; }

        SR_NODISCARD bool IsValid() const { return GetWaveData() && GetWaveDataSize(); }

    };

    IWaveDataProvider::Ptr CreateWaveDataProvider(const SR_UTILS_NS::Path& path, const SoundData& data);
}

#endif //SRENGINE_IWAVEDATAPROVIDER_H
