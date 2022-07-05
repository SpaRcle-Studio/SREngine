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

        //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
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

        std::uint8_t 	channels;
        std::int32_t 	sampleRate;
        std::uint8_t 	bitsPerSample;
        ALsizei			dataSize;
        char* rawSoundData = load_wav(path.CStr(), channels, sampleRate, bitsPerSample, dataSize);
        if(rawSoundData == nullptr || dataSize == 0)
        {
            std::cerr << "ERROR: Could not load wav" << std::endl;
            return 0;
        }
        std::vector<char> soundData(rawSoundData, rawSoundData + dataSize);

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

        alCall(alBufferData, buffer, format, soundData.data(), soundData.size(), sampleRate);
        soundData.clear(); // erase the sound in RAM

        ALuint source;
        alCall(alGenSources, 1, &source);
        alCall(alSourcef, source, AL_PITCH, 1);
        alCall(alSourcef, source, AL_GAIN, 1.0f);
        alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
        alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
        alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
        alCall(alSourcei, source, AL_BUFFER, buffer);

        alSourcePlay( source);

        ALint state = AL_PLAYING;

        while(state == AL_PLAYING)
        {
            alGetSourcei(source, AL_SOURCE_STATE, &state);
        }

        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);

        alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
        alcCall(alcDestroyContext, openALDevice, openALContext);

        ALCboolean closed;
        alcCall(alcCloseDevice, closed, openALDevice, openALDevice);
        return NULL;
        //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
    }
}