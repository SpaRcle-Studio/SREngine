//
// Created by Monika on 08.07.2022.
//

#ifndef SRENGINE_SOUNDCONTEXT_H
#define SRENGINE_SOUNDCONTEXT_H

#include <Utils/Common/NonCopyable.h>
#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    class SoundDevice;

    class SoundContext : public SR_UTILS_NS::NonCopyable {
    protected:
        explicit SoundContext(SoundDevice* pDevice);

    public:
        ~SoundContext() override = default;

        static SoundContext* Allocate(SoundDevice* pDevice);

    public:
        SR_NODISCARD SoundDevice* GetDevice() const;

        SR_NODISCARD virtual SoundSource AllocateSource(SoundBuffer buffer) = 0;

        SR_NODISCARD virtual SoundBuffer AllocateBuffer(
                void* data,
                uint64_t dataSize,
                int32_t sampleRate,
                SoundFormat format) = 0;

        virtual bool FreeBuffer(SoundBuffer* buffer) = 0;

        virtual void Play(SoundSource source) = 0;

        virtual bool Init() = 0;

    private:
        SoundDevice* m_device = nullptr;

    };
}

#endif //SRENGINE_SOUNDCONTEXT_H
