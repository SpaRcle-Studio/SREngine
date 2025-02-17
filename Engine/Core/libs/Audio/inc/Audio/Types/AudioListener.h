//
// Created by Capitan_Slider on 16.09.2023.
//

#ifndef SR_ENGINE_AUDIOLSTENER_H
#define SR_ENGINE_AUDIOLSTENER_H

#include <Audio/ListenerData.h>
#include <Utils/ECS/Component.h>

namespace SR_AUDIO_NS
{
    class SoundListener;

    class AudioListener : public SR_UTILS_NS::Component {
        SR_CLASS()
        SR_REGISTER_NEW_COMPONENT(AudioListener, 1003);
        using Super = SR_UTILS_NS::Component;
        using Handle = void*;
    public:
        SR_NODISCARD bool UseNewSerialization() const noexcept override { return true; }

        void OnEnable() override;
        void OnDisable() override;

        void OnMatrixDirty() override;
        void OnAttached() override;

        void SetDistanceModel(ListenerDistanceModel distanceModel);
        void SetVelocity(const SR_MATH_NS::FVector3& velocity);
        void SetGain(float_t gain);

    protected:
        void OnDestroy() override;

    private:
        SoundListener* m_listenerContext = nullptr;

        /// @property @setter(SetDistanceModel)
        ListenerDistanceModel m_distanceModel = ListenerDistanceModel::InverseClamped;
        /// @property @setter(SetVelocity)
        SR_MATH_NS::FVector3 m_velocity;
        /// @property @setter(SetGain)
        float_t m_gain = 1.0f;
    };
}

#endif //SR_ENGINE_AUDIOLSTENER_H
