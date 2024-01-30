//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_SOUNDDATA_H
#define SR_ENGINE_SOUNDDATA_H

#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    class Sound;
    class SoundManager;

    struct SoundData : public SR_UTILS_NS::NonCopyable {
        SoundContext* pContext = nullptr;
        SoundBuffer pBuffer = nullptr;
        Sound* pSound = nullptr;
        bool initialized = false;
    };
}

#endif //SR_ENGINE_SOUNDDATA_H
