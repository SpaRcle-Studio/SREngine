//
// Created by Monika on 09.07.2022.
//

#ifndef SRENGINE_AUDIOLIBRARY_H
#define SRENGINE_AUDIOLIBRARY_H

#include <Utils/macros.h>

namespace SR_AUDIO_NS {
    enum class AudioLibrary : uint8_t {
        Unknown, OpenAL, FMOD, Wwise, Allegro, SoLoud
    };
}

#endif //SRENGINE_AUDIOLIBRARY_H
