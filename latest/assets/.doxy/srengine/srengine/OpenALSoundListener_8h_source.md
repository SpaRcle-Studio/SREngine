

# File OpenALSoundListener.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Impl**](dir_45f97ee406bd7a76126228ed02b235a4.md) **>** [**OpenALSoundListener.h**](OpenALSoundListener_8h.md)

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


