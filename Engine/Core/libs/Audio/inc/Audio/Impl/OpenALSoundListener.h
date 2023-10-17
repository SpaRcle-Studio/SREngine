//
// Created by innerviewer on 10/11/2023.
//

#ifndef SRENGINE_OPENALSOUNDLISTENER_H
#define SRENGINE_OPENALSOUNDLISTENER_H

#include <Audio/SoundListener.h>

namespace SR_AUDIO_NS {
    class OpenALSoundListener : public SoundListener {
        using Super = SoundListener;
    public: /// TODO: AL_VELOCITY, AL_GAIN, AL_CONE_OUTER_GAIN, AL_DOPPLER_FACTOR
        bool Init() override;
        bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) override;

    public:
        void SetDistanceModel(ListenerDistanceModel distanceModel) override;
        void SetRolloffFactor(float_t rolloffFactor) override;
        void SetReferenceDistance(float_t referenceDistance) override;
        void SetMaxDistance(float_t maxDistance) override;
        void SetVelocity(SR_MATH_NS::FVector3 velocity) override;
        void SetDopplerFactor(float_t dopplerFactor) override;
        void SetGain(float_t gain) override;
        void SetOuterConeGain(float_t outerConeGain) override;
    };
}
#endif //SRENGINE_OPENALSOUNDLISTENER_H
