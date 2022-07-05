//
// Created by Igor on 05/07/2022.
//

#include <Audio/Sound.h>
#include <Audio/Tools.h>
#include <Audio/Loader.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_AUDIO_NS {
    bool get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device)
    {
        const ALCchar* devices;
        if(!alcCall(alcGetString, devices, device, nullptr, ALC_DEVICE_SPECIFIER))
            return false;

        const char* ptr = devices;

        devicesVec.clear();

        do
        {
            devicesVec.push_back(std::string(ptr));
            ptr += devicesVec.back().size() + 1;
        }
        while(*(ptr + 1) != '\0');

        return true;
    }



    Sound::Sound()
        :SR_UTILS_NS::IResource(typeid(Sound).name(), true /** auto remove */)
    {

    }

    Sound *Sound::Load(SR_UTILS_NS::Path rawPath) {

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::ResourceManager::Instance().GetAudioPath().Concat(rawPath);

        ALCdevice* openALDevice = alcOpenDevice(nullptr);
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

        std::uint8_t channels;
        std::int32_t sampleRate;
        std::uint8_t bitsPerSample;
        std::vector<char> soundData;
        if(!load_wav(path.CStr(), channels, sampleRate, bitsPerSample,
                     reinterpret_cast<ALsizei &>(soundData)))
        {
            std::cerr << "ERROR: Could not load wav" << std::endl;
            return 0;
        }

        ALuint buffer;
        alGenBuffers( 1, &buffer);

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

        alBufferData(buffer, format, soundData.data(), soundData.size(), sampleRate);
        soundData.clear(); // erase the sound in RAM

        ALuint source;
        alGenSources( 1, &source);
        alSourcef( source, AL_PITCH, 1);
        alSourcef( source, AL_GAIN, 1.0f);
        alSource3f( source, AL_POSITION, 0, 0, 0);
        alSource3f( source, AL_VELOCITY, 0, 0, 0);
        alSourcei( source, AL_LOOPING, AL_FALSE);
        alSourcei( source, AL_BUFFER, buffer);

        alSourcePlay( source);

        ALint state = AL_PLAYING;

        while(state == AL_PLAYING)
        {
            alGetSourcei( source, AL_SOURCE_STATE, &state);
        }

        alDeleteSources( 1, &source);
        alDeleteBuffers( 1, &buffer);

        alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
        alcCall(alcDestroyContext, openALDevice, openALContext);

        ALCboolean closed;
        alcCall(alcCloseDevice, closed, openALDevice, openALDevice);
        return nullptr;
    }
}