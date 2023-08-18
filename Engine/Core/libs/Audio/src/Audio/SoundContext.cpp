//
// Created by Monika on 08.07.2022.
//

#include <Audio/SoundContext.h>
#include <Audio/Impl/OpenALContext.h>

namespace SR_AUDIO_NS {
    SoundDevice *SoundContext::GetDevice() const {
        return m_device;
    }
    PlayParams PlayParams::GetDefault() {

            PlayParams playParams;
            playParams.async = true;
            playParams.loop = false;
            playParams.library = AudioLibrary::OpenAL;
            playParams.relative = 360.f;
            playParams.gain = 1.f;
            playParams.minGain = 0.f;
            playParams.pitch = 1.f;
            playParams.maxGain = 1.f;
            playParams.coneInnerAngle = 360.f;
            playParams.uniqueId = 0;
            playParams.device = "";
            return playParams;

    }
    void SoundContext::ApplyParams(SoundSource pSource, const PlayParams &params)
    {
        if(params.device !=std::nullopt){
            if(m_params.device != std::nullopt){
                if(m_params.device.value() != params.device.value()){
                    m_params.device = params.device;
                }
            }else{
                m_params.device = params.device;
            }
        }


        if(params.coneInnerAngle != std::nullopt){
            if(m_params.coneInnerAngle != std::nullopt ){
                if(m_params.coneInnerAngle.value() != params.coneInnerAngle.value()){
                    m_params.coneInnerAngle = params.coneInnerAngle;
                }
            }else{
                m_params.coneInnerAngle = params.coneInnerAngle;
            }
        }

        if(params.async != std::nullopt){
            if(m_params.async != std::nullopt){
                if(m_params.async.value() != params.async.value()){
                    m_params.async = params.async;
                }
            } else{
                m_params.async = params.async;
            }

        }

        if(params.direction != std::nullopt){
            if(m_params.direction != std::nullopt){
                if(m_params.direction.value() != params.direction.value()){
                    m_params.direction = params.direction;
                }
            } else{
                m_params.direction = params.direction;
            }

        }

        //Volume
        if(params.gain != std::nullopt){
            if(m_params.gain != std::nullopt){
                if(m_params.gain.value() != params.gain.value()){
                    m_params.gain = params.gain;
                }
            }else{
                m_params.gain = params.gain;
            }

        }

        if(params.library != std::nullopt){
            if(m_params.library != std::nullopt){
                if(m_params.library.value() != params.library.value()){
                    m_params.library = params.library;
                }
            }else{
                m_params.library = params.library;
            }

        }

        if(params.loop != std::nullopt){
            if(m_params.loop != std::nullopt){
                if(m_params.loop.value() != params.loop.value()){
                    m_params.loop = params.loop;
                }
            } else{
                m_params.loop = params.loop;
            }

        }

        if(params.maxGain != std::nullopt){
            if(m_params.maxGain != std::nullopt){
                if(m_params.maxGain.value() != params.maxGain.value()){
                    m_params.maxGain = params.maxGain;
                }
            }else{
                m_params.maxGain = params.maxGain;
            }

        }

        if(params.minGain != std::nullopt){
            if(m_params.minGain != std::nullopt){
                if(m_params.minGain.value() != params.minGain.value()){
                    m_params.minGain= params.minGain;
                }
            }else{
                m_params.minGain= params.minGain;
            }

        }

        if(params.orientation != std::nullopt){
            if(m_params.orientation != std::nullopt){
                if(m_params.orientation.value().t != params.orientation.value().t &&
                m_params.orientation.value().v != params.orientation.value().v &&
                m_params.orientation.value().w != params.orientation.value().w &&
                m_params.orientation.value().x != params.orientation.value().x &&
                m_params.orientation.value().y != params.orientation.value().y &&
                m_params.orientation.value().z != params.orientation.value().z){
                    m_params.orientation = params.orientation;
                }
            }else{
                m_params.orientation = params.orientation;
            }

        }

        if(params.pitch != std::nullopt){
            if(m_params.pitch != std::nullopt){
                if(m_params.pitch.value() != params.pitch.value()){
                    m_params.pitch = params.pitch;
                }
            } else{
                m_params.pitch = params.pitch;
            }

        }

        if(params.position != std::nullopt){
            if(m_params.position != std::nullopt){
                if(m_params.position.value() != params.position.value()){
                    m_params.position = params.position;
                }
            }else{
                m_params.position = params.position;
            }

        }

        if(params.relative != std::nullopt){
            if(m_params.relative != std::nullopt){
                if(m_params.relative.value() != params.relative.value()){
                    m_params.relative = params.relative;
                }
            }else{
                m_params.relative = params.relative;
            }

        }

        if(params.uniqueId != std::nullopt){
            if(m_params.uniqueId != std::nullopt){
                if(m_params.uniqueId.value() != params.uniqueId.value()){
                    m_params.uniqueId= params.uniqueId;
                }
            }else{
                m_params.uniqueId= params.uniqueId;
            }

        }

        if(params.velocity != std::nullopt){
            if(m_params.velocity != std::nullopt){
                if(m_params.velocity.value() != params.velocity.value()){
                    m_params.velocity = params.velocity;
                }
            }else{
                m_params.velocity = params.velocity;
            }

        }



    }
    SoundContext::SoundContext(SoundDevice *pDevice)
        : m_device(pDevice)
    { }

    SoundContext::~SoundContext() {
        delete m_device;
    }

    SoundContext* SoundContext::Allocate(SoundDevice *pDevice) {
        SR_INFO("SoundContext::Allocate() : allocating a sound context...");

        if (!pDevice) {
            SR_ERROR("SoundContext::Allocate() : the device is nullptr!");
            return nullptr;
        }

        switch (pDevice->GetLibrary()) {
            case AudioLibrary::OpenAL:
                return new OpenALContext(pDevice);
            case AudioLibrary::FMOD:
            case AudioLibrary::Wwise:
            case AudioLibrary::Allegro:
            case AudioLibrary::SoLoud:
            case AudioLibrary::Unknown:
                SR_ERROR("SoundContext::Allocate() : unsupported library!");
                break;
        }

        return nullptr;
    }
}