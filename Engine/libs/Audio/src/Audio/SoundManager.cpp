//
// Created by Monika on 07.07.2022.
//

#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Audio/SoundDevice.h>
#include <Audio/SoundContext.h>
#include <Audio/SoundListener.h>
#include <Audio/Sound.h>

#include <Utils/Platform/Platform.h>
#include <Utils/Common/Features.h>
#include <Utils/Resources/ResourceManager.h>

#include <Enum/AudioLibrary.hpp>

namespace SR_AUDIO_NS {
    bool SoundManager::SetPaused(Handle pHandle, bool paused) {
        SR_TRACY_ZONE;
        return m_thread && m_thread->Execute([this, pHandle, paused]() {
            for (auto&& pData : m_playStack) {
                if (pData->pHandle == pHandle) {
                    pData->isPaused = paused;
                    if (pData->pSource) {
                        if (paused) {
                            pData->pData->pContext->Pause(pData->pSource);
                        }
                        else {
                            pData->pData->pContext->Play(pData->pSource);
                        }
                    }
                    return true;
                }
            }
            return false;
        });
    }

    bool SoundManager::Seek(Handle pHandle, float_t seconds) {
        SR_TRACY_ZONE;
        if (!std::isfinite(seconds) || seconds < 0.f) {
            return false;
        }
        return m_thread && m_thread->Execute([this, pHandle, seconds]() {
            for (auto&& pData : m_playStack) {
                if (pData->pHandle == pHandle) {
                    const auto bytesPerSecond = static_cast<double_t>(pData->pSound->GetSampleRate()) * pData->pSound->GetChannels() * pData->pSound->GetBitsPerSample() / 8.0;
                    const auto duration = bytesPerSecond > 0.0 ? pData->pSound->GetBufferSize() / bytesPerSecond : 0.0;
                    if (seconds >= duration) {
                        return false;
                    }
                    pData->offset = seconds;
                    return !pData->pSource || pData->pData->pContext->Seek(pData->pSource, seconds);
                }
            }
            return false;
        });
    }

    float_t SoundManager::GetPlaybackPosition(Handle pHandle) const {
        SR_TRACY_ZONE;
        float_t result = 0.f;
        if (m_thread) {
            m_thread->Execute([this, pHandle, &result]() {
                for (auto&& pData : m_playStack) {
                    if (pData->pHandle == pHandle) {
                        result = pData->pSource ? pData->pData->pContext->GetPlaybackPosition(pData->pSource) : pData->offset;
                        return true;
                    }
                }
                return false;
            });
        }
        return result;
    }

    bool SoundManager::IsPaused(Handle pHandle) const {
        return m_thread && m_thread->Execute([this, pHandle]() {
            for (auto&& pData : m_playStack) {
                if (pData->pHandle == pHandle) {
                    return pData->isPaused;
                }
            }
            return false;
        });
    }

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
        SR_TRACY_ZONE;
        SRAssert(!m_thread);

        if (!SR_UTILS_NS::Features::Instance().Enabled("Audio", true)) {
            SR_INFO("SoundManager::InitSingleton() : audio feature is disabled!");
            m_isEnabled = false;
            return;
        }

        m_isEnabled = true;
        m_state = State::Active;

        SR_HTYPES_NS::Thread::Factory::Instance().Create(m_thread, [this]() -> bool {
            if (m_threadId == SR_HTYPES_NS::Thread::EmptyThreadId()) {
                m_threadId = m_thread->GetId();
            }

            if (m_state == State::Stopped) {
                Destroy();
                return false;
            }

            Update();
            return true;
        });
        m_thread->SetName("Sound manager");

