//
// Created by Danilka000novishok on 08.08.2023.
//

#ifndef SR_ENGINE_AUDIOSOURCE_H
#define SR_ENGINE_AUDIOSOURCE_H

#include <Audio/macros.h>

#include <Utils/ECS/Component.h>
#include <Utils/FileSystem/Path.h>
#include <Audio/PlayParams.h>
#include <Audio/AudioMixer.h>
#include <Utils/Common/Subscription.h>

namespace SR_AUDIO_NS
{
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_AUDIO_FORMATS = "wav,mp3,ogg";

    /// @category(Sound)
    class SR_AUDIO_DLL_API AudioSource : public SR_UTILS_NS::Component {
        SR_CLASS()
    public:
        AudioSource();

        /// @method
        bool SetGroup(SR_UTILS_NS::StringAtom group);
        /// @method @evaluate
        SR_UTILS_NS::StringAtom GetGroup() const noexcept {
            return m_group;
        }

        /// @method
        bool Play();
        /// @method
        void Stop();
        /// @method
        bool Pause();
        /// @method
        bool Resume();
        /// @method
        bool Seek(float_t seconds);
        /// @method @evaluate
        float_t GetPlaybackPosition() const;
        /// @method @evaluate
        bool IsPlaying() const;
        /// @method @evaluate
        bool IsPaused() const;
        /// @method @evaluate
        bool HasFinished() const;

    public:
        void OnMatrixDirty() override;

        /// @method
        void SetLoop(bool loop);
        void SetConeInnerAngle(float_t Angle);
        /// @method
        void SetPitch(float_t pitch);
        /// @method
        void SetPath(const SR_UTILS_NS::Path& path);
        /// @method
        void SetVolume(float_t volume);
        void SetMaxDistance(float_t maxDistance);
        void SetRolloffFactor(float_t rolloffFactor);
        void SetReferenceDistance(float_t referenceDistance);
        void SetDirection(const SR_MATH_NS::FVector3& direction);
        /// @method
        void SetSpatialize(SpatializeMode spatialize);
        void SetContinueOnDisable(bool continueOnDisable);

        SR_NODISCARD bool GetLoop() const;
        SR_NODISCARD float_t GetConeInnerAngle() const;
        /// @method @evaluate
        SR_NODISCARD float_t GetPitch() const;
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const;
        /// @method @evaluate
        SR_NODISCARD float_t GetVolume() const;
        SR_NODISCARD float_t GetMaxDistance() const;
        SR_NODISCARD float_t GetRolloffFactor() const;
        SR_NODISCARD float_t GetReferenceDistance() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetDirection() const;
        SR_NODISCARD SpatializeMode GetSpatialize() const;
        SR_NODISCARD bool GetContinueOnDisable() const;

    protected:
        void OnDisable() override;
        void OnEnable() override;
        void OnDestroy() override;

    private:
        void UpdateParams();

    private:
        PlayParams m_params;
        SR_UTILS_NS::Path m_path;
        void* m_handle = nullptr;
        SR_UTILS_NS::Subscription m_mixerSubscription;
        bool m_startedPlayback = false;

        /// @property @onChanged(UpdateParams)
        SR_UTILS_NS::StringAtom m_group;
        /// @property
        bool m_playOnEnable = true;

        /// @virtualProperty(sound) @getter(GetPath) @setter(SetPath)
        /// @customArgs(pick: enabled, filter name: Sound, relative: resources)
        /// @customArg(filter value: ogg,mp3,wav)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(volume) @getter(GetVolume) @setter(SetVolume) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(pitch) @getter(GetPitch) @setter(SetPitch) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(loop) @getter(GetLoop) @setter(SetLoop) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(maxDistance) @getter(GetMaxDistance) @setter(SetMaxDistance) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(rolloffFactor) @getter(GetRolloffFactor) @setter(SetRolloffFactor) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(referenceDistance) @getter(GetReferenceDistance) @setter(SetReferenceDistance) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(spatialize) @getter(GetSpatialize) @setter(SetSpatialize) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(direction) @getter(GetDirection) @setter(SetDirection) @group(Audio params)
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(coneInnerAngle) @getter(GetConeInnerAngle) @setter(SetConeInnerAngle) @group(Audio params)
        SR_VIRTUAL_PROPERTY

        /// @property
        bool m_continueOnDisable = false;

    };
}

#endif //SR_ENGINE_AUDIOSOURCE_H
