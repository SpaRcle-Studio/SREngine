//
// Created by innerviewer on 10/11/2023.
//

#ifndef SR_ENGINE_OPENALSOUNDLISTENER_H
#define SR_ENGINE_OPENALSOUNDLISTENER_H

#include <Audio/SoundListener.h>

namespace SR_AUDIO_NS {
    class OpenALSoundListener : public SoundListener {
        using Super = SoundListener;
    public:
        explicit OpenALSoundListener(SoundDevice* pDevice)
            : Super(pDevice)
        { }

        bool Init() override;
        bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) override;

        SR_NODISCARD ListenerDistanceModel GetDistanceModel() const noexcept override;
        SR_NODISCARD SR_MATH_NS::FVector3 GetVelocity() const noexcept override;
        SR_NODISCARD SR_MATH_NS::FVector3 GetPosition() const noexcept override;
        SR_NODISCARD SR_MATH_NS::FVector6 GetOrientation() const noexcept override;
        SR_NODISCARD float_t GetGain() const noexcept override;

    public:
        void SetDistanceModel(ListenerDistanceModel distanceModel) override;
        void SetVelocity(SR_MATH_NS::FVector3 velocity) override;
        void SetGain(float_t gain) override;
    };
}
#endif //SR_ENGINE_OPENALSOUNDLISTENER_H
