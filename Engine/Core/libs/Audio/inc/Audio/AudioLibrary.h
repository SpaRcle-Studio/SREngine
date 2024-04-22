//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_AUDIOLIBRARY_H
#define SR_ENGINE_AUDIOLIBRARY_H

#include <Utils/Common/Enumerations.h>

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(AudioLibrary, uint8_t,
        Unknown, OpenAL, FMOD, Wwise, Allegro, SoLoud
   );
}

#endif //SR_ENGINE_AUDIOLIBRARY_H
