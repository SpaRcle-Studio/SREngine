//
// Created by Monika on 09.07.2022.
//

#ifndef SRENGINE_PLAYPARAMS_H
#define SRENGINE_PLAYPARAMS_H

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector6.h>
#include <Audio/AudioLibrary.h>
#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    struct PlayParams {
        std::optional<bool> async;
        std::optional<bool> loop;
        std::optional<AudioLibrary> library;
        std::optional<float_t> relative;
        std::optional<float_t> gain;
        std::optional<float_t> minGain;
        std::optional<float_t> pitch;
        std::optional<float_t> maxGain;
        std::optional<float_t> coneInnerAngle;
        std::optional<uint64_t> uniqueId;
        std::optional<SR_MATH_NS::FVector3> position;
        std::optional<SR_MATH_NS::FVector3> direction;
        std::optional<SR_MATH_NS::FVector3> velocity;
        std::optional<SR_MATH_NS::FVector6> orientation;
        std::optional<std::string> device = "";
    public:
        static PlayParams GetDefault();
    };


}

#endif //SRENGINE_PLAYPARAMS_H
