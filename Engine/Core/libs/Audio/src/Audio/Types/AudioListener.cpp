//
// Created by Capitan_Slider on 16.09.1901.
//

#include <Audio/Types/AudioListener.h>
#include <Audio/ListenerContext.h>
#include <Utils/ECS/GameObject.h>

#include <Utils/ECS/Transform.h>

namespace SR_AUDIO_NS{
    SR_REGISTER_COMPONENT(AudioListener);

    AudioListener::AudioListener()
        : SR_UTILS_NS::Component()
    {
        m_listenerContext = SR_AUDIO_NS ::SoundManager::Instance().CreateListenerContext();
    }

    void AudioListener::OnDestroy() {
        SR_AUDIO_NS ::SoundManager::Instance().DestroyListenerContext(m_listenerContext);
        m_listenerContext = nullptr;

        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    SR_UTILS_NS::Component* AudioListener::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new AudioListener();
        return pComponent;
    }

    SR_HTYPES_NS::Marshal::Ptr AudioListener::Save(SR_UTILS_NS::SavableSaveData data) const {
        data.pMarshal = Super::Save(data);
        return data.pMarshal;
    }

    void AudioListener::OnAttached() {
        Component::OnAttached();
    }

    void AudioListener::OnMatrixDirty() {
        auto&& matrix = GetTransform()->GetMatrix();
        SR_MATH_NS::Quaternion q;
        SR_MATH_NS::FVector3 pos;

        if (!matrix.Decompose(pos, q)) {
            SR_ERROR("AudioListener::OnMatrixDirty() : failed to decompose matrix!")
            return;
        }

        m_listenerContext->Update(pos, q);

        Component::OnMatrixDirty();
    }
}
