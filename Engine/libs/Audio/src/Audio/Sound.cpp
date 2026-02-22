//
// Created by Igor on 05/07/2022.
//

#include <Audio/Sound.h>
#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Audio/RawSound.h>

#include <Utils/Resources/ResourceManager.h>

#include <Codegen/Sound.generated.hpp>

namespace SR_AUDIO_NS {
    Sound::Sound() = default;

    Sound::~Sound() {
        if (m_data && !SoundManager::Instance().Unregister(&m_data)) {
            SR_ERROR("Sound::~Sound() : failed to unregister sound!");
        }
        SetRawSound(nullptr);
    }

    Sound::Handle Sound::Play(const PlayParams& params) {
        return SoundManager::Instance().Play(this, params);
    }

    Sound::Handle Sound::Play() {
        PlayParams params;
        return Play(params);
    }

    bool Sound::Load() {
        if (auto&& pRawSound = CoreResLoader::Load<RawSound>(GetResourceId())) {
            SetRawSound(pRawSound);
        }
        else {
            SR_ERROR("Sound::Load() : failed to load raw sound resource!");
            return false;
        }

        if (!(m_data = SoundManager::Instance().Register(this))) {
            SR_ERROR("Sound::Load() : failed to register sound!");
            return false;
        }

        return Super::Load();
    }

    bool Sound::Unload() {
        if (m_data && !SoundManager::Instance().Unregister(&m_data)) {
            SR_ERROR("Sound::Unload() : failed to unregister sound!");
        }

        SetRawSound(nullptr);

        return Super::Unload();
    }

    bool Sound::Reload() {
        SR_LOG("Sound::Reload() : reloading \"" + std::string(GetResourceId()) + "\" sound...");

        m_loadState = LoadState::Reloading;

        Unload();
        Load();

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    void Sound::SetRawSound(const RawSound::Ptr& pRawSound) {
        if (m_rawSound && pRawSound) {
            SRHalt0();
            return;
        }

        if (m_rawSound) {
            RemoveDependency(m_rawSound.StaticCast<SR_UTILS_NS::ResourceContainer>());
        }

        if (pRawSound) {
            AddDependency(pRawSound.StaticCast<SR_UTILS_NS::ResourceContainer>());
        }

        m_rawSound = pRawSound;
    }

    const uint8_t *Sound::GetBufferData() const {
        return m_rawSound ? m_rawSound->GetBufferData() : nullptr;
    }

    uint64_t Sound::GetBufferSize() const {
        return m_rawSound ? m_rawSound->GetBufferSize() : 0;
    }

    uint8_t Sound::GetChannels() const {
        return m_rawSound ? m_rawSound->GetChannels() : 0;
    }

    uint8_t Sound::GetBitsPerSample() const {
        return m_rawSound ? m_rawSound->GetBitsPerSample() : 0;
    }

    uint32_t Sound::GetSampleRate() const {
        return m_rawSound ? m_rawSound->GetSampleRate() : 0;
    }

    SoundData* Sound::GetData() const {
        return m_data;
    }

    bool Sound::IsAllowedToRevive() const {
        return true;
    }
}