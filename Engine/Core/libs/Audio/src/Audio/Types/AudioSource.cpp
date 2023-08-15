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
        auto&& pComponent = new AudioSource();

        pComponent->m_path = marshal.Read<std::string>();
        pComponent->Volume = marshal.Read<int32_t>();

        return dynamic_cast<Component*>(pComponent);
    }

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr AudioSource::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const{
        pMarshal = Component::Save(pMarshal, flags);
        pMarshal->Write<std::string>(m_path.ToString());
        pMarshal->Write<int>(Volume);
        return pMarshal;
    }

    int32_t AudioSource::GetVolume() {
        return Volume;
    }
    void AudioSource::SetVolume(int32_t Volume) {
        this->Volume  = Volume;
    }

    SR_UTILS_NS::Path AudioSource::GetPath() {
        return m_path;
    }
    void AudioSource::SetPath(std::string path) {
        m_path = path;
    }

    void AudioSource::OnEnable() {
        SoundManager::Instance().Play(m_path.ToString());
        Component::OnEnable();
    }

    void AudioSource::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }
}
