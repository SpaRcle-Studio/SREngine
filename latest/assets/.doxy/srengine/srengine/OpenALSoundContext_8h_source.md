

# File OpenALSoundContext.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Impl**](dir_1bd135d85244281d14f19c1ce566dd82.md) **>** [**OpenALSoundContext.h**](OpenALSoundContext_8h.md)

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


