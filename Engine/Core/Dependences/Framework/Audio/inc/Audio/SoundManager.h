//
// Created by Monika on 07.07.2022.
//

#ifndef SRENGINE_SOUNDMANAGER_H
#define SRENGINE_SOUNDMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

#include <Audio/PlayParams.h>

namespace SR_AUDIO_NS {
    class Sound;
    class SoundDevice;
    class SoundData;
    class SoundContext;

    struct PlayData {
        Sound* pSound = nullptr;
        SoundData* pData = nullptr;
        SoundContext* pContext = nullptr;
        SoundBuffer pBuffer = nullptr;
        SoundSource pSource = nullptr;
        PlayParams params;
        float_t offset = 0.f;
    };

    class SoundManager : public SR_UTILS_NS::Singleton<SoundManager> {
        friend class SR_UTILS_NS::Singleton<SoundManager>;
    public:
        enum class State : uint8_t {
            Stopped, Active, Paused
        };
    private:
        SoundManager() = default;
        ~SoundManager() override = default;

    public:
        bool Play(Sound* pSound, const PlayParams& params);
        bool IsPlaying(Sound* pSound, uint64_t uniqueId) const;

        SoundData* Register(Sound* pSound);
        bool Unregister(SoundData** pSoundData);

    protected:
        bool PlayInternal(PlayData& playData);
        bool PrepareData(PlayData& playData);

        void InitSingleton() override;
        void OnSingletonDestroy() override;

        void Update();

    private:
        SR_HTYPES_NS::Thread::Ptr m_thread = nullptr;
        std::atomic<State> m_state = State::Stopped;
        std::list<PlayData> m_playStack;

    };
}

#endif //SRENGINE_SOUNDMANAGER_H
