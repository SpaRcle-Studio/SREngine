//
// Created by Monika on 07.07.2022.
//

#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Audio/SoundDevice.h>
#include <Audio/SoundContext.h>
#include <Audio/SoundListener.h>

namespace SR_AUDIO_NS {
    void SoundManager::OnSingletonDestroy() {
        m_state = State::Stopped;

        if (m_thread && m_thread->Joinable()) {
            m_thread->Join();
            m_thread->Free();
            m_thread = nullptr;
        }

        Singleton::OnSingletonDestroy();
    }

    void SoundManager::InitSingleton() {
        SRAssert(!m_thread);

        m_state = State::Active;

        SR_HTYPES_NS::Thread::Factory::Instance().Create(m_thread, [this]() {
            m_threadId = m_thread->GetId();
            while (m_state != State::Stopped) {
                while (m_state == State::Paused) {
                    SR_NOOP;
                }
                Update();
            }
            Destroy();
        });
        m_thread->SetName("Sound manager");

        Singleton::InitSingleton();
    }

    void SoundManager::StopAll() {
        SR_TRACY_ZONE;

        m_thread->Execute([this]() {
            for (auto&& pPlayData : m_playStack) {
                DestroyPlayData(pPlayData);
            }
            return true;
        });

        m_playStack.clear();
        m_playing.clear();
    }

    std::optional<PlayParams> SoundManager::GetSourceParams(const PlayData* pPlayData) const {
        SR_TRACY_ZONE;

        std::optional<PlayParams> result;

        m_thread->Execute([this, &result, pPlayData]() {
            if (m_playing.count(const_cast<PlayData*>(pPlayData)) == 0) {
                return false;
            }

            auto&& pContext = pPlayData->pData->pContext;
            if (!pContext) {
                SR_ERROR("SoundManager::GetSourceParams() : sound context is nullptr!");
                return false;
            }

            if (!pPlayData->pData->initialized || !pPlayData->pSource) {
                return false;
            }

            result = pContext->GetSourceParams(pPlayData->pSource);
            return true;
        });

        return result;
    }

    std::optional<ListenerData> SoundManager::GetListenerParams(const SoundListener* pListener) const {
        SR_TRACY_ZONE;

        std::optional<ListenerData> result;

        m_thread->Execute([this, &result, pListener]() {
            if (m_listeners.count(const_cast<SoundListener*>(pListener)) == 0) {
                return false;
            }
            result = ListenerData();
            result->position = pListener->GetPosition();
            result->orientation = pListener->GetOrientation();
            result->velocity = pListener->GetVelocity();
            result->gain = pListener->GetGain();
            result->distanceModel = pListener->GetDistanceModel();
            return true;
        });

        return result;
    }

    void SoundManager::Update() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        m_thread->Synchronize();

