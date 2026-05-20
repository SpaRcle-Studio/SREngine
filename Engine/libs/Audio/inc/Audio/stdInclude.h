//
// Created by Monika on 11.11.2025.
//

#ifndef SR_ENGINE_AUDIO_STD_INCLUDE_H
#define SR_ENGINE_AUDIO_STD_INCLUDE_H

#include <Audio/macros.h>

#include <Utils/stdInclude.h>
#include <Utils/Types/String.h>

namespace SR_AUDIO_NS {
    typedef SR_UTILS_NS::String RawSoundData;
    typedef std::shared_ptr<RawSoundData> RawSoundDataPtr;
}

#endif //SR_ENGINE_AUDIO_STD_INCLUDE_H
