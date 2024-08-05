//
// Created by innerviewer on 10/11/2023.
//

#include <Audio/Impl/OpenALSoundListener.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    void OpenALSoundListener::SetDistanceModel(ListenerDistanceModel distanceModel) {
        auto&& pOpenALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (!pOpenALDevice) {
            SR_ERROR("OpenALSoundListener::SetDistanceModel() : invalid device!");
            return;
        }

        if (!SR_ALC_CALL(alDistanceModel, pOpenALDevice, DistanceModelToALDistanceModel(distanceModel))) {
            SR_ERROR("OpenALListenerContext::SetDistanceModel() : failed to set distance model!");
            return;
        }

        Super::SetDistanceModel(distanceModel);
    }

    bool OpenALSoundListener::Init() {
        /*SetDistanceModel(ListenerDistanceModel::InverseClamped);
        SetRolloffFactor(1.0f);
        SetReferenceDistance(1.0f);
        SetMaxDistance(SR_FLOAT_MAX);*/

        return true;
    }

    bool OpenALSoundListener::Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) {
        SR_MATH_NS::FVector3 up = SR_MATH_NS::FVector3::Up();
        SR_MATH_NS::FVector3 forward = -SR_MATH_NS::FVector3::Forward();

        up = quaternion * up;
        forward = quaternion * forward;

        m_data.position = position;
        m_data.orientation = SR_MATH_NS::FVector6(forward, up);

        if (!SR_AL_CALL(alListenerfv, AL_POSITION, FV3ToALV3(position).vec3)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set listener position!");
            return false;
        }

        if (!SR_AL_CALL(alListenerfv, AL_ORIENTATION, FV6ToALV6(SR_MATH_NS::FVector6(forward, up)).vec6)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set orientation!");
            return false;
        }

        return true;
    }

    ListenerDistanceModel OpenALSoundListener::GetDistanceModel() const noexcept {
        auto&& pOpenALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();
        ALenum distanceModel;
        SR_ALC_CALL(alGetIntegerv, pOpenALDevice, AL_DISTANCE_MODEL, &distanceModel);
        return ALDistanceModelToDistanceModel(distanceModel);
    }

    SR_MATH_NS::FVector3 OpenALSoundListener::GetVelocity() const noexcept {
        SR_MATH_NS::FVector3 velocity;
        SR_AL_CALL(alGetListener3f, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
        return velocity;
    }

    SR_MATH_NS::FVector3 OpenALSoundListener::GetPosition() const noexcept {
        SR_MATH_NS::FVector3 position;
        SR_AL_CALL(alGetListener3f, AL_POSITION, &position.x, &position.y, &position.z);
        return position;
    }

    SR_MATH_NS::FVector6 OpenALSoundListener::GetOrientation() const noexcept {
        SR_MATH_NS::FVector6 orientation;
        SR_AL_CALL(alGetListenerfv, AL_ORIENTATION, &orientation.x);
        return orientation;
    }

    float_t OpenALSoundListener::GetGain() const noexcept {
        float_t gain = 0.0f;
        SR_AL_CALL(alGetListenerf, AL_GAIN, &gain);
        return gain;
    }

    void OpenALSoundListener::SetVelocity(SR_MATH_NS::FVector3 velocity) {
        if (!SR_AL_CALL(alListenerfv, AL_VELOCITY, FV3ToALV3(velocity).vec3)) {
            SR_ERROR("OpenALListenerContext::SetVelocity() : failed to set velocity!");
            return;
        }

        Super::SetVelocity(velocity);
    }

    void OpenALSoundListener::SetGain(float_t gain) {
        if (!SR_AL_CALL(alListenerf, AL_GAIN, gain)) {
            SR_ERROR("OpenALListenerContext::SetDopplerFactor() : failed to set gain!");
            return;
        }

        Super::SetGain(gain);
    }
}