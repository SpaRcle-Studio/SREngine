//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_SOUNDCONTEXT_H
#define SR_ENGINE_SOUNDCONTEXT_H

#include <Utils/Common/NonCopyable.h>
#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    class SoundDevice;
    class SoundListener;

    class SoundContext : public SR_UTILS_NS::NonCopyable {
    protected:
        explicit SoundContext(SoundDevice* pDevice);

    public:
        ~SoundContext() override;

        static SoundContext* Allocate(SoundDevice* pDevice);

    public:
        SR_NODISCARD SoundDevice* GetDevice() const;

        SR_NODISCARD virtual bool IsPlaying(SoundSource pSource) const = 0;
        SR_NODISCARD virtual bool IsPaused(SoundSource pSource) const = 0;
        SR_NODISCARD virtual bool IsStopped(SoundSource pSource) const = 0;

        SR_NODISCARD virtual bool MakeContextCurrent() = 0;

        SR_NODISCARD virtual SoundListener* AllocateListener();

        SR_NODISCARD virtual SoundSource AllocateSource(SoundBuffer buffer) = 0;

        SR_NODISCARD virtual SoundBuffer AllocateBuffer(
                void* data,
                uint64_t dataSize,
                int32_t sampleRate,
                SoundFormat format) = 0;

        SR_NODISCARD virtual PlayParams GetSourceParams(SoundSource pSource) const = 0;

        template <typename T> void ApplyParam(SoundSource pSource, const T& newParam, T& currentParam, PlayParamType paramType) {
            if (newParam.has_value()) { /// Данил, мы тебя любим! (с) SpaRcle Team <3
                if (currentParam.has_value()) {
                    if (const_cast<const T&>(currentParam).value() != newParam.value()) {
                        currentParam = newParam;
                        ApplyParamImpl(pSource, paramType, (void*)&currentParam.value());
                    }
                }
                else {
                    currentParam = newParam;
                    ApplyParamImpl(pSource, paramType, (void*)&currentParam.value());
                }
            }
        }

        template <typename T> void ApplyParam(SoundSource pSource, const T& newParam, PlayParamType paramType) {
            SR_TRACY_ZONE;
            if (newParam.has_value() && newParam.is_changed()) { /// Данил, мы тебя любим! (с) SpaRcle Team <3
                ApplyParamImpl(pSource, paramType, (void*)&newParam.value());
                newParam.reset_changed();
            }
        }

        virtual void ApplyParams(SoundSource pSource, const PlayParams& params);
        virtual void ApplyParamImpl(SoundSource pSource, PlayParamType paramType, const void* pValue) = 0;

        virtual bool FreeBuffer(SoundBuffer* buffer) = 0;
        virtual bool FreeSource(SoundSource* pSource) = 0;
        virtual bool FreeListener(SoundListener* pListener);

        virtual void Play(SoundSource source) = 0;

        virtual bool Init() = 0;

    protected:
        SoundDevice* m_device = nullptr;
        std::list<SoundListener*> m_listeners;

    };
}

#endif //SR_ENGINE_SOUNDCONTEXT_H
