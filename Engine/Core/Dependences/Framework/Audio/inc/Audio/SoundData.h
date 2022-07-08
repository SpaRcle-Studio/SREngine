//
// Created by Monika on 09.07.2022.
//

#ifndef SRENGINE_SOUNDDATA_H
#define SRENGINE_SOUNDDATA_H

#include <Utils/Common/NonCopyable.h>

namespace SR_AUDIO_NS {
    class Sound;
    class SoundManager;

    struct SoundData {
        friend class SoundManager;
    private:
        Sound* pSound = nullptr;
        bool initialized = false;

    };
}

#endif //SRENGINE_SOUNDDATA_H
