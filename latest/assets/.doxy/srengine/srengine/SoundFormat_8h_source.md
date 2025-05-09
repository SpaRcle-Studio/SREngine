

# File SoundFormat.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**SoundFormat.h**](SoundFormat_8h.md)

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


