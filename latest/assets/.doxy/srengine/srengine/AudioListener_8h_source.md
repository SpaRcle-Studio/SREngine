

# File AudioListener.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Types**](dir_729cedc52027d33bd7afa3f0ac3e6b5f.md) **>** [**AudioListener.h**](AudioListener_8h.md)

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


