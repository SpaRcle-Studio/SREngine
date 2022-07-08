//
// Created by Monika on 08.07.2022.
//

#include <Audio/SoundContext.h>
#include <Audio/Impl/OpenALContext.h>

namespace SR_AUDIO_NS {
    SoundDevice *SoundContext::GetDevice() const {
        return m_device;
    }

    SoundContext::SoundContext(SoundDevice *pDevice)
        : m_device(pDevice)
    { }

    SoundContext *SoundContext::Allocate(SoundDevice *pDevice) {
        SR_INFO("SoundContext::Allocate() : allocate sound context...");

        if (!pDevice) {
            SR_ERROR("SoundContext::Allocate() : device is nullptr!");
            return nullptr;
        }

        switch (pDevice->GetLibrary()) {
            case AudioLibrary::OpenAL:
                return new OpenALContext(pDevice);
            case AudioLibrary::FMOD:
            case AudioLibrary::Wwise:
            case AudioLibrary::Allegro:
            case AudioLibrary::SoLoud:
            case AudioLibrary::Unknown:
                SR_ERROR("SoundContext::Allocate() : unsupported library!");
                break;
        }

        return nullptr;
    }
}