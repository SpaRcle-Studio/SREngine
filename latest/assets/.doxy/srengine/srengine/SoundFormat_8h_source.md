

# File SoundFormat.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**SoundFormat.h**](SoundFormat_8h.md)

[Go to the documentation of this file](SoundFormat_8h.md)


```C++
//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_SOUNDFORMAT_H
#define SR_ENGINE_SOUNDFORMAT_H

#include <Audio/macros.h>

#include <Utils/Common/NonCopyable.h>

namespace SR_AUDIO_NS {
    using SoundBuffer = void*;
    using SoundSource = void*;

    enum SoundFormat : uint8_t {
        SR_SOUND_FORMAT_UNKNOWN,
        SR_SOUND_FORMAT_MONO_8,
        SR_SOUND_FORMAT_MONO_16,
        SR_SOUND_FORMAT_STEREO_8,
        SR_SOUND_FORMAT_STEREO_16,
    };

    static SoundFormat CalculateSoundFormat(uint8_t channels, uint8_t bitsPerSample) {
        if (channels == 1 && bitsPerSample == 8) {
            return SR_SOUND_FORMAT_MONO_8;
        }

        if (channels == 1 && bitsPerSample == 16) {
            return SR_SOUND_FORMAT_MONO_16;
        }

        if (channels == 2 && bitsPerSample == 8) {
            return SR_SOUND_FORMAT_STEREO_8;
        }

        if (channels == 2 && bitsPerSample == 16) {
            return SR_SOUND_FORMAT_STEREO_16;
        }

        return SR_SOUND_FORMAT_UNKNOWN;
    }
}

#endif //SR_ENGINE_SOUNDFORMAT_H
```


