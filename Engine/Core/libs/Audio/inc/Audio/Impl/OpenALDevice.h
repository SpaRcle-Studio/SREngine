//
// Created by Monika on 08.07.2022.
//

#ifndef SRENGINE_OPENALDEVICE_H
#define SRENGINE_OPENALDEVICE_H

#include <Audio/SoundDevice.h>

class ALCdevice;

namespace SR_AUDIO_NS {
    class OpenALDevice : public SoundDevice {
    public:
        explicit OpenALDevice(AudioLibrary library);
        ~OpenALDevice() override;

    public:
        bool Init() override;

        SR_NODISCARD ALCdevice* GetALDevice() const;

    private:
        ALCdevice* m_openALDevice = nullptr;

    };
}

#endif //SRENGINE_OPENALDEVICE_H
