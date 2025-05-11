//
// Created by Monika on 08.07.2022.
//

#include <alext.h>
#include <Audio/PlayParams.h>
#include <Audio/Impl/OpenALSoundContext.h>
#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    OpenALSoundContext::OpenALSoundContext(SoundDevice *pDevice)
        : SoundContext(pDevice)
    { }

    OpenALSoundContext::~OpenALSoundContext() {
        auto&& openALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (m_openALContext && openALDevice) {
            ALCboolean contextMadeCurrent = ALC_TRUE;
            SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
            SR_ALC_CALL(alcDestroyContext, openALDevice, m_openALContext);
            m_openALContext = nullptr;
        }
    }

    bool OpenALSoundContext::Init() {
        auto&& openALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (!openALDevice) {
            SR_ERROR("OpenALContext::Init() : invalid device!");
            return false;
        }

        if(!SR_ALC_CALL(alcCreateContext, m_openALContext, openALDevice, openALDevice, nullptr) || !m_openALContext) {
            SR_ERROR("OpenALContext::Init() : failed to create audio context!");
            return false;
        }

        if (!MakeContextCurrent()) {
            SR_ERROR("OpenALContext::Init() : failed to make context current!");
            return false;
        }

        return true;
    }

    SoundSource OpenALSoundContext::AllocateSource(SoundBuffer buffer) {
        ALuint* alSource = new ALuint();
        ALuint* alBuffer = reinterpret_cast<ALuint*>(buffer);

        SR_AL_CALL(alGenSources, 1, alSource);
        SR_AL_CALL(alSourcei, *alSource, AL_BUFFER, *alBuffer);

        return reinterpret_cast<void*>(alSource);
    }

    PlayParams OpenALSoundContext::GetSourceParams(SoundSource pSource) const {
        SR_TRACY_ZONE;

        PlayParams params;

        /// SR_AL_CALL(alGetSourcei, *(ALuint*)pSource, AL_LOOPING, &params.loop.value());

        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_PITCH, &params.pitch.value());
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_GAIN, &params.gain.value());
        SR_AL_CALL(alGetSource3f, *(ALuint*)pSource, AL_POSITION, &params.position.value().x, &params.position.value().y, &params.position.value().z);
        SR_AL_CALL(alGetSource3f, *(ALuint*)pSource, AL_VELOCITY, &params.velocity.value().x, &params.velocity.value().y, &params.velocity.value().z);
        SR_AL_CALL(alGetSource3f, *(ALuint*)pSource, AL_DIRECTION, &params.direction.value().x, &params.direction.value().y, &params.direction.value().z);
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_CONE_INNER_ANGLE, &params.coneInnerAngle.value());
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_MAX_DISTANCE, &params.maxDistance.value());
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_MIN_GAIN, &params.minGain.value());
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_MAX_GAIN, &params.maxGain.value());
        SR_AL_CALL(alGetSourcefv, *(ALuint*)pSource, AL_ORIENTATION, &params.orientation.value().x);
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_REFERENCE_DISTANCE, &params.referenceDistance.value());
        SR_AL_CALL(alGetSourcef, *(ALuint*)pSource, AL_ROLLOFF_FACTOR, &params.rolloffFactor.value());

        ALint spatialize = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALuint*)pSource, AL_SOURCE_SPATIALIZE_SOFT, &spatialize);
        switch (spatialize) {
            case AL_FALSE: params.spatialize = SpatializeMode::Off; break;
            case AL_TRUE: params.spatialize = SpatializeMode::On; break;
            default: params.spatialize = SpatializeMode::Auto; break;
        }

        return params;
    }

    SoundBuffer OpenALSoundContext::AllocateBuffer(void *data, uint64_t dataSize, int32_t sampleRate, SoundFormat format) {
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

    bool OpenALSoundContext::FreeBuffer(SoundBuffer* buffer) {
        ALuint* alBuffer = reinterpret_cast<ALuint*>(*buffer);

        SR_AL_CALL(alDeleteBuffers, 1, alBuffer);

        delete alBuffer;
        (*buffer) = nullptr;

        return true;
    }

    void OpenALSoundContext::Play(SoundSource source) {
        ALuint* alSource = reinterpret_cast<ALuint*>(source);

        alSourcePlay(*alSource);
    }

    bool OpenALSoundContext::MakeContextCurrent() {
        auto&& openALDevice = dynamic_cast<OpenALDevice*>(GetDevice())->GetALDevice();

        if (!openALDevice) {
            SR_ERROR("OpenALContext::Init() : invalid device!");
            return false;
        }

        ALCboolean contextMadeCurrent = ALC_FALSE;
        if(!SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, m_openALContext) || contextMadeCurrent != ALC_TRUE) {
            SR_ALC_CALL(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
            SR_ALC_CALL(alcDestroyContext, openALDevice, m_openALContext);
            m_openALContext = nullptr;
            SR_ERROR("OpenALSoundContext::MakeContextCurrent() : failed to make audio context current!");
            return false;
        }

        return true;
    }

    void OpenALSoundContext::ApplyParamImpl(SoundSource pSource, PlayParamType paramType, const void* pValue) {
        ALuint* alSource = reinterpret_cast<ALuint*>(pSource);

        //alSourcei(*alSource, AL_DISTANCE_MODEL, AL_INVERSE_DISTANCE_CLAMPED);

        switch (paramType) {
            case PlayParamType::Pitch:
                SR_AL_CALL(alSourcef, *alSource, AL_PITCH, *(float_t*)pValue);
                break;
            case PlayParamType::Gain:
                SR_AL_CALL(alSourcef, *alSource, AL_GAIN, *(float_t*)pValue);
                break;
            case PlayParamType::Loop:
                SR_AL_CALL(alSourcei, *alSource, AL_LOOPING, *(bool*)pValue ? AL_TRUE : AL_FALSE);
                break;
            case PlayParamType::Position:
                SR_AL_CALL(alSource3f, *alSource, AL_POSITION, ((SR_MATH_NS::FVector3*)pValue)->x, ((SR_MATH_NS::FVector3*)pValue)->y, ((SR_MATH_NS::FVector3*)pValue)->z);
                break;
            case PlayParamType::Velocity:
                SR_AL_CALL(alSource3f, *alSource, AL_VELOCITY, ((SR_MATH_NS::FVector3*)pValue)->x, ((SR_MATH_NS::FVector3*)pValue)->y, ((SR_MATH_NS::FVector3*)pValue)->z);
                break;
            case PlayParamType::Direction:
                SR_AL_CALL(alSource3f, *alSource, AL_DIRECTION, ((SR_MATH_NS::FVector3*)pValue)->x, ((SR_MATH_NS::FVector3*)pValue)->y, ((SR_MATH_NS::FVector3*)pValue)->z);
                break;
            case PlayParamType::ConeInnerAngle:
                SR_AL_CALL(alSourcef, *alSource, AL_CONE_INNER_ANGLE, *(float_t*)pValue);
                break;
            case PlayParamType::MaxDistance:
                SR_AL_CALL(alSourcef, *alSource, AL_MAX_DISTANCE, *(float_t*)pValue);
                break;
            //case PlayParamType::ConeOuterAngle:
            //    SR_AL_CALL(alSourcef, *alSource, AL_CONE_OUTER_ANGLE, *(float_t*)pValue);
            //    break;
            //case PlayParamType::ConeOuterGain:
            //    SR_AL_CALL(alSourcef, *alSource, AL_CONE_OUTER_GAIN, *(float_t*)pValue);
            //    break;
            case PlayParamType::MinGain:
                SR_AL_CALL(alSourcef, *alSource, AL_MIN_GAIN, *(float_t*)pValue);
                break;
            case PlayParamType::MaxGain:
                SR_AL_CALL(alSourcef, *alSource, AL_MAX_GAIN, *(float_t*)pValue);
                break;
            case PlayParamType::Orientation:
                SR_AL_CALL(alSourcefv, *alSource, AL_ORIENTATION, (float_t*)pValue);
                break;
            case PlayParamType::ReferenceDistance:
                SR_AL_CALL(alSourcef, *alSource, AL_REFERENCE_DISTANCE, *(float_t*)pValue);
                break;
            case PlayParamType::RolloffFactor:
                SR_AL_CALL(alSourcef, *alSource, AL_ROLLOFF_FACTOR, *(float_t*)pValue);
                break;
            case PlayParamType::Spatialize: {
                switch (*(SpatializeMode*)pValue) {
                    case SpatializeMode::Off:
                        SR_AL_CALL(alSourcei, *alSource, AL_SOURCE_SPATIALIZE_SOFT, AL_FALSE);
                        break;
                    case SpatializeMode::On:
                        SR_AL_CALL(alSourcei, *alSource, AL_SOURCE_SPATIALIZE_SOFT, AL_TRUE);
                        break;
                    case SpatializeMode::Auto:
                        SR_AL_CALL(alSourcei, *alSource, AL_SOURCE_SPATIALIZE_SOFT, AL_AUTO_SOFT);
                        break;
                    default:
                        SR_ERROR("OpenALContext::ApplyParamImpl() : unsupported spatialize mode \"{}\"!", SR_UTILS_NS::EnumReflector::ToStringAtom(*(SpatializeMode*)pValue).c_str());
                        break; // (кирпич)
                }
                break;
            }
            default:
                //SR_ERROR("OpenALContext::ApplyParamImpl() : unsupported param type \"{}\"!", SR_UTILS_NS::EnumReflector::ToStringAtom(paramType).c_str());
                break; // (кирпич)

        }

        //SR_AL_CALL(alSource3f, *alSource, AL_POSITION, 0, 0, 0);
        //SR_AL_CALL(alSource3f, *alSource, AL_VELOCITY, 0, 0, 0);
    }

    bool OpenALSoundContext::IsPlaying(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    bool OpenALSoundContext::IsPaused(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_PAUSED;
    }

    bool OpenALSoundContext::IsStopped(SoundSource pSource) const {
        ALint state = AL_INVALID;
        SR_AL_CALL(alGetSourcei, *(ALint*)pSource, AL_SOURCE_STATE, &state);
        return state == AL_STOPPED;
    }

    bool OpenALSoundContext::FreeSource(SoundSource* pSource) {
        ALuint* alSource = reinterpret_cast<ALuint*>(*pSource);

        SR_AL_CALL(alDeleteSources, 1, alSource);

        delete alSource;
        (*pSource) = nullptr;

        return true;
    }
}