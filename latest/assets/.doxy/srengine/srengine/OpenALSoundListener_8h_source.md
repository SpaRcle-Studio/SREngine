

# File OpenALSoundListener.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Impl**](dir_1bd135d85244281d14f19c1ce566dd82.md) **>** [**OpenALSoundListener.h**](OpenALSoundListener_8h.md)

[Go to the documentation of this file](OpenALSoundListener_8h.md)


```C++
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
```


