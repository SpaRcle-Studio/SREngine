//
// Created by Monika on 07.07.2022.
//

#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Audio/SoundDevice.h>
#include <Audio/SoundContext.h>

namespace SR_AUDIO_NS {
    void SoundManager::OnSingletonDestroy() {
        m_state = State::Stopped;

        if (m_thread && m_thread->Joinable()) {
            m_thread->Join();
        }

        Singleton::OnSingletonDestroy();
    }

    void SoundManager::InitSingleton() {
        SRAssert(!m_thread);

        m_state = State::Active;

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([this]() {
            while (m_state != State::Stopped) {
                while (m_state == State::Paused);
                Update();
            }
        });

        Singleton::InitSingleton();
    }

    void SoundManager::Update() {
        SR_LOCK_GUARD

        for (auto pIt = m_playStack.begin(); pIt != m_playStack.end(); ) {
            auto&& playData = *pIt;

            if (!PrepareData(playData) || !PlayInternal(playData)) {
                pIt = m_playStack.erase(pIt);
            }
            else {
                ++pIt;
            }
        }
    }

    bool SoundManager::PrepareData(PlayData &playData) {
        if (playData.pData->initialized) {
            return true;
        }

        auto&& pDevice = SoundDevice::Allocate(playData.params.library);

        if (!pDevice) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate sound device!");
            return false;
        }

        if (!pDevice->Init()) {
            SR_ERROR("SoundManager::PrepareData() : failed to initialize sound device!");
            delete pDevice;
            return false;
        }

        if (!(playData.pContext = SoundContext::Allocate(pDevice))) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate sound context!");
            return false;
        }

        if (!playData.pContext->Init()) {
            SR_ERROR("SoundManager::PrepareData() : failed to initialize sound context!");
            return false;
        }

        auto&& data = (void*)playData.pSound->GetBufferData();
        auto&& dataSize = playData.pSound->GetBufferSize();
        auto&& sampleRate = playData.pSound->GetSampleRate();
        auto&& format = CalculateSoundFormat(playData.pSound->GetChannels(), playData.pSound->GetBitsPerSample());

        if (!(playData.pBuffer = playData.pContext->AllocateBuffer(data, dataSize, sampleRate, format))) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate buffer!");
            return false;
        }

        if (!(playData.pSource = playData.pContext->AllocateSource(playData.pBuffer))) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate source!");
            return false;
        }

        playData.pContext->Play(playData.pSource);

        playData.pData->initialized = true;

        return true;
    }

    bool SoundManager::PlayInternal(PlayData &playData) {
        return true;
    }

    bool SoundManager::Play(Sound* pSound, const PlayParams &params) {
        if (!pSound) {
            SR_ERROR("SoundManager::Play() : sound is nullptr!");
            return false;
        }

        ///// синхронно добавляем звук в стек
        {
            SR_LOCK_GUARD

            if (m_playStack.size() >= 256) {
                SR_WARN("SoundManager::Play() : stack overflow!");
                return false;
            }

            PlayData playData = { 0 };

            playData.pSound = pSound;
            playData.pData = pSound->GetData();
            playData.params = params;

            pSound->AddUsePoint();

            m_playStack.emplace_back(playData);
        }

        while (!params.async && IsPlaying(pSound, params.uniqueId));

        return true;
    }

    bool SoundManager::IsPlaying(Sound* pSound, uint64_t uniqueId) const {
        SR_LOCK_GUARD

        //for (auto&& playData : m_soundStack) {
        //    if (playData.pSound == pSound && playData.params.uniqueId) {
        //        return true;
        //    }
        //}

        return true;
    }

    SoundData* SoundManager::Register(Sound *pSound) {
        if (!pSound) {
            SR_ERROR("SoundManager::Register() : sound is nullptr!");
            return nullptr;
        }

        pSound->AddUsePoint();

        auto&& soundData = new SoundData();

        soundData->pSound = pSound;

        return soundData;
    }

    bool SoundManager::Unregister(SoundData** pSoundData) {
        if (!pSoundData || !(*pSoundData) || !(*pSoundData)->pSound) {
            SR_ERROR("SoundManager::Unregister() : sound data is invalid!");
            return false;
        }

        (*pSoundData)->pSound->RemoveUsePoint();

        delete *pSoundData;

        (*pSoundData) = nullptr;

        return true;
    }
}
