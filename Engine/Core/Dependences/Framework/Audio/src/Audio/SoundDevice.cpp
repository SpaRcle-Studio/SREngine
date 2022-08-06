//
// Created by Monika on 08.07.2022.
//

#include <Audio/SoundDevice.h>

#include <Audio/Impl/OpenALDevice.h>

namespace SR_AUDIO_NS {
    SoundDevice::SoundDevice(AudioLibrary library)
        : m_library(library)
    { }

    SoundDevice* SoundDevice::Allocate(AudioLibrary audioLibrary) {
        SR_LOG("SoundDevice::Allocate() : allocating a sound device...");

        switch (audioLibrary) {
            case AudioLibrary::OpenAL:
                return new OpenALDevice(audioLibrary);
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