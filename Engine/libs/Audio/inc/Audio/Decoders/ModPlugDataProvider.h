//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_MODPLUGDATAPROVIDER_H
#define SR_ENGINE_MODPLUGDATAPROVIDER_H

#include <Audio/Decoders/IWaveDataProvider.h>

#include <modplug.h>

namespace SR_AUDIO_NS {
    /// ModPlug decoder
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

        /// ModPlug stuff
        ModPlugFile* m_ModPlugFile;
    };
}

#endif //SR_ENGINE_MODPLUGDATAPROVIDER_H
