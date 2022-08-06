//
// Created by Monika on 06.07.2022.
//

#include <Audio/RawSound.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Audio/Decoders/IWaveDataProvider.h>

namespace SR_AUDIO_NS {
    RawSound::RawSound()
        : IResource(typeid(RawSound).name(), true /** auto remove */)
    { }

    RawSound::~RawSound() { }

    RawSound *RawSound::Load(const SR_UTILS_NS::Path& rawPath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_UTILS_NS::Path&& path = rawPath.RemoveSubPath(resourceManager.GetResPath());

        if (auto&& pRawSound = resourceManager.Find<RawSound>(path))
            return pRawSound;

        auto&& pRawSound = new RawSound();

        pRawSound->SetId(path, false);

        if (!pRawSound->Reload()) {
            delete pRawSound;
            return nullptr;
        }

        resourceManager.RegisterResource(pRawSound);

        return pRawSound;
    }

    SR_UTILS_NS::Path RawSound::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    bool RawSound::Unload() {
        SR_LOCK_GUARD

        if (m_dataProvider) {
            m_dataProvider.reset();
        }

        return IResource::Unload();
    }

    bool RawSound::Load() {
        SR_LOCK_GUARD

        bool hasErrors = !IResource::Load();

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());
        if (!path.IsAbs()) {
            path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);
        }

        auto&& dataBlob = SR_UTILS_NS::FileSystem::ReadFileAsBlob(path);
        if (!dataBlob || dataBlob->empty())
        {
            SR_ERROR("RawSound::Load() : cannot read file!\n\t" + path.ToString());
            return false;
        }

        if (!(m_dataProvider = CreateWaveDataProvider(path.CStr(), dataBlob)))
        {
            SR_ERROR("RawSound::Load() : cannot parse file!\n\t" + path.ToString());
            return false;
        }

        if (!m_dataProvider->IsValid()) {
            SR_ERROR("RawSound::Load() : data provider is invalid!\n\t" + path.ToString());
            return false;
        }

        return !hasErrors;
    }

    bool RawSound::Reload() {
        SR_LOCK_GUARD

        SR_LOG("RawSound::Reload() : reloading \"" + GetResourceId() + "\" audio...");

        m_loadState = LoadState::Reloading;

        Unload();
        Load();

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    const uint8_t* RawSound::GetBufferData() const {
        if (m_dataProvider) {
            return m_dataProvider.get()->GetWaveData();
        }

        return nullptr;
    }

    uint8_t RawSound::GetChannels() const {
        if (m_dataProvider) {
            return m_dataProvider->GetWaveDataFormat().m_numChannels;
        }

        return 0;
    }

    uint64_t RawSound::GetBufferSize() const {
        if (m_dataProvider) {
            return m_dataProvider->GetWaveDataSize();
        }

        return 0;
    }

    uint32_t RawSound::GetSampleRate() const {
        if (m_dataProvider) {
            return m_dataProvider->GetWaveDataFormat().m_samplesPerSecond;
        }

        return 0;
    }

    uint8_t RawSound::GetBitsPerSample() const {
        if (m_dataProvider) {
            return m_dataProvider->GetWaveDataFormat().m_bitsPerSample;
        }

        return 0;
    }
}