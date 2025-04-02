

# File SoundData.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**SoundData.h**](SoundData_8h.md)

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


