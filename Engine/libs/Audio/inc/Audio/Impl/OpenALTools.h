//
// Created by Monika on 09.07.2022.
//

#ifndef SR_ENGINE_OPENALTOOLS_H
#define SR_ENGINE_OPENALTOOLS_H

#include <Audio/ListenerData.h>
#include <Audio/SoundManager.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace SR_AUDIO_NS {
    typedef struct ALfVec3 { ALfloat vec3[3]; } ALfVec3;
    typedef struct ALfVec6 { ALfloat vec6[6]; } ALfVec6;

    /*bool get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device)
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
    }*/

    ListenerDistanceModel ALDistanceModelToDistanceModel(ALenum distanceModel);
    ALenum DistanceModelToALDistanceModel(ListenerDistanceModel distanceModel);

    SR_MAYBE_UNUSED ALfVec6 FV6ToALV6(const SR_MATH_NS::FVector6& vector6);
    SR_MAYBE_UNUSED ALfVec3 FV3ToALV3(const SR_MATH_NS::FVector3& vector3);

    void CheckThreadId(const char* filename, std::uint_fast32_t line);

    //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
    bool check_alc_errors(const std::string& filename, std::uint_fast32_t line, ALCdevice* device);
    bool check_al_errors(const std::string& filename, std::uint_fast32_t line);

    template<typename alFunction, typename... Params> auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alFunction function,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, decltype(function(params...))>
    {
        CheckThreadId(filename, line);
        auto ret = function(std::forward<Params>(params)...);
        check_al_errors(filename, line);
        return ret;
    }

    template<typename alFunction, typename... Params> auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alFunction function,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
    {
        CheckThreadId(filename, line);
        function(std::forward<Params>(params)...);
        return check_al_errors(filename, line);
    }

    template<typename alcFunction, typename... Params> auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void,decltype(function(params...))>,bool>
    {
        CheckThreadId(filename, line);
        function(std::forward<Params>(params)...);
        return check_alc_errors(filename,line,device);
    }

    template<typename alcFunction, typename ReturnType, typename... Params> auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        ReturnType& returnValue,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void,decltype(function(params...))>,bool>
    {
        CheckThreadId(filename, line);
        returnValue = function(std::forward<Params>(params)...);
        return check_alc_errors(filename,line,device);
    }
}

#define SR_ALC_CALL(function, device, ...) SR_AUDIO_NS::alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)
#define SR_AL_CALL(function, ...) SR_AUDIO_NS::alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

#endif //SR_ENGINE_OPENALTOOLS_H
