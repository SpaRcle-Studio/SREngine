//
// Created by Monika on 08.07.2022.
//

#include <Audio/SoundContext.h>
#include <Audio/Impl/OpenALSoundContext.h>
#include <Audio/Impl/OpenALSoundListener.h>

namespace SR_AUDIO_NS {
    SoundContext::SoundContext(SoundDevice *pDevice)
        : m_device(pDevice)
    { }

    SoundContext::~SoundContext() {
        for (auto&& pListener : m_listeners) {
            delete pListener;
        }

        SR_SAFE_DELETE_PTR(m_device);
    }

    SoundDevice* SoundContext::GetDevice() const {
        return m_device;
    }

    PlayParams PlayParams::GetDefault() {
        PlayParams playParams;

        playParams.async = true;
        playParams.loop = false;
        playParams.library = AudioLibrary::OpenAL;
        playParams.relative = 360.f;
        playParams.gain = 1.f;
        playParams.minGain = 0.f;
        playParams.pitch = 1.f;
        playParams.maxGain = 1.f;
        playParams.coneInnerAngle = 360.f;
        playParams.uniqueId = 0;
        playParams.device = "";

        return playParams;
    }

    void SoundContext::ApplyParams(SoundSource pSource, const PlayParams &params)
    {
        ApplyParam(pSource, params.device, m_params.device, PlayParamType::Device);
        ApplyParam(pSource, params.coneInnerAngle, m_params.coneInnerAngle, PlayParamType::ConeInnerAngle);
        ApplyParam(pSource, params.async, m_params.async, PlayParamType::Async);
        ApplyParam(pSource, params.direction, m_params.direction, PlayParamType::Direction);
        ApplyParam(pSource, params.gain, m_params.gain, PlayParamType::Gain);
        ApplyParam(pSource, params.library, m_params.library, PlayParamType::Library);
        ApplyParam(pSource, params.loop, m_params.loop, PlayParamType::Loop);
        ApplyParam(pSource, params.maxGain, m_params.maxGain, PlayParamType::MaxGain);
        ApplyParam(pSource, params.minGain, m_params.minGain, PlayParamType::MinGain);
        ApplyParam(pSource, params.orientation, m_params.orientation, PlayParamType::Orientation);
        ApplyParam(pSource, params.pitch, m_params.pitch, PlayParamType::Pitch);
        ApplyParam(pSource, params.position, m_params.position, PlayParamType::Position);
        ApplyParam(pSource, params.relative, m_params.relative, PlayParamType::Relative);
        ApplyParam(pSource, params.uniqueId, m_params.uniqueId, PlayParamType::UniqueId);
        ApplyParam(pSource, params.velocity, m_params.velocity, PlayParamType::Velocity);
    }

    SoundContext* SoundContext::Allocate(SoundDevice* pDevice) {
        if (!pDevice) {
            SR_ERROR("SoundContext::Allocate() : the device is nullptr!");
            return nullptr;
        }

        switch (pDevice->GetLibrary()) {
            case AudioLibrary::OpenAL:
                return new OpenALSoundContext(pDevice);
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

    SoundListener* SoundContext::AllocateListener() {
        if (!m_device) {
            SR_ERROR("SoundContext::Allocate() : the device is nullptr!");
            return nullptr;
        }

        auto&& listenerData = ListenerData();

        switch (m_device->GetLibrary()) {
            case AudioLibrary::OpenAL:{
                auto&& pListener = new OpenALSoundListener();
                pListener->SetData(new ListenerData());
                m_listeners.emplace_back(pListener);

                return pListener;
            }
            case AudioLibrary::FMOD:
            case AudioLibrary::Wwise:
            case AudioLibrary::Allegro:
            case AudioLibrary::SoLoud:
            case AudioLibrary::Unknown:
                SR_ERROR("SoundContext::Allocate() : unsupported library!");
        }

        return nullptr;
    }

    bool SoundContext::FreeListener(SoundListener* pListener) {
        for (auto pIt = m_listeners.begin(); pIt != m_listeners.end(); ++pIt ) {
            if (*pIt == pListener) {
                pListener->SetData(nullptr);
                m_listeners.erase(pIt);
                return true;
            }
        }

        return false;
    }
}