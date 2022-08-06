//
// Created by Monika on 08.07.2022.
//

#include <Audio/Impl/OpenALDevice.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    OpenALDevice::OpenALDevice(AudioLibrary library)
        : SoundDevice(library)
    { }

    OpenALDevice::~OpenALDevice() {
        if (m_openALDevice) {

            m_openALDevice = nullptr;
        }
    }

    bool OpenALDevice::Init() {
        auto&& deviceName = GetName();

        if(!(m_openALDevice = alcOpenDevice(deviceName.empty() ? nullptr : deviceName.c_str()))) {
            if (deviceName.empty()) {
                SR_ERROR("OpenALDevice::Init() : device not found! \n\tName: " + deviceName);
            }
            else {
                SR_ERROR("OpenALDevice::Init() : no suitable audio device has been found!");
            }
            return false;
        }

        return true;
    }

    ALCdevice *OpenALDevice::GetALDevice() const {
        return m_openALDevice;
    }
}