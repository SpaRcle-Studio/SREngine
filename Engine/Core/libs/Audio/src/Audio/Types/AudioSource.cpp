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
        pComponent->m_volume = marshal.Read<int32_t>();

        return dynamic_cast<Component*>(pComponent);
    }

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr AudioSource::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const{
        pMarshal = Component::Save(pMarshal, flags);
        pMarshal->Write<std::string>(m_path.ToString());
        pMarshal->Write<float_t>(m_volume);
        return pMarshal;
    }

    float AudioSource::GetVolume() {

        return m_volume;

    }
    void AudioSource::SetVolume(float volume) {

        m_volume = volume;
        m_volume = volume;

    }

    SR_UTILS_NS::Path AudioSource::GetPath() {
        return m_path;
    }
    void AudioSource::SetPath(std::string path) {
        m_path = path;
    }

    void AudioSource::OnEnable() {
        m_params.gain = m_volume;
        SoundManager::Instance().Play(m_path.ToString(),m_params);
        Component::OnEnable();
    }

    void AudioSource::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }
}