        Singleton::InitSingleton();
    }

    void SoundManager::StopAll() {
        SR_TRACY_ZONE;

        if (!m_thread) {
            return;
        }

        m_thread->Execute([this]() {
            for (auto&& pPlayData : m_playStack) {
                DestroyPlayData(pPlayData);
            }
            m_playStack.clear();
            m_playing.clear();
            return true;
        });
    }

    SR_UTILS_NS::Optional<PlayParams> SoundManager::GetSourceParams(const PlayData* pPlayData) const {
        SR_TRACY_ZONE;

        SR_UTILS_NS::Optional<PlayParams> result;

        if (!m_thread) {
            return result;
        }

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

    SR_UTILS_NS::Optional<ListenerData> SoundManager::GetListenerParams(const SoundListener* pListener) const {
        SR_TRACY_ZONE;

        SR_UTILS_NS::Optional<ListenerData> result;

        if (!m_thread) {
            return result;
        }

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
            if (pPlayData->isPaused) {
                pContext->Pause(pPlayData->pSource);
            }
            if (pPlayData->offset > 0.f) {
                pContext->Seek(pPlayData->pSource, pPlayData->offset);
            }

            pPlayData->isPlaying = true;
        }

        return !pPlayData->isFailed;
    }

    SoundManager::Handle SoundManager::Play(Sound* pSound, const PlayParams& params) {
        SR_TRACY_ZONE;

        if (!m_thread) {
            return nullptr;
        }

        if (!pSound) {
            SR_ERROR("SoundManager::Play() : sound is nullptr!");
            return nullptr;
        }

        if (!pSound->GetData()) {
            SRHalt("SoundManager::Play() : sound data is nullptr!");
            return nullptr;
        }

        ///// синхронно добавляем звук в стек
        Handle pHandle = nullptr;
        const bool result = m_thread->Execute([this, &pHandle, pSound, &params]() {
            if (m_playStack.size() >= 256) {
                SR_WARN("SoundManager::Play() : stack overflow!");
                return false;
            }

            auto&& pPlayData = new PlayData();

            pHandle = pPlayData->pHandle = reinterpret_cast<void*>(++m_nextHandleId);

            pPlayData->pSound = pSound;
            pPlayData->pData = pSound->GetData();
            pPlayData->params = params;

            pSound->AddUsePoint();

            m_playStack.emplace_back(pPlayData);
            m_playing.emplace(pPlayData);

            return true;
        });

        if (!result) {
            return nullptr;
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

        if (!m_thread) {
            return false;
        }

        return m_thread->Execute([this, pHandle]() {
            for (auto&& pPlayData : m_playStack) {
                if (pHandle == pPlayData->pHandle) {
                    if (!pPlayData->pData->initialized || !pPlayData->pSource) {
                        return false;
                    }
                    return pPlayData->pData->pContext->IsPlaying(pPlayData->pSource);
                }
            }

            return false;
        });
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

        if (!m_thread) {
            return true;
        }

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

        if (!m_thread) {
            return false;
        }

        return m_thread->Execute([this, pHandle]() {
            for (auto&& pPlayData: m_playStack) {
                if (pHandle == pPlayData->pHandle) {
                    return pPlayData->pData->initialized;
                }
            }

            SRHalt("Handle not found!");

            return false;
        });
    }

    bool SoundManager::IsExists(SoundManager::Handle pHandle) const {
        SR_TRACY_ZONE;

        if (!m_thread || !pHandle) {
            return false;
        }

        return m_thread->Execute([this, pHandle]() {
            for (auto&& pPlayData : m_playStack) {
                if (pHandle == pPlayData->pHandle) {
                    return true;
                }
            }

            return false;
        });
    }

    bool SoundManager::IsFailed(SoundManager::Handle pHandle) const {
        SR_TRACY_ZONE;

        return m_thread->Execute([this, pHandle]() {
            for (auto&& pPlayData: m_playStack) {
                if (pHandle == pPlayData->pHandle) {
                    return pPlayData->isFailed;
                }
            }

            SRHalt("Handle not found!");

            return false;
        });
    }


    SoundContext* SoundManager::GetSoundContext(const PlayParams& params) noexcept {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        AudioLibrary library = params.library.has_value() ? params.library.value() : GetRelevantLibrary();
        const SR_UTILS_NS::String device = params.device.has_value() ? SR_UTILS_NS::String(params.device.value()) : SR_UTILS_NS::String();

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
            SR_INFO("SoundManager::GetSoundContext() : initializing \"{}\" library...", library);
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

    SoundManager::Handle SoundManager::Play(SR_UTILS_NS::StringView path, const PlayParams& params) {
        SR_TRACY_ZONE;

        if (path.empty()) {
            SRHalt("Empty sound path!");
            return nullptr;
        }

        if (auto&& pSound = CoreResLoader::Load<Sound>(SR_UTILS_NS::Path(path))) {
            return pSound->Play(params);
        }

        return nullptr;
    }

    SoundManager::Handle SoundManager::Play(SR_UTILS_NS::StringView path) {
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

        if (!m_thread || !pHandle) {
            return;
        }

        m_thread->Execute([this, pHandle, params]() {
            for (auto&& pPlayData : m_playStack) {
                if (pHandle == pPlayData->pHandle) {
                    pPlayData->params = params;
                    if (!pPlayData->pData->initialized || !pPlayData->pSource) {
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

        if (!m_thread || !pHandle) {
            return;
        }

        m_thread->Execute([this, pHandle]() {
            for (auto pIt = m_playStack.begin(); pIt != m_playStack.end(); ) {
                if (pHandle == (*pIt)->pHandle) {
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

        if (!m_thread) {
            return nullptr;
        }

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

            pListener->SetGlobalGain(m_globalGain.load());

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

    void SoundManager::SetGlobalGain(float_t gain) noexcept {
        SR_TRACY_ZONE;

        if (!m_thread) {
            m_globalGain.store(gain);
            return;
        }

        m_thread->Execute([gain, this]() {
            m_globalGain.store(gain);
            for (auto&& pListener : m_listeners) {
                pListener->SetGlobalGain(gain);
            }
            return true;
        });
    }
}
