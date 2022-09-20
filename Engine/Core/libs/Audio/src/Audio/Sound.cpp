//
// Created by Igor on 05/07/2022.
//

#include <Audio/Sound.h>
#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_AUDIO_NS {
    Sound::Sound()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Sound), true /** auto remove */)
    { }

    Sound::~Sound() {
        SetRawSound(nullptr);
    }

    Sound *Sound::Load(const SR_UTILS_NS::Path& rawPath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_UTILS_NS::Path&& path = rawPath.RemoveSubPath(resourceManager.GetResPath());

        if (auto&& pSound = resourceManager.Find<Sound>(path))
            return pSound;

        auto&& pRawSound = RawSound::Load(path);

        if (!pRawSound) {
            SR_ERROR("Sound::Load() : failed to load a raw sound!");
            return nullptr;
        }

        auto&& pSound = new Sound();

        pSound->SetRawSound(pRawSound);
        pSound->SetId(path, false);

        if (!pSound->Reload()) {
            SR_ERROR("Sound::Load() : failed to reload sound!");
            delete pSound;
            return nullptr;
        }

        resourceManager.RegisterResource(pSound);

        return pSound;
    }

    bool Sound::Play(const PlayParams &params) {
        return SoundManager::Instance().Play(this, params);
    }

    bool Sound::Play() {
        PlayParams params = { 0 };
        params.async = false;
        return Play(params);
    }

    bool Sound::PlayAsync() {
        PlayParams params = { 0 };
        params.async = true;
        return Play(params);
    }

    bool Sound::Load() {
        auto&& soundManager = SoundManager::Instance();

        if (!(m_data = soundManager.Register(this))) {
            SR_ERROR("Sound::Load() : failed to register sound!");
            return false;
        }

        return IResource::Load();
    }

    bool Sound::Unload() {
        auto&& soundManager = SoundManager::Instance();

        if (m_data && !soundManager.Unregister(&m_data)) {
            SR_ERROR("Sound::Unload() : failed to unregister sound!");
        }

        return IResource::Unload();
    }

    bool Sound::Reload() {
        SR_LOCK_GUARD

        SR_LOG("Sound::Reload() : reloading \"" + std::string(GetResourceId()) + "\" sound...");

        m_loadState = LoadState::Reloading;

        Unload();
        Load();

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    void Sound::SetRawSound(RawSound *pRawSound) {
        if (m_rawSound && pRawSound) {
            SRHalt0();
            return;
        }

        if (m_rawSound) {
            RemoveDependency(m_rawSound);
        }

        if (pRawSound) {
            AddDependency(pRawSound);
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

    SoundData *Sound::GetData() const {
        return m_data;
    }
}