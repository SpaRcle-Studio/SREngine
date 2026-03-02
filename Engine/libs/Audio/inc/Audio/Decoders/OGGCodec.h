//
// Created by Monika on 09.12.2025.
//

#ifndef SR_ENGINE_AUDIO_OGG_CODEC_H
#define SR_ENGINE_AUDIO_OGG_CODEC_H

#include <Audio/stdInclude.h>

#include <Utils/Common/Enumerations.h>

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(OggCodec, uint8_t,
        Unknown,
        Vorbis,
        Opus,
        Flac
    )

    SR_AUDIO_DLL_API extern OggCodec DetectOggCodec(const char* data, size_t size);
    SR_AUDIO_DLL_API extern std::vector<RawSoundData> UnpackOggDataSeparated(const std::string& oggData);
    SR_AUDIO_DLL_API extern RawSoundDataPtr UnpackOggData(const std::string& oggData);
}

#endif //SR_ENGINE_AUDIO_OGG_CODEC_H
