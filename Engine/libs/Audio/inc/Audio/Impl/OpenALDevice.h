//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_OPENALDEVICE_H
#define SR_ENGINE_OPENALDEVICE_H

#include <Audio/SoundDevice.h>

#ifdef SR_EMSCRIPTEN
    struct ALCdevice_struct;
    using SROpenALDeviceHandle = ALCdevice_struct*;
#else
    struct ALCdevice;
    using SROpenALDeviceHandle = ALCdevice*;
#endif

namespace SR_AUDIO_NS {
    class OpenALDevice : public SoundDevice {
    public:
        explicit OpenALDevice(AudioLibrary library, const std::string& name);
        ~OpenALDevice() override;

    public:
        bool Init() override;

        SR_NODISCARD SROpenALDeviceHandle GetALDevice() const;

    private:
        SROpenALDeviceHandle m_openALDevice = nullptr;

    };
}

#endif //SR_ENGINE_OPENALDEVICE_H
