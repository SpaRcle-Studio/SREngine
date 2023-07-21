//
// Created by Monika on 08.07.2022.
//

#include <Audio/Impl/OpenALContext.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    OpenALContext::OpenALContext(SoundDevice *pDevice)
        : SoundContext(pDevice)
    { }

    OpenALContext::~OpenALContext() {
        auto&& openALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (m_openALContext && openALDevice) {
            ALCboolean contextMadeCurrent = ALC_TRUE;
            SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
            SR_ALC_CALL(alcDestroyContext, openALDevice, m_openALContext);
            m_openALContext = nullptr;
        }
    }

    bool OpenALContext::Init() {
        auto&& openALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (!openALDevice) {
            SR_ERROR("OpenALContext::Init() : invalid device!");
            return false;
        }

        if(!SR_ALC_CALL(alcCreateContext, m_openALContext, openALDevice, openALDevice, nullptr) || !m_openALContext) {
            SR_ERROR("OpenALContext::Init() : failed to create audio context!");
            return false;
        }

        ALCboolean contextMadeCurrent = ALC_FALSE;
        if(!SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, m_openALContext) || contextMadeCurrent != ALC_TRUE) {
            SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
            SR_ALC_CALL(alcDestroyContext, openALDevice, m_openALContext);
            m_openALContext = nullptr;
            SR_ERROR("OpenALContext::Init() : failed to make audio context current!");
            return false;
        }

        return true;
    }

    SoundSource OpenALContext::AllocateSource(SoundBuffer buffer) {
        ALuint* alSource = new ALuint();
        ALuint* alBuffer = reinterpret_cast<ALuint*>(buffer);

        SR_AL_CALL(alGenSources, 1, alSource);
        SR_AL_CALL(alSourcei, *alSource, AL_BUFFER, *alBuffer);

        return reinterpret_cast<void*>(alSource);
    }

    SoundBuffer OpenALContext::AllocateBuffer(void *data, uint64_t dataSize, int32_t sampleRate, SoundFormat format) {
        ALuint* alBuffer = new ALuint();

        SR_AL_CALL(alGenBuffers, 1, alBuffer);

        ALenum alFormat;

        switch (format) {
            case SR_SOUND_FORMAT_MONO_8: alFormat = AL_FORMAT_MONO8; break;
            case SR_SOUND_FORMAT_MONO_16: alFormat = AL_FORMAT_MONO16; break;
            case SR_SOUND_FORMAT_STEREO_8: alFormat = AL_FORMAT_STEREO8; break;
            case SR_SOUND_FORMAT_STEREO_16: alFormat = AL_FORMAT_STEREO16; break;
            default:
                SR_ERROR("OpenALContext::AllocateBuffer() : unsupported audio format!");
                return nullptr;
        }

        SR_AL_CALL(alBufferData, *alBuffer, alFormat, data, dataSize, sampleRate);

        return reinterpret_cast<void*>(alBuffer);
    }

    bool OpenALContext::FreeBuffer(SoundBuffer* buffer) {
        ALuint* alBuffer = reinterpret_cast<ALuint*>(*buffer);

        SR_AL_CALL(alDeleteBuffers, 1, alBuffer);

        delete alBuffer;
        (*buffer) = nullptr;

        return true;
    }

    void OpenALContext::Play(SoundSource source) {
        ALuint* alSource = reinterpret_cast<ALuint*>(source);

        alSourcePlay(*alSource);
    }

    void OpenALContext::ApplyParams(SoundSource pSource, const PlayParams& params) {
        ALuint* alSource = reinterpret_cast<ALuint*>(pSource);

        SR_AL_CALL(alSourcef, *alSource, AL_PITCH, params.pitch);
        SR_AL_CALL(alSourcef, *alSource, AL_GAIN, params.gain);
        SR_AL_CALL(alSource3f, *alSource, AL_POSITION, 0, 0, 0);
        SR_AL_CALL(alSource3f, *alSource, AL_VELOCITY, 0, 0, 0);
        SR_AL_CALL(alSourcei, *alSource, AL_LOOPING, params.loop ? AL_TRUE : AL_FALSE);
    }

    bool OpenALContext::IsPlaying(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    bool OpenALContext::IsPaused(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_PAUSED;
    }

    bool OpenALContext::IsStopped(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_STOPPED;
    }

    bool OpenALContext::FreeSource(SoundSource* pSource) {
        ALuint* alSource = reinterpret_cast<ALuint*>(*pSource);

        SR_AL_CALL(alDeleteSources, 1, alSource);

        delete alSource;
        (*pSource) = nullptr;

        return true;
    }
}