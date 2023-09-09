//
// Created by Danilka000novishok on 08.08.2023.
//

#ifndef SRENGINE_AUDIOSOURCE_H
#define SRENGINE_AUDIOSOURCE_H

#include <Utils/ECS/Component.h>
#include <Utils/FileSystem/Path.h>
#include <Audio/PlayParams.h>
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
        void SetPath(std::string path);

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        float GetVolume();
        void SetVolume(float volume);

        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);



    private:
        PlayParams m_params = PlayParams::GetDefault();
        SR_UTILS_NS::Path m_path;

        float m_volume = 0;
        void OnDestroy() override;

    };
}
#endif //SRENGINE_AUDIOSOURCE_H
