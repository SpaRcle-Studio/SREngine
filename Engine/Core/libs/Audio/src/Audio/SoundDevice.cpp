//
// Created by Monika on 08.07.2022.
//

#include <Audio/SoundDevice.h>

#include <Audio/Impl/OpenALDevice.h>

namespace SR_AUDIO_NS {
    SoundDevice::SoundDevice(AudioLibrary library, const std::string& name)
        : m_library(library)
        , m_name(name)
    { }

    SoundDevice* SoundDevice::Allocate(AudioLibrary audioLibrary, const std::string& name) {
        if (name.empty()) {
            SR_LOG("SoundDevice::Allocate() : allocating a sound device...");
        }
        else {
            SR_LOG("SoundDevice::Allocate() : allocating a sound device with name \"" + name + "\"...");
        }

        switch (audioLibrary) {
            case AudioLibrary::OpenAL:
                return new OpenALDevice(audioLibrary, name);
            case AudioLibrary::FMOD:
            case AudioLibrary::Wwise:
            case AudioLibrary::Allegro:
            case AudioLibrary::SoLoud:
            case AudioLibrary::Unknown:
            default:
                SR_ERROR("SoundDevice::Allocate() : the audio library is not supported!");
                break;
        }

        return nullptr;
    }

    std::string SoundDevice::GetName() const {
        return m_name;
    }

    AudioLibrary SoundDevice::GetLibrary() const {
        return m_library;
    }
}