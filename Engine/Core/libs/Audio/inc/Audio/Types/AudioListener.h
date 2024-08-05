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
        SR_REGISTER_NEW_COMPONENT(AudioListener, 1001);
        using Super = SR_UTILS_NS::Component;
        using Handle = void*;
    public:
        AudioListener();

    public:
        void OnEnable() override;
        void OnDisable() override;

        bool InitializeEntity() noexcept override;
        void OnMatrixDirty() override;
        void OnAttached() override;

        void SetDistanceModel(ListenerDistanceModel distanceModel);
        void SetVelocity(const SR_MATH_NS::FVector3& velocity);
        void SetGain(float_t gain);

    protected:
        void OnDestroy() override;

    private:
        SoundListener* m_listenerContext = nullptr;

        ListenerDistanceModel m_distanceModel = ListenerDistanceModel::InverseClamped;
        SR_MATH_NS::FVector3 m_velocity;
        float_t m_gain = 1.0f;
    };
}

#endif //SR_ENGINE_AUDIOLSTENER_H
