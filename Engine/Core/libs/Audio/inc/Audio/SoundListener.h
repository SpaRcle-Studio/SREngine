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
        explicit SoundListener(SoundDevice* pDevice)
            : m_pDevice(pDevice)
        { }

        SoundListener* Allocate(SoundDevice* pDevice);

    public:
        virtual bool Init() { return true; }
        virtual bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) { return true; }

    public:
        SR_NODISCARD const ListenerData& GetData() const noexcept { return m_data; }
        SR_NODISCARD ListenerData& GetData() noexcept { return m_data; }

        SR_NODISCARD virtual ListenerDistanceModel GetDistanceModel() const noexcept { return m_data.distanceModel; }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetVelocity() const noexcept { return m_data.velocity; }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetPosition() const noexcept { return m_data.position; }
        SR_NODISCARD virtual SR_MATH_NS::FVector6 GetOrientation() const noexcept { return m_data.orientation; }
        SR_NODISCARD virtual float_t GetGain() const noexcept { return m_data.gain; }

        SR_NODISCARD SoundDevice* GetDevice() const noexcept { return m_pDevice; }

        void SetData(const ListenerData& data) { m_data = data; }

        virtual void SetDistanceModel(ListenerDistanceModel distanceModel) { m_data.distanceModel = distanceModel; }
        virtual void SetVelocity(SR_MATH_NS::FVector3 velocity) { m_data.velocity = velocity; }
        virtual void SetGain(float_t gain) { m_data.gain = gain; }

    protected:
        ListenerData m_data;

    private:
        SoundDevice* m_pDevice = nullptr;

    };
}

#endif //SR_ENGINE_SOUNDLISTENER_H