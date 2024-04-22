//
// Created by Capitan_Slider on 30.09.2023.
//

#include <Audio/SoundListener.h>
#include <Audio/Impl/OpenALSoundListener.h>

namespace SR_AUDIO_NS {
    SoundListener* SoundListener::Allocate(SoundDevice* pDevice) {
        if (!pDevice) {
            SR_ERROR("ListenerContext::Allocate() : pDevice is nullptr!");
            return nullptr;
        }

        switch (pDevice->GetLibrary()) {
            case AudioLibrary::OpenAL:
                return new OpenALSoundListener();
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