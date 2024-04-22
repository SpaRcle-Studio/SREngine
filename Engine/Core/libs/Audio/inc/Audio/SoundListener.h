//
// Created by Capitan_Slider on 30.09.2023.
//

#ifndef SR_ENGINE_SOUNDLISTENER_H
#define SR_ENGINE_SOUNDLISTENER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>

#include <Audio/ListenerData.h>

namespace SR_AUDIO_NS{
    class SoundDevice;

    class SoundListener : public SR_UTILS_NS::NonCopyable {
    public:
        SoundListener* Allocate(SoundDevice* pDevice);

    public:
        virtual bool Init() { return true; };
        virtual bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) { return true; }

    public:
        SR_NODISCARD ListenerData* GetData() const noexcept { return m_data; }

        SR_NODISCARD ListenerDistanceModel GetDistanceModel() const noexcept { return m_data->distanceModel; }
        SR_NODISCARD float_t GetRolloffFactor() const noexcept { return m_data->rolloffFactor; }
        SR_NODISCARD float_t GetReferenceDistance() const noexcept { return m_data->referenceDistance; }
        SR_NODISCARD float_t GetMaxDistance() const noexcept { return m_data->maxDistance; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetVelocity() const noexcept { return m_data->velocity; }
        SR_NODISCARD float_t GetDopplerFactor() const noexcept { return m_data->dopplerFactor; }
        SR_NODISCARD float_t GetGain() const noexcept { return m_data->gain; }
        SR_NODISCARD float_t GetOuterConeGain() const noexcept { return m_data->outerConeGain; }

        void SetData(ListenerData* data) { m_data = data; }

        virtual void SetDistanceModel(ListenerDistanceModel distanceModel) { m_data->distanceModel = distanceModel; }
        virtual void SetRolloffFactor(float_t rolloffFactor) { m_data->rolloffFactor = rolloffFactor; }
        virtual void SetReferenceDistance(float_t referenceDistance) { m_data->referenceDistance = referenceDistance; }
        virtual void SetMaxDistance(float_t maxDistance) { m_data->maxDistance = maxDistance; }
        virtual void SetVelocity(SR_MATH_NS::FVector3 velocity) { m_data->velocity = velocity; }
        virtual void SetDopplerFactor(float_t dopplerFactor) { m_data->dopplerFactor = dopplerFactor; }
        virtual void SetGain(float_t gain) { m_data->gain = gain; }
        virtual void SetOuterConeGain(float_t outerConeGain) { m_data->outerConeGain = outerConeGain; }

    protected:
        ListenerData* m_data = nullptr;

    };
}

#endif //SR_ENGINE_SOUNDLISTENER_H