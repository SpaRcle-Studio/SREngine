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
        bool async = true;
        bool loop = false;
        AudioLibrary library = AudioLibrary::OpenAL;
        float_t relative = 360.f;
        float_t gain = 1.f;
        float_t minGain = 0.f;
        float_t maxGain = 1.f;
        float_t coneInnerAngle = 360.f;
        uint64_t uniqueId = 0;
        SR_MATH_NS::FVector3 m_position;
        SR_MATH_NS::FVector3 m_direction;
        SR_MATH_NS::FVector3 m_velocity;
        SR_MATH_NS::FVector3 m_pitch;
        SR_MATH_NS::FVector6 m_orientation;
        std::string device;
    };
}

#endif //SRENGINE_PLAYPARAMS_H
