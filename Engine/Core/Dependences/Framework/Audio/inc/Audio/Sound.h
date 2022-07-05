//
// Created by Igor on 05/07/2022.
//

#ifndef SRENGINE_SOUND_H
#define SRENGINE_SOUND_H


#include <Utils/ResourceManager/IResource.h>

namespace SR_AUDIO_NS {
    class Sound : public SR_UTILS_NS::IResource {

    protected:
        Sound();

        ~Sound() override = default;

        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };

    public:
        static Sound* Load(SR_UTILS_NS::Path path);
    };

}

#endif //SRENGINE_SOUND_H

