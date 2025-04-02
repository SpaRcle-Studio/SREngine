

# File OpenALSoundContext.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Impl**](dir_45f97ee406bd7a76126228ed02b235a4.md) **>** [**OpenALSoundContext.h**](OpenALSoundContext_8h.md)

[Go to the documentation of this file](OpenALSoundContext_8h.md)


```C++
//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_OPENALSOUNDCONTEXT_H
#define SR_ENGINE_OPENALSOUNDCONTEXT_H

#include <Audio/SoundContext.h>

class ALCcontext;

namespace SR_AUDIO_NS {
    class OpenALSoundContext : public SoundContext {
        using Super = SoundContext;
    public:
        explicit OpenALSoundContext(SoundDevice* pDevice);
        ~OpenALSoundContext() override;

    public:
        bool Init() override;
        void Play(SoundSource source) override;

        bool MakeContextCurrent() override;

        void ApplyParamImpl(SoundSource pSource, PlayParamType paramType, const void* pValue) override;

    public:
        SR_NODISCARD bool IsPlaying(SoundSource pSource) const override;
        SR_NODISCARD bool IsPaused(SoundSource pSource) const override;
        SR_NODISCARD bool IsStopped(SoundSource pSource) const override;

    public:
        SR_NODISCARD SoundSource AllocateSource(SoundBuffer buffer) override;

        SR_NODISCARD PlayParams GetSourceParams(SoundSource pSource) const override;

        SR_NODISCARD SoundBuffer AllocateBuffer(
                void* data,
                uint64_t dataSize,
                int32_t sampleRate,
                SoundFormat format) override;

    public:
        bool FreeBuffer(SoundBuffer* buffer) override;
        bool FreeSource(SoundSource* pSource) override;

    private:
        ALCcontext* m_openALContext = nullptr;

    };
}

#endif //SR_ENGINE_OPENALSOUNDCONTEXT_H
```


