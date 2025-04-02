

# File AudioLibrary.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**AudioLibrary.h**](AudioLibrary_8h.md)

[Go to the documentation of this file](AudioLibrary_8h.md)


```C++
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
```


