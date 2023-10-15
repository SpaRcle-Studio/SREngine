//
// Created by innerviewer on 10/11/2023.
//

#ifndef SRENGINE_OPENALLISTENERCONTEXT_H
#define SRENGINE_OPENALLISTENERCONTEXT_H

#include <Audio/ListenerContext.h>

namespace SR_AUDIO_NS {
    class OpenALListenerContext : public ListenerContext {
        using Super = ListenerContext;
    public: /// TODO: AL_VELOCITY, AL_GAIN, AL_CONE_OUTER_GAIN, AL_DOPPLER_FACTOR
        bool Init() override;
        bool Update(const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) override;

    public:
        void SetDistanceModel(ListenerDistanceModel distanceModel) override;
        void SetRolloffFactor(float_t rolloffFactor) override;
        void SetReferenceDistance(float_t referenceDistance) override;
        void SetMaxDistance(float_t maxDistance) override;
    };
}
#endif //SRENGINE_OPENALLISTENERCONTEXT_H
