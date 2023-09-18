//
// Created by Monika on 08.07.2022.
//

#include <Audio/Impl/OpenALDevice.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    OpenALDevice::OpenALDevice(AudioLibrary library, const std::string& name)
        : SoundDevice(library, name)
    { }

    OpenALDevice::~OpenALDevice() {
        if (m_openALDevice) {
            SR_LOG("OpenALDevice::~OpenALDevice() : close device \"" + m_name + "\"");
            alcCloseDevice(m_openALDevice);
            m_openALDevice = nullptr;
        }
    }

    bool OpenALDevice::Init() {
        const ALchar* pDeviceNames = NULL;

        pDeviceNames = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
        while (pDeviceNames && *pDeviceNames)
        {
            if (std::string(pDeviceNames) == m_name || m_name.empty()) {
                break;
            }
            pDeviceNames += strlen(pDeviceNames) + 1;
        }

        if (!pDeviceNames) {
            SR_ERROR("OpenALDevice::Init() : no suitable audio device has been found!");
        }
        else if (m_name.empty()) {
            m_name = pDeviceNames;
        }

        if (!(m_openALDevice = alcOpenDevice(pDeviceNames))) {
            SR_ERROR("OpenALDevice::Init() : failed to open \"" + m_name + "\" device!");
            return false;
        }

        SR_LOG("OpenALDevice::Init() : found device \"" + m_name + "\"");

        return true;
    }

    ALCdevice* OpenALDevice::GetALDevice() const {
        return m_openALDevice;
    }
}