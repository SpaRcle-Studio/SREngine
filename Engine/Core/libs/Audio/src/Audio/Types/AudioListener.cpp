//
// Created by Capitan_Slider on 16.09.1901.
//

#include <Audio/Types/AudioListener.h>
#include <Audio/SoundListener.h>
#include <Audio/Impl/OpenALSoundListener.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_AUDIO_NS{
    AudioListener::AudioListener()
        : SR_UTILS_NS::Component()
    { }

    void AudioListener::OnEnable() {
        SR_TRACY_ZONE;

        if (!m_listenerContext) {
            m_listenerContext = SR_AUDIO_NS::SoundManager::Instance().CreateListener();
            if (!m_listenerContext) {
                SR_ERROR("AudioListener::OnEnable() : failed to create listener!");
                return;
            }

            SR_AUDIO_NS::SoundManager::Instance().SetListenerDistanceModel(m_listenerContext, m_distanceModel);
            SR_AUDIO_NS::SoundManager::Instance().SetListenerGain(m_listenerContext, m_gain);
            SR_AUDIO_NS::SoundManager::Instance().SetListenerVelocity(m_listenerContext, m_velocity);
        }
        Super::OnEnable();
    }

    void AudioListener::OnDisable() {
        if (m_listenerContext) {
            SR_AUDIO_NS::SoundManager::Instance().DestroyListener(m_listenerContext);
            m_listenerContext = nullptr;
        }
        Super::OnEnable();
    }

    bool AudioListener::InitializeEntity() noexcept {
        GetComponentProperties().AddEnumProperty("Distance model", &m_distanceModel)
            .SetSetter([this](const SR_UTILS_NS::StringAtom& value) { SetDistanceModel(SR_UTILS_NS::EnumReflector::FromString<ListenerDistanceModel>(value)); });

        GetComponentProperties().AddStandardProperty("Gain", &m_gain)
            .SetSetter([this](void* pData) { SetGain(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<SR_MATH_NS::FVector3>("Velocity", &m_velocity)
            .SetSetter([this](void* pData) { SetVelocity(*static_cast<SR_MATH_NS::FVector3*>(pData)); });

        return Super::InitializeEntity();
    }

    void AudioListener::OnDestroy() {
        if (m_listenerContext) {
            SR_AUDIO_NS::SoundManager::Instance().DestroyListener(m_listenerContext);
            m_listenerContext = nullptr;
        }

        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void AudioListener::OnAttached() {
        Super::OnAttached();
    }

    void AudioListener::SetDistanceModel(ListenerDistanceModel distanceModel) {
        if (m_distanceModel == distanceModel) {
            return;
        }
        m_distanceModel = distanceModel;
        if (m_listenerContext) {
            SR_AUDIO_NS::SoundManager::Instance().SetListenerDistanceModel(m_listenerContext, m_distanceModel);
        }
    }

    void AudioListener::SetVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_velocity == velocity) {
            return;
        }
        m_velocity = velocity;
        if (m_listenerContext) {
            SR_AUDIO_NS::SoundManager::Instance().SetListenerVelocity(m_listenerContext, m_velocity);
        }
    }

    void AudioListener::SetGain(float_t gain) {
        if (m_gain == gain) {
            return;
        }
        m_gain = gain;
        if (m_listenerContext) {
            SR_AUDIO_NS::SoundManager::Instance().SetListenerGain(m_listenerContext, m_gain);
        }
    }

    void AudioListener::OnMatrixDirty() {
        SR_TRACY_ZONE;

        if (!m_listenerContext) {
            return;
        }

        auto&& matrix = GetTransform()->GetMatrix();
        SR_MATH_NS::Quaternion q;
        SR_MATH_NS::FVector3 pos;

        if (!matrix.Decompose(pos, q)) {
            SR_ERROR("AudioListener::OnMatrixDirty() : failed to decompose matrix!");
            return;
        }

        SR_AUDIO_NS::SoundManager::Instance().SetListenerTransform(m_listenerContext, pos, q);

        Component::OnMatrixDirty();
    }
}
