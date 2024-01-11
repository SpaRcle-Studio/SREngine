//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_SOUNDFORMAT_H
#define SR_ENGINE_SOUNDFORMAT_H

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
