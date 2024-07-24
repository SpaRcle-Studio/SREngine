//
// Created by Monika on 07.07.2022.
//

#ifndef SR_ENGINE_SOUNDMANAGER_H
#define SR_ENGINE_SOUNDMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

#include <Audio/ListenerData.h>
#include <Audio/PlayParams.h>

namespace SR_AUDIO_NS {
    class Sound;
    class SoundDevice;
    class SoundData;
    class SoundContext;
    class SoundListener;

    using AudioDeviceName = std::string;

    struct PlayData : public SR_UTILS_NS::NonCopyable {
        Sound* pSound = nullptr;
        SoundData* pData = nullptr;
        SoundSource pSource = nullptr;
        PlayParams params;
        float_t offset = 0.f;
        bool isPlaying = false;
        bool isFailed = false;
    };

    class SoundManager : public SR_UTILS_NS::Singleton<SoundManager> {
        SR_REGISTER_SINGLETON(SoundManager)
    public:
        enum class State : uint8_t {
            Stopped, Active, Paused
        };
        using Handle = void*;
    private:
        SoundManager() = default;
        ~SoundManager() override = default;

    public:
        void StopAll();

        SR_NODISCARD std::optional<PlayParams> GetSourceParams(const PlayData* pPlayData) const;
        SR_NODISCARD std::optional<ListenerData> GetListenerParams(const SoundListener* pListener) const;

        Handle Play(const std::string& path);
        Handle Play(const std::string& path, const PlayParams& params);
        Handle Play(Sound* pSound, const PlayParams& params);

        bool IsExists(Handle pHandle) const;
        bool IsPlaying(Handle pHandle) const;
        bool IsInitialized(Handle pHandle) const;
        bool IsFailed(Handle pHandle) const;

        void ApplyParams(Handle pHandle, const PlayParams& params);
        void Stop(Handle pHandle);

        SoundData* Register(Sound* pSound);
        bool Unregister(SoundData** pSoundData);

        void SetListenerDistanceModel(SoundListener* pListenerContext, ListenerDistanceModel distanceModel);
        void SetListenerGain(SoundListener* pListenerContext, float_t gain);
        void SetListenerVelocity(SoundListener* pListenerContext, SR_MATH_NS::FVector3 velocity);
        void SetListenerTransform(SoundListener* pListenerContext, const SR_MATH_NS::FVector3& position, const SR_MATH_NS::Quaternion& quaternion);

        SR_NODISCARD const std::set<SoundListener*>& GetListeners() const noexcept { return m_listeners; }
        SR_NODISCARD const std::list<PlayData*>& GetPlayStack() const noexcept { return m_playStack; }

        SR_NODISCARD SR_HTYPES_NS::Thread::ThreadId GetThreadId() const noexcept { return m_threadId; }
        SR_NODISCARD SoundListener* CreateListener();
        SR_NODISCARD SoundListener* CreateListener(AudioLibrary library);
        void DestroyListener(SoundListener* pListener);

    protected:
        SR_NODISCARD SoundContext* GetSoundContext(const PlayParams& params) noexcept;
        SR_NODISCARD AudioLibrary GetRelevantLibrary() const noexcept;

        void DestroyPlayData(PlayData* pPlayData);

        bool PlayInternal(PlayData* pPlayData);
        bool PrepareData(PlayData* pPlayData);

        void InitSingleton() override;
        void OnSingletonDestroy() override;

        void Update();
        void Destroy();

    private:
        void Sleep();

    private:
        std::atomic<SR_HTYPES_NS::Thread::ThreadId> m_threadId = SR_HTYPES_NS::Thread::EmptyThreadId();
        std::set<SoundListener*> m_listeners;
        SR_HTYPES_NS::Thread::Ptr m_thread = nullptr;
        std::atomic<State> m_state = State::Stopped;
        std::list<PlayData*> m_playStack;
        std::set<PlayData*> m_playing;
        std::map<AudioLibrary, std::map<AudioDeviceName, SoundContext*>> m_contexts;

    };
}

#endif //SR_ENGINE_SOUNDMANAGER_H
