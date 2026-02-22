//
// Created by Monika on 06.07.2022.
//

#include <Audio/Decoders/IWaveDataProvider.h>
#include <Audio/RawSound.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/FileSystem/FileSystem.h>

#include <Codegen/RawSound.generated.hpp>

namespace SR_AUDIO_NS {
    RawSound::RawSound() = default;

    RawSound::~RawSound() = default;

    bool RawSound::Unload() {
        if (m_dataProvider) {
            m_dataProvider.reset();
        }

        return Super::Unload();
    }

    bool RawSound::Load() {
        bool hasErrors = !Super::Load();

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());
        if (!path.IsAbs()) {
            path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);
        }

        if (!path.Exists(SR_UTILS_NS::Path::Type::File)) {
            SR_ERROR("RawSound::Load() : file not found!\n\tPath: {}", path.ToString());
            return false;
        }

        auto&& dataBlob = SR_UTILS_NS::FileSystem::ReadFileAsBlob(path);
        if (!dataBlob || dataBlob->empty()) {
            SR_ERROR("RawSound::Load() : cannot read file!\n\tPath: {}", path.ToString());
            return false;
        }

        if (!((m_dataProvider = CreateWaveDataProvider(path.CStr(), dataBlob)))) {
            SR_ERROR("RawSound::Load() : cannot parse file!\n\tPath: {}", path.ToString());
            return false;
        }

        if (!m_dataProvider->IsValid()) {
            SR_ERROR("RawSound::Load() : data provider is invalid!\n\tPath: {}", path.ToString());
            return false;
        }

        return !hasErrors;
    }

    bool RawSound::Reload() {
        SR_LOG("RawSound::Reload() : reloading \"{}\" audio...", GetResourceId().ToStringRef());

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