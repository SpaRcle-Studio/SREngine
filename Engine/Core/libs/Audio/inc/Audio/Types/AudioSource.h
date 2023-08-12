//
// Created by Danilka000novishok on 08.08.2023.
//

#ifndef SRENGINE_AUDIOSOURCE_H
#define SRENGINE_AUDIOSOURCE_H

#include <Utils/ECS/Component.h>

namespace SR_AUDIO_NS
{
    class AudioSource : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(AudioSource);
        using Super = SR_UTILS_NS::Component;
    public:
        AudioSource();

    public:
        void OnEnable();

        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    private:
        void OnDestroy() override;

    };
}
#endif //SRENGINE_AUDIOSOURCE_H
