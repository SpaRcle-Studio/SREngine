//
// Created by Danilka000novishok on 08.08.2023.
//

#ifndef SRENGINE_AUDIOSOURCE_H
#define SRENGINE_AUDIOSOURCE_H

#include <Utils/ECS/Component.h>
#include <Utils/FileSystem/Path.h>

namespace SR_AUDIO_NS
{
    class AudioSource : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1001);
        SR_INITIALIZE_COMPONENT(AudioSource);
        using Super = SR_UTILS_NS::Component;
    public:
        AudioSource();


    public:
        void OnEnable() override;
        SR_UTILS_NS::Path GetPath();

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void SetPath(std::string path);
        int GetVolume();

        void SetVolume(int32_t Volume);

        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    private:

        SR_UTILS_NS::Path m_path;
        int32_t Volume = 100;

        void OnDestroy() override;

    };
}
#endif //SRENGINE_AUDIOSOURCE_H
