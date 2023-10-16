//
// Created by Capitan_Slider on 30.09.2023.
//

#ifndef SRENGINE_SOUNDLISTENER_H
#define SRENGINE_SOUNDLISTENER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>

namespace SR_AUDIO_NS{
    class SoundDevice;

    SR_ENUM_NS_CLASS_T(ListenerDistanceModel, uint8_t,
       None,
       InverseDistance,
       InverseDistanceClamped,
       LinearDistance,
       LinearDistanceClamped,
       ExponentDistance,
       ExponentDistanceClamped
    );

    class SoundListener : public SR_UTILS_NS::NonCopyable {
    public:
        SoundListener* Allocate(SoundDevice* pDevice);

    public:
        virtual bool Init() { return true; };
        virtual bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) { return true; }

    public:
        SR_NODISCARD ListenerDistanceModel GetDistanceModel() const noexcept { return m_distanceModel; }
        SR_NODISCARD float_t GetRolloffFactor() const noexcept { return m_rolloffFactor; }
        SR_NODISCARD float_t GetReferenceDistance() const noexcept { return m_referenceDistance; }
        SR_NODISCARD float_t GetMaxDistance() const noexcept { return m_maxDistance; }

        virtual void SetDistanceModel(ListenerDistanceModel distanceModel) { m_distanceModel = distanceModel; }
        virtual void SetRolloffFactor(float_t rolloffFactor) { m_rolloffFactor = rolloffFactor; }
        virtual void SetReferenceDistance(float_t referenceDistance) { m_referenceDistance = referenceDistance; }
        virtual void SetMaxDistance(float_t maxDistance) { m_maxDistance = maxDistance; }

    protected:
        ListenerDistanceModel m_distanceModel = ListenerDistanceModel::InverseDistanceClamped;
        float_t m_rolloffFactor = 1.0f;
        float_t m_referenceDistance = 1.0f;
        float_t m_maxDistance = SR_FLOAT_MAX;

    };
}

#endif //SRENGINE_SOUNDLISTENER_H