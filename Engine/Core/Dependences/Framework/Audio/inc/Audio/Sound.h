//
// Created by Igor on 05/07/2022.
//

#ifndef SRENGINE_SOUND_H
#define SRENGINE_SOUND_H


#include <Utils/ResourceManager/IResource.h>

namespace SR_AUDIO_NS {
    class RawSound;

    class Sound : public SR_UTILS_NS::IResource {
    protected:
        Sound();
        ~Sound() override;

        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };

    public:
        static Sound* Load(const SR_UTILS_NS::Path& path);

    protected:
        bool Load() override;
        bool Unload() override;
        bool Reload() override;

    private:
        void SetRawSound(RawSound* pRawSound);

    private:
        RawSound* m_rawSound = nullptr;

    };

}

#endif //SRENGINE_SOUND_H

