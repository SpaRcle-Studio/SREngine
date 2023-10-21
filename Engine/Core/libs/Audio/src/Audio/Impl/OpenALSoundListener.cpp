//
// Created by innerviewer on 10/11/2023.
//

#include <Audio/Impl/OpenALSoundListener.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    void OpenALSoundListener::SetDistanceModel(ListenerDistanceModel distanceModel) {
        if (!SR_AL_CALL(alListenerf, AL_DISTANCE_MODEL, DistanceModelToALDistanceModel(distanceModel))) {
            SR_ERROR("OpenALListenerContext::SetDistanceModel() : failed to set distance model!");
            return;
        }

        Super::SetDistanceModel(distanceModel);
    }

    void OpenALSoundListener::SetRolloffFactor(float_t rolloffFactor) {
        if (!SR_AL_CALL(alListenerf, AL_ROLLOFF_FACTOR, rolloffFactor)) {
            SR_ERROR("OpenALListenerContext::SetRolloffFactor() : failed to set rolloff factor!");
            return;
        }

        Super::SetRolloffFactor(rolloffFactor);
    }

    void OpenALSoundListener::SetReferenceDistance(float_t referenceDistance) {
        if (!SR_AL_CALL(alListenerf, AL_REFERENCE_DISTANCE, referenceDistance)) {
            SR_ERROR("OpenALListenerContext::SetReferenceDistance() : failed to set reference distance!");
            return;
        }

        Super::SetReferenceDistance(referenceDistance);
    }

    void OpenALSoundListener::SetMaxDistance(float_t maxDistance) {
        if (!SR_AL_CALL(alListenerf, AL_MAX_DISTANCE, maxDistance)) {
            SR_ERROR("OpenALListenerContext::SetMaxDistance() : failed to set max distance!");
            return;
        }

        Super::SetMaxDistance(maxDistance);
    }

    bool OpenALSoundListener::Init() {
        SetDistanceModel(ListenerDistanceModel::InverseDistanceClamped);
        SetRolloffFactor(1.0f);
        SetReferenceDistance(1.0f);
        SetMaxDistance(SR_FLOAT_MAX);

        return true;
    }

    bool OpenALSoundListener::Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) {
        SR_MATH_NS::FVector3 up = { 0.0f, 1.0f, 0.0f };
        SR_MATH_NS::FVector3 forward = { 0.0f, 0.0f, -1.0f };

        const SR_MATH_NS::FVector3 pos = position * SR_MATH_NS::FVector3(1.f, 1.f, -1.f);

        up = quaternion * up;
        forward = quaternion * forward;

        if (!SR_AL_CALL(alListenerfv, AL_ORIENTATION, FV6ToALV6(SR_MATH_NS::FVector6(forward, up)).vec6)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set orientation!");
            return false;
        }

        if (!SR_AL_CALL(alListenerfv, AL_POSITION, FV3ToALV3(pos).vec3)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set listener position!");
            return false;
        }

        return true;
    }

    void OpenALSoundListener::SetVelocity(SR_MATH_NS::FVector3 velocity) {
        if (!SR_AL_CALL(alListenerfv, AL_VELOCITY, FV3ToALV3(velocity).vec3)) {
            SR_ERROR("OpenALListenerContext::SetVelocity() : failed to set velocity!");
            return;
        }

        Super::SetVelocity(velocity);
    }

    void OpenALSoundListener::SetDopplerFactor(float_t dopplerFactor) {
        if (!SR_AL_CALL(alListenerf, AL_DOPPLER_FACTOR, dopplerFactor)) {
            SR_ERROR("OpenALListenerContext::SetDopplerFactor() : failed to set doppler factor!");
            return;
        }

        Super::SetDopplerFactor(dopplerFactor);
    }

    void OpenALSoundListener::SetGain(float_t gain) {
        if (!SR_AL_CALL(alListenerf, AL_GAIN, gain)) {
            SR_ERROR("OpenALListenerContext::SetDopplerFactor() : failed to set gain!");
            return;
        }

        Super::SetGain(gain);
    }

    void OpenALSoundListener::SetOuterConeGain(float_t outerConeGain) {
        if (!SR_AL_CALL(alListenerf, AL_CONE_OUTER_GAIN, outerConeGain)) {
            SR_ERROR("OpenALListenerContext::SetOuterConeGain() : failed to set outer cone gain!");
            return;
        }

        Super::SetOuterConeGain(outerConeGain);
    }
}