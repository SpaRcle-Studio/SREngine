//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_OPENALDEVICE_H
#define SR_ENGINE_OPENALDEVICE_H

#include <Audio/SoundDevice.h>

class ALCdevice;

namespace SR_AUDIO_NS {
    class OpenALDevice : public SoundDevice {
    public:
        explicit OpenALDevice(AudioLibrary library, const std::string& name);
        ~OpenALDevice() override;

    public:
        bool Init() override;

        SR_NODISCARD ALCdevice* GetALDevice() const;

    private:
        ALCdevice* m_openALDevice = nullptr;

    };
}

#endif //SR_ENGINE_OPENALDEVICE_H
