//
// Created by Monika on 11.11.2025.
//

#include <Audio/Impl/OpenALTools.h>

namespace SR_AUDIO_NS {
    ALenum DistanceModelToALDistanceModel(ListenerDistanceModel distanceModel) {
        switch (distanceModel) {
            case ListenerDistanceModel::None:
                return AL_NONE;
            case ListenerDistanceModel::Inverse:
                return AL_INVERSE_DISTANCE;
            case ListenerDistanceModel::InverseClamped:
                return AL_INVERSE_DISTANCE_CLAMPED;
            case ListenerDistanceModel::Linear:
                return AL_LINEAR_DISTANCE;
            case ListenerDistanceModel::LinearClamped:
                return AL_LINEAR_DISTANCE_CLAMPED;
            case ListenerDistanceModel::Exponent:
                return AL_EXPONENT_DISTANCE;
            case ListenerDistanceModel::ExponentClamped:
                return AL_EXPONENT_DISTANCE_CLAMPED;
            default:
                SRHalt("DistanceModelToALDistanceModel() : no such distance model;");
                return AL_NONE;
        }
    }

    ListenerDistanceModel ALDistanceModelToDistanceModel(ALenum distanceModel) {
        switch (distanceModel) {
            case AL_NONE:
                return ListenerDistanceModel::None;
            case AL_INVERSE_DISTANCE:
                return ListenerDistanceModel::Inverse;
            case AL_INVERSE_DISTANCE_CLAMPED:
                return ListenerDistanceModel::InverseClamped;
            case AL_LINEAR_DISTANCE:
                return ListenerDistanceModel::Linear;
            case AL_LINEAR_DISTANCE_CLAMPED:
                return ListenerDistanceModel::LinearClamped;
            case AL_EXPONENT_DISTANCE:
                return ListenerDistanceModel::Exponent;
            case AL_EXPONENT_DISTANCE_CLAMPED:
                return ListenerDistanceModel::ExponentClamped;
            default:
                SRHalt("ALDistanceModelToDistanceModel() : no such distance model;");
                return ListenerDistanceModel::None;
        }
    }

    ALfVec6 FV6ToALV6(const SR_MATH_NS::FVector6& vector6) {
        ALfVec6 vec6 = {vector6.x, vector6.y, vector6.z, vector6.w, vector6.v, vector6.u};
        return vec6;
    }

    ALfVec3 FV3ToALV3(const SR_MATH_NS::FVector3& vector3) {
        ALfVec3 vec3 =  {vector3.x, vector3.y, vector3.z};
        return vec3;
    }

    void CheckThreadId(const char* filename, const std::uint_fast32_t line) {
    #ifdef SR_DEBUG
        SR_HTYPES_NS::Thread::ThreadId currentThreadId = SR_UTILS_NS::GetThisThreadId();
        SR_HTYPES_NS::Thread::ThreadId soundThreadId = SoundManager::Instance().GetThreadId();
        if (currentThreadId != soundThreadId) {
            SRHalt("OpenAL error: {}:{}\n\tOpenAL function called from different thread!\n\tCurrent thread id: {}\n\tSound thread id: {}", filename, line, currentThreadId.c_str(), soundThreadId.c_str());
        }
    #endif
    }

    //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
    bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device) {
        ALCenum error = alcGetError(device);
        if(error != ALC_NO_ERROR) {
            std::string message = "OpenAL context error " + filename + ": " + std::to_string(line) + "\n\tMessage: ";

            switch(error)
            {
                case ALC_INVALID_VALUE:
                    message += "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
                    break;
                case ALC_INVALID_DEVICE:
                    message += "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
                    break;
                case ALC_INVALID_CONTEXT:
                    message += "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
                    break;
                case ALC_INVALID_ENUM:
                    message += "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
                    break;
                case ALC_OUT_OF_MEMORY:
                    message += "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function";
                    break;
                default:
                    message += "UNKNOWN ALC ERROR: " + std::to_string(error);
            }

            SR_ERROR(message);

            return false;
        }
        return true;
    }

    bool check_al_errors(const std::string& filename, const std::uint_fast32_t line) {
        ALenum error = alGetError();
        if(error != AL_NO_ERROR) {
            std::string message = "OpenAL error " + filename + ": " + std::to_string(line) + "\n\tMessage: ";
            switch(error)
            {
                case AL_INVALID_NAME:
                    message += "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
                    break;
                case AL_INVALID_ENUM:
                    message += "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
                    break;
                case AL_INVALID_VALUE:
                    message += "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
                    break;
                case AL_INVALID_OPERATION:
                    message += "AL_INVALID_OPERATION: the requested operation is not valid";
                    break;
                case AL_OUT_OF_MEMORY:
                    message += "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
                    break;
                default:
                    message += "UNKNOWN AL ERROR: " + std::to_string(error);
            }

            SR_ERROR(message);

            return false;
        }
        return true;
    }
}