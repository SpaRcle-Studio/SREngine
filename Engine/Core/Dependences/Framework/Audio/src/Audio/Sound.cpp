//
// Created by Igor on 05/07/2022.
//

#include <Audio/Sound.h>
#include <Audio/SoundManager.h>
#include <Audio/SoundData.h>
#include <Utils/ResourceManager/ResourceManager.h>

/*ALCdevice* openALDevice = alcOpenDevice(nullptr);
if(!openALDevice)
    return 0;

ALCcontext* openALContext;
if(!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr) || !openALContext)
{
    std::cerr << "ERROR: Could not create audio context" << std::endl;
    return 0;
}
ALCboolean contextMadeCurrent = false;
if(!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext)
   || contextMadeCurrent != ALC_TRUE)
{
    std::cerr << "ERROR: Could not make audio context current" << std::endl;
    return 0;
}

std::uint8_t 	channels = m_rawSound->GetChannels();
std::int32_t 	sampleRate = m_rawSound->GetSampleRate();
std::uint8_t 	bitsPerSample = m_rawSound->GetBitsPerSample();

ALuint buffer;
alCall(alGenBuffers, 1, &buffer);

ALenum format;
if(channels == 1 && bitsPerSample == 8)
    format = AL_FORMAT_MONO8;
else if(channels == 1 && bitsPerSample == 16)
    format = AL_FORMAT_MONO16;
else if(channels == 2 && bitsPerSample == 8)
    format = AL_FORMAT_STEREO8;
else if(channels == 2 && bitsPerSample == 16)
    format = AL_FORMAT_STEREO16;
else
{
    std::cerr
            << "ERROR: unrecognised wave format: "
            << channels << " channels, "
            << bitsPerSample << " bps" << std::endl;
    return 0;
}

alCall(alBufferData, buffer, format, m_rawSound->GetBufferData(), m_rawSound->GetBufferSize(), sampleRate);

ALuint source;
alCall(alGenSources, 1, &source);
alCall(alSourcef, source, AL_PITCH, 1);
alCall(alSourcef, source, AL_GAIN, 1.0f);
alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
alCall(alSourcei, source, AL_LOOPING, AL_TRUE);
alCall(alSourcei, source, AL_BUFFER, buffer);

alSourcePlay( source);

ALint state = AL_PLAYING;
float_t offset = 0.f;

while(state == AL_PLAYING)
{
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    alGetSourcef(source, AL_SAMPLE_OFFSET, &offset);
    std::cout << offset << std::endl;
}

alDeleteSources(1, &source);
alDeleteBuffers(1, &buffer);

alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
alcCall(alcDestroyContext, openALDevice, openALContext);

ALCboolean closed;
alcCall(alcCloseDevice, closed, openALDevice, openALDevice);*/

namespace SR_AUDIO_NS {
    Sound::Sound()
        : SR_UTILS_NS::IResource(typeid(Sound).name(), true /** auto remove */)
    { }

    Sound::~Sound() {
        SetRawSound(nullptr);
    }

    Sound *Sound::Load(const SR_UTILS_NS::Path& rawPath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_UTILS_NS::Path&& path = rawPath.RemoveSubPath(resourceManager.GetAudioPath());

        if (auto&& pSound = resourceManager.Find<Sound>(path))
            return pSound;

        auto&& pRawSound = RawSound::Load(path);

        if (!pRawSound) {
            SR_ERROR("Sound::Load() : failed to load raw sound!");
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

        SR_LOG("Sound::Reload() : reloading \"" + GetResourceId() + "\" sound...");

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