        for (auto pIt = m_playStack.begin(); pIt != m_playStack.end(); ) {
            auto&& pPlayData = *pIt;

            if (!PrepareData(pPlayData) || !PlayInternal(pPlayData)) {
                DestroyPlayData(pPlayData);
                m_playing.erase(pPlayData);
                pIt = m_playStack.erase(pIt);
            }
            else if (pPlayData->pData->pContext->IsStopped(pPlayData->pSource)) {
                DestroyPlayData(pPlayData);
                m_playing.erase(pPlayData);
                pIt = m_playStack.erase(pIt);
            }
            else {
                ++pIt;
            }
        }
    }

    bool SoundManager::PrepareData(PlayData* pPlayData) {
        SR_TRACY_ZONE;

        if (pPlayData->pData->initialized) {
            return true;
        }

        auto&& pContext = pPlayData->pData->pContext = GetSoundContext(pPlayData->params);
        auto&& pSound = pPlayData->pData->pSound;

        if (!pContext) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate sound context!");
            return false;
        }

        auto&& data = (void*)pSound->GetBufferData();
        auto&& dataSize = pSound->GetBufferSize();
        auto&& sampleRate = pSound->GetSampleRate();
        auto&& format = CalculateSoundFormat(pSound->GetChannels(), pSound->GetBitsPerSample());

        auto&& pBuffer = pPlayData->pData->pBuffer = pContext->AllocateBuffer(data, dataSize, sampleRate, format);

        if (!pBuffer) {
            SR_ERROR("SoundManager::PrepareData() : failed to allocate buffer!");
            return false;
        }

        pPlayData->pData->initialized = true;

        return true;
    }

    bool SoundManager::PlayInternal(PlayData* pPlayData) {
        SR_TRACY_ZONE;

        if (!pPlayData->isPlaying) {
            auto&& pContext = pPlayData->pData->pContext;

            if (!((pPlayData->pSource = pContext->AllocateSource(pPlayData->pData->pBuffer)))) {
                SR_ERROR("SoundManager::PlayInternal() : failed to allocate source!");
                return false;
            }

            pContext->ApplyParams(pPlayData->pSource, pPlayData->params);
            pContext->Play(pPlayData->pSource);

            pPlayData->isPlaying = true;
        }

        return !pPlayData->isFailed;
    }

    SoundManager::Handle SoundManager::Play(Sound* pSound, const PlayParams& params) {
        SR_TRACY_ZONE;

        if (!pSound) {
            SR_ERROR("SoundManager::Play() : sound is nullptr!");
            return nullptr;
        }

        ///// синхронно добавляем звук в стек
        Handle pHandle = nullptr;
        {
            SR_LOCK_GUARD;

            if (m_playStack.size() >= 256) {
                SR_WARN("SoundManager::Play() : stack overflow!");
                return nullptr;
            }

            auto&& pPlayData = new PlayData();

            pHandle = pPlayData;

            pPlayData->pSound = pSound;
            pPlayData->pData = pSound->GetData();
            pPlayData->params = params;

            pSound->AddUsePoint();

            m_playStack.emplace_back(pPlayData);
            m_playing.emplace(pPlayData);
        }

        bool async = params.async.has_value() ? params.async.value() : true; /// NOLINT

        while (!async) {
            SR_LOCK_GUARD;

            if (!IsExists(pHandle) || IsFailed(pHandle)) {
                break;
            }

            if (!IsInitialized(pHandle)) {
                continue;
            }

            if (IsPlaying(pHandle)) {
                continue;
            }
        }

        return pHandle;
    }

    bool SoundManager::IsPlaying(Handle pHandle) const {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (auto&& pPlayData : m_playStack) {
            if (pHandle == pPlayData) {
                if (!pPlayData->pData->initialized) {
                    return false;
                }
                return pPlayData->pData->pContext->IsPlaying(pPlayData->pSource);
            }
        }

        return false;
    }

    SoundData* SoundManager::Register(Sound *pSound) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (!pSound) {
            SR_ERROR("SoundManager::Register() : sound is nullptr!");
            return nullptr;
        }

        auto&& soundData = new SoundData();

        soundData->pSound = pSound;

        return soundData;
    }

    bool SoundManager::Unregister(SoundData** pSoundData) {
        SR_TRACY_ZONE;

        return m_thread->Execute([this, pSoundData]() {
            if (!pSoundData || !(*pSoundData) || !(*pSoundData)->pSound) {
                SR_ERROR("SoundManager::Unregister() : sound data is invalid!");
                return false;
            }

            if ((*pSoundData)->pBuffer) {
                (*pSoundData)->pContext->FreeBuffer(&(*pSoundData)->pBuffer);
            }

            delete *pSoundData;

            (*pSoundData) = nullptr;

            return true;
        });
    }

    void SoundManager::SetListenerDistanceModel(SoundListener* pListenerContext, ListenerDistanceModel distanceModel) {
        m_thread->Execute([pListenerContext, distanceModel]() {
            pListenerContext->SetDistanceModel(distanceModel);
            return true;
        });
    }

    void SoundManager::SetListenerGain(SoundListener* pListenerContext, float_t gain) {
        m_thread->Execute([pListenerContext, gain]() {
            pListenerContext->SetGain(gain);
            return true;
        });
    }

    void SoundManager::SetListenerVelocity(SoundListener* pListenerContext, SR_MATH_NS::FVector3 velocity) {
        m_thread->Execute([pListenerContext, velocity]() {
            pListenerContext->SetVelocity(velocity);
            return true;
        });
    }

    void SoundManager::SetListenerTransform(SoundListener* pListenerContext, const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion) {
        m_thread->Execute([pListenerContext, position, quaternion]() {
            pListenerContext->Update(position, quaternion);
            return true;
        });
    }

    void SoundManager::DestroyPlayData(PlayData* pPlayData) {
        SR_TRACY_ZONE;

        auto&& pSoundData = pPlayData->pData;

        if (pSoundData->pSound) {
            pSoundData->pSound->RemoveUsePoint();
        }

        if (pPlayData->pSource) {
            pSoundData->pContext->FreeSource(&pPlayData->pSource);
        }

        delete pPlayData;
    }

    bool SoundManager::IsInitialized(SoundManager::Handle pHandle) const {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (auto&& pPlayData : m_playStack) {
            if (pHandle == pPlayData) {
                return pPlayData->pData->initialized;
            }
        }

        SRHalt("Handle not found!");

        return false;
    }

    bool SoundManager::IsExists(SoundManager::Handle pHandle) const {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (auto&& pPlayData : m_playStack) {
            if (pHandle == pPlayData) {
                return true;
            }
        }

        return false;
    }

    bool SoundManager::IsFailed(SoundManager::Handle pHandle) const {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (auto&& pPlayData : m_playStack) {
            if (pHandle == pPlayData) {
                return pPlayData->isFailed;
            }
        }

        SRHalt("Handle not found!");

        return false;
    }


    SoundContext* SoundManager::GetSoundContext(const PlayParams& params) noexcept {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        AudioLibrary library = params.library.has_value() ? params.library.value() : GetRelevantLibrary();
        auto&& device = params.device.has_value() ? params.device.value() : std::string();

        if (auto&& pLibIt = m_contexts.find(library); pLibIt != m_contexts.end()) {
            auto&& deviceContexts = pLibIt->second;

            if (device.empty() && !deviceContexts.empty()) {
                return deviceContexts.begin()->second;
            }

            if (!device.empty()) {
                if (auto&& pDeviceIt = deviceContexts.find(device); pDeviceIt != deviceContexts.end()) {
                    return pDeviceIt->second;
                }
            }
        }
        else {
            SR_INFO("SoundManager::GetSoundContext() : initializing \"" + SR_UTILS_NS::EnumReflector::ToStringAtom(library).ToStringRef() + "\" library...");
        }

        auto&& pDevice = SoundDevice::Allocate(library, device);
        if (!pDevice) {
            SR_ERROR("SoundManager::GetSoundContext() : failed to allocate sound device!");
            return nullptr;
        }

        if (!pDevice->Init()) {
            SR_ERROR("SoundManager::GetSoundContext() : failed to initialize sound device!");
            delete pDevice;
            return nullptr;
        }

        auto&& pContext = SoundContext::Allocate(pDevice);
        if (!pContext->Init()) {
            SR_ERROR("SoundManager::GetSoundContext() : failed to initialize sound context!");
            delete pContext;
            return nullptr;
        }

        m_contexts[library][pDevice->GetName()] = pContext;

        return pContext;
    }

    void SoundManager::Destroy() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        SR_INFO("SoundManager::Destroy() : destroy all sound libraries...");

        StopAll();

        for (auto&& [libraryType, contexts] : m_contexts) {
            for (auto&& [deviceName, pSoundContext] : contexts) {
                delete pSoundContext;
            }
        }

        m_contexts.clear();
    }

    void SoundManager::Sleep() {
        SR_TRACY_ZONE;
        SR_PLATFORM_NS::Sleep(1);
    }

    SoundManager::Handle SoundManager::Play(const std::string& path, const PlayParams& params) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (path.empty()) {
            SRHalt("Empty sound path!");
            return nullptr;
        }

        if (auto&& pSound = SR_AUDIO_NS::Sound::Load(path)) {
            return pSound->Play(params);
        }

        return nullptr;
    }

    SoundManager::Handle SoundManager::Play(const std::string& path) {
        SR_TRACY_ZONE;
        return Play(path, PlayParams::GetDefault());
    }

    AudioLibrary SoundManager::GetRelevantLibrary() const noexcept {
        if (m_contexts.empty()) {
            return AudioLibrary::OpenAL;
        }

        return m_contexts.begin()->first;
    }

    void SoundManager::ApplyParams(SoundManager::Handle pHandle, const PlayParams& params) {
        SR_TRACY_ZONE;

        m_thread->Execute([this, pHandle, params]() {
            for (auto&& pPlayData : m_playStack) {
                if (pHandle == pPlayData) {
                    if (!pPlayData->pData->initialized) {
                        break;
                    }
                    pPlayData->pData->pContext->ApplyParams(pPlayData->pSource, params);
                    break;
                }
            }
            return true;
        });
    }

    void SoundManager::Stop(Handle pHandle) {
        SR_TRACY_ZONE;

        m_thread->Execute([this, pHandle]() {
            for (auto pIt = m_playStack.begin(); pIt != m_playStack.end(); ) {
                if (pHandle == *pIt) {
                    DestroyPlayData(*pIt);
                    m_playing.erase(*pIt);
                    m_playStack.erase(pIt);
                    break;
                }
                else {
                    ++pIt;
                }
            }
            return true;
        });
    }

    SoundListener* SoundManager::CreateListener() {
        SR_TRACY_ZONE;
        return CreateListener(AudioLibrary::Unknown);
    }

    SoundListener* SoundManager::CreateListener(AudioLibrary audioLibrary) {
        SR_TRACY_ZONE;

        SoundListener* pListener = nullptr;
        m_thread->Execute([&]() {
            if (audioLibrary == AudioLibrary::Unknown) {
                if (m_contexts.empty()) {
                    audioLibrary = GetRelevantLibrary();
                }
                else {
                    audioLibrary = m_contexts.begin()->first;
                }
            }

            PlayParams params = PlayParams::GetDefault();
            params.library = audioLibrary;
            auto&& pSoundContext = GetSoundContext(params);
            if (!pSoundContext) {
                SR_ERROR("SoundManager::CreateListenerContext() : failed to create sound context!");
                return false;
            }

            pListener = pSoundContext->AllocateListener();
            if (!pListener) {
                SR_ERROR("SoundManager::CreateListenerContext() : failed to allocate listener!");
                return false;
            }

            m_listeners.insert(pListener);
            return true;
        });

        return pListener;
    }

    void SoundManager::DestroyListener(SoundListener* pListener) {
        SR_TRACY_ZONE;

        m_thread->Execute([&]() {
            for (auto&& [libraryType, deviceContexts] : m_contexts) {
                for (auto&& [deviceName, pSoundContext] : deviceContexts) {
                    if (pSoundContext->FreeListener(pListener)) {
                        if (m_listeners.erase(pListener) == 0) {
                            SR_ERROR("SoundManager::DestroyListenerContext() : failed to erase listener!");
                            return false;
                        }
                        return true;
                    }
                    SR_ERROR("SoundManager::DestroyListenerContext() : failed to free listener!");
                    return false;
                }
            }
            SR_ERROR("SoundManager::DestroyListenerContext() : listener not found!");
            return false;
        });
    }
}
