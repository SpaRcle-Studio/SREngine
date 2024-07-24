//
// Created by Danilka000novishok on 08.08.2023.
//

#ifndef SR_ENGINE_AUDIOSOURCE_H
#define SR_ENGINE_AUDIOSOURCE_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/FileSystem/Path.h>
#include <Audio/PlayParams.h>

namespace SR_AUDIO_NS
{
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_AUDIO_FORMATS = "wav,mp3,ogg";

    class AudioSource : public SR_UTILS_NS::Component {
        SR_REGISTER_NEW_COMPONENT(AudioSource, 1005);
        using Super = SR_UTILS_NS::Component;
        using Handle = void*;
    public:
        AudioSource();

    public:
        bool InitializeEntity() noexcept override;

        void OnMatrixDirty() override;

        void SetLoop(bool loop);
        void SetConeInnerAngle(float_t Angle);
        void SetPitch(float_t pitch);
        void SetPath(const SR_UTILS_NS::Path& path);
        void SetVolume(float_t volume);
        void SetMaxDistance(float_t maxDistance);
        void SetRolloffFactor(float_t rolloffFactor);
        void SetReferenceDistance(float_t referenceDistance);
        void SetDirection(const SR_MATH_NS::FVector3& direction);
        void SetSpatialize(SpatializeMode spatialize);

        SR_NODISCARD bool GetLoop() const;
        SR_NODISCARD float_t GetConeInnerAngle() const;
        SR_NODISCARD float_t GetPitch() const;
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const;
        SR_NODISCARD float_t GetVolume() const;
        SR_NODISCARD float_t GetMaxDistance() const;
        SR_NODISCARD float_t GetRolloffFactor() const;
        SR_NODISCARD float_t GetReferenceDistance() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetDirection() const;
        SR_NODISCARD SpatializeMode GetSpatialize() const;

    protected:
        void OnDisable() override;
        void OnEnable() override;
        void OnDestroy() override;

    private:
        void UpdateParams();

    private:
        PlayParams m_params;
        SR_UTILS_NS::Path m_path;
        Handle m_handle = nullptr;
    };
}

#endif //SR_ENGINE_AUDIOSOURCE_H
