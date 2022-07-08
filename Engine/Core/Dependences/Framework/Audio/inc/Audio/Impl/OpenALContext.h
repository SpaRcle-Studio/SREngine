//
// Created by Monika on 08.07.2022.
//

#ifndef SRENGINE_OPENALCONTEXT_H
#define SRENGINE_OPENALCONTEXT_H

#include <Audio/SoundContext.h>

class ALCcontext;

namespace SR_AUDIO_NS {
    class OpenALContext : public SoundContext {
    public:
        explicit OpenALContext(SoundDevice* pDevice);
        ~OpenALContext() override;

    public:
        bool Init() override;

        SR_NODISCARD SoundSource AllocateSource(SoundBuffer buffer) override;

        SR_NODISCARD SoundBuffer AllocateBuffer(
                void* data,
                uint64_t dataSize,
                int32_t sampleRate,
                SoundFormat format) override;

        bool FreeBuffer(SoundBuffer* buffer) override;

        void Play(SoundSource source) override;

    private:
        ALCcontext* m_openALContext = nullptr;

    };
}

#endif //SRENGINE_OPENALCONTEXT_H
