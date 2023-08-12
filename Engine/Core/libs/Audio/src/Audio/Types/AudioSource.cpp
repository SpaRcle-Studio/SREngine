//
// Created by Danilka000novishok on 08.08.2023.
//

#include <Audio/Types/AudioSource.h>
#include <Utils/ECS/ComponentManager.h>
#include <Audio/SoundManager.h>

namespace SR_AUDIO_NS
{
    SR_REGISTER_COMPONENT(AudioSource);

    AudioSource::AudioSource()
            : SR_UTILS_NS::Component()
    { }

    SR_UTILS_NS::Component*  AudioSource::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        return new AudioSource();
    }

    void AudioSource::OnEnable() {
        SoundManager::Instance().Play("Editor\\Audio\\music.mp3");
    }

    void AudioSource::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }
}
