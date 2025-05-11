

# File SoundData.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**SoundData.h**](SoundData_8h.md)

[Go to the documentation of this file](SoundData_8h.md)


```C++
//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_SOUNDDATA_H
#define SR_ENGINE_SOUNDDATA_H

#include <Audio/SoundFormat.h>

namespace SR_AUDIO_NS {
    class Sound;
    class SoundManager;
    class SoundContext;

    struct SoundData : public SR_UTILS_NS::NonCopyable {
        SoundContext* pContext = nullptr;
        SoundBuffer pBuffer = nullptr;
        Sound* pSound = nullptr;
        bool initialized = false;
    };
}

#endif //SR_ENGINE_SOUNDDATA_H
```


