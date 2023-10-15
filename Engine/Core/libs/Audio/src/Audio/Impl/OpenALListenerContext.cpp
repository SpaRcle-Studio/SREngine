//
// Created by innerviewer on 10/11/2023.
//

#include <Audio/Impl/OpenALListenerContext.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    void OpenALListenerContext::SetDistanceModel(ListenerDistanceModel distanceModel) {
        if (!SR_AL_CALL(alListenerf, AL_DISTANCE_MODEL, DistanceModelToALDistanceModel(distanceModel))) {
            SR_ERROR("OpenALListenerContext::SetDistanceModel() : failed to set distance model!");
            return;
        }

        ListenerContext::SetDistanceModel(distanceModel);
    }

    void OpenALListenerContext::SetRolloffFactor(float_t rolloffFactor) {
        if (!SR_AL_CALL(alListenerf, AL_ROLLOFF_FACTOR, rolloffFactor)) {
            SR_ERROR("OpenALListenerContext::SetRolloffFactor() : failed to set rolloff factor!");
            return;
        }

        ListenerContext::SetRolloffFactor(rolloffFactor);
    }

    void OpenALListenerContext::SetReferenceDistance(float_t referenceDistance) {
        if (!SR_AL_CALL(alListenerf, AL_REFERENCE_DISTANCE, referenceDistance)) {
            SR_ERROR("OpenALListenerContext::SetReferenceDistance() : failed to set reference distance!");
            return;
        }

        ListenerContext::SetReferenceDistance(referenceDistance);
    }

    void OpenALListenerContext::SetMaxDistance(float_t maxDistance) {
        if (!SR_AL_CALL(alListenerf, AL_MAX_DISTANCE, maxDistance)) {
            SR_ERROR("OpenALListenerContext::SetMaxDistance() : failed to set max distance!");
            return;
        }

        ListenerContext::SetMaxDistance(maxDistance);
    }

    bool OpenALListenerContext::Init() {
        SetDistanceModel(ListenerDistanceModel::InverseDistanceClamped);
        SetRolloffFactor(1.0f);
        SetReferenceDistance(1.0f);
        SetMaxDistance(SR_FLOAT_MAX);

        return true;
    }

    bool OpenALListenerContext::Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) {
        SR_MATH_NS::FVector3 up = { 0.0f, 1.0f, 0.0f };
        SR_MATH_NS::FVector3 forward = { 0.0f, 0.0f, 1.0f };

        up = quaternion * up;
        forward = quaternion * forward;

        if (!SR_AL_CALL(alListenerfv, AL_ORIENTATION, FV6ToALV6(SR_MATH_NS::FVector6(up, forward)).vec6)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set orientation!");
            return false;
        }

        if (!SR_AL_CALL(alListenerfv, AL_POSITION, FV3ToALV3(position).vec3)) {
            SR_ERROR("OpenALListenerContext::Update() : failed to set listener position!");
            return false;
        }

        return true;
    }


}