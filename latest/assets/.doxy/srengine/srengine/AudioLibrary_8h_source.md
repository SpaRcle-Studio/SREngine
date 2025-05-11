

# File AudioLibrary.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**AudioLibrary.h**](AudioLibrary_8h.md)

[Go to the documentation of this file](AudioLibrary_8h.md)


```C++
//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_AUDIOLIBRARY_H
#define SR_ENGINE_AUDIOLIBRARY_H

#include <Audio/macros.h>

#include <Utils/Common/Enumerations.h>

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(AudioLibrary, uint8_t,
        Unknown, OpenAL, FMOD, Wwise, Allegro, SoLoud
   );
}

#endif //SR_ENGINE_AUDIOLIBRARY_H
```


