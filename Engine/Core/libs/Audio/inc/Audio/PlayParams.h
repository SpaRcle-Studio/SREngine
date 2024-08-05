//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_PLAYPARAMS_H
#define SR_ENGINE_PLAYPARAMS_H

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector6.h>

#include <Audio/AudioLibrary.h>
#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(PlayParamType, uint8_t,
        Async, Loop, Library,
        Relative, Gain, MinGain,
        Pitch, ConeInnerAngle, ConeOuterAngle, UniqueId,
        Position, Direction, Velocity, ConeOuterGain,
        Orientation, Device, MaxGain, MaxDistance, RolloffFactor, ReferenceDistance, Spatialize
    );

    template<typename T> class PlayParamChangeChecker {
    public:
        PlayParamChangeChecker() = default;
        explicit PlayParamChangeChecker(const T& value)
            : m_value(value)
            , m_changed(true)
            , m_hasValue(true)
        { }

        SR_NODISCARD SR_FORCE_INLINE bool has_value() const noexcept { return m_hasValue; }
        SR_NODISCARD SR_FORCE_INLINE bool is_changed() const noexcept { return m_changed; }
        SR_NODISCARD SR_FORCE_INLINE const T& value() const noexcept { return m_value; }
        SR_NODISCARD SR_FORCE_INLINE T& value() noexcept { return m_value; }

        PlayParamChangeChecker& operator=(const T& value) {
            m_value = value;
            m_changed = true;
            m_hasValue = true;
            return *this;
        }

        SR_FORCE_INLINE void reset_changed() const noexcept {
            m_changed = false;
        }

        SR_FORCE_INLINE void mark_as_changed() const noexcept {
            m_changed = true;
        }

    private:
        T m_value;
        mutable bool m_changed : 4 = false;
        bool m_hasValue : 4 = false;

    };

    SR_ENUM_NS_CLASS_T(SpatializeMode, uint8_t,
        Off, On, Auto
    );

    struct PlayParams {
    public:
        static PlayParams GetDefault();

        void MarkAsChanged() noexcept {
            async.mark_as_changed();
            loop.mark_as_changed();
            spatialize.mark_as_changed();
            library.mark_as_changed();
            maxDistance.mark_as_changed();
            referenceDistance.mark_as_changed();
            rolloffFactor.mark_as_changed();
            relative.mark_as_changed();
            gain.mark_as_changed();
            minGain.mark_as_changed();
            pitch.mark_as_changed();
            maxGain.mark_as_changed();
            coneInnerAngle.mark_as_changed();
            uniqueId.mark_as_changed();
            position.mark_as_changed();
            direction.mark_as_changed();
            velocity.mark_as_changed();
            orientation.mark_as_changed();
            device.mark_as_changed();
        }

    public:
        PlayParamChangeChecker<bool> async;
        PlayParamChangeChecker<bool> loop;
        PlayParamChangeChecker<SpatializeMode> spatialize;
        PlayParamChangeChecker<AudioLibrary> library;
        PlayParamChangeChecker<float_t> maxDistance;
        PlayParamChangeChecker<float_t> referenceDistance;
        PlayParamChangeChecker<float_t> rolloffFactor;
        PlayParamChangeChecker<float_t> relative;
        PlayParamChangeChecker<float_t> gain;
        PlayParamChangeChecker<float_t> minGain;
        PlayParamChangeChecker<float_t> pitch;
        PlayParamChangeChecker<float_t> maxGain;
        PlayParamChangeChecker<float_t> coneInnerAngle;
        PlayParamChangeChecker<uint64_t> uniqueId;
        PlayParamChangeChecker<SR_MATH_NS::FVector3> position;
        PlayParamChangeChecker<SR_MATH_NS::FVector3> direction;
        PlayParamChangeChecker<SR_MATH_NS::FVector3> velocity;
        PlayParamChangeChecker<SR_MATH_NS::FVector6> orientation;
        PlayParamChangeChecker<std::string> device;

    };
}

#endif //SR_ENGINE_PLAYPARAMS_H
