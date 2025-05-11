

# File AudioListener.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Types**](dir_a09ad68eb0a32f84766b81c9859654b8.md) **>** [**AudioListener.h**](AudioListener_8h.md)

[Go to the documentation of this file](AudioListener_8h.md)


```C++
//
// Created by Capitan_Slider on 16.09.2023.
//

#ifndef SR_ENGINE_AUDIOLISTENER_H
#define SR_ENGINE_AUDIOLISTENER_H

#include <Audio/macros.h>

#include <Audio/ListenerData.h>
#include <Utils/ECS/Component.h>

namespace SR_AUDIO_NS
{
    class SoundListener;

    class AudioListener : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
        using Handle = void*;
    public:
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

        ListenerDistanceModel m_distanceModel = ListenerDistanceModel::InverseClamped;
        SR_MATH_NS::FVector3 m_velocity;
        float_t m_gain = 1.0f;
    };
}

#endif //SR_ENGINE_AUDIOLISTENER_H
```


