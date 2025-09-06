//
// Created by Danilka000novishok on 08.08.2023.
//

#include <Audio/Types/AudioSource.h>
#include <Audio/SoundManager.h>

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/ComponentManager.h>

#include <Codegen/AudioSource.generated.hpp>

namespace SR_AUDIO_NS {
    AudioSource::AudioSource()
        : Super()
    {
        m_params = PlayParams::GetDefault();
    }

    void AudioSource::OnMatrixDirty() {
        SR_TRACY_ZONE;

        if (auto&& pTransform = GetTransform()) {
            auto&& matrix4x4 = pTransform->GetMatrix();
            const SR_MATH_NS::FVector3 position = matrix4x4.GetTranslate();
            const SR_MATH_NS::Quaternion quaternion = matrix4x4.GetQuat();

            m_params.position = position;
            m_params.orientation = {
                quaternion * SR_MATH_NS::FVector3::Forward(),
                quaternion * SR_MATH_NS::FVector3::Up()
            };

            UpdateParams();
        }

        Super::OnMatrixDirty();
    }

    float_t AudioSource::GetVolume() const {
        return m_params.gain.has_value() ? m_params.gain.value() : 0.f;
    }

    float_t AudioSource::GetMaxDistance() const {
        return m_params.maxDistance.has_value() ? m_params.maxDistance.value() : 0.f;
    }

    float_t AudioSource::GetRolloffFactor() const {
        return m_params.rolloffFactor.has_value() ? m_params.rolloffFactor.value() : 0.f;
    }

    float_t AudioSource::GetReferenceDistance() const {
        return m_params.referenceDistance.has_value() ? m_params.referenceDistance.value() : 0.f;
    }

    SR_MATH_NS::FVector3 AudioSource::GetDirection() const {
        return m_params.direction.has_value() ? m_params.direction.value() : SR_MATH_NS::FVector3::Forward();
    }

    SpatializeMode AudioSource::GetSpatialize() const {
        return m_params.spatialize.has_value() ? m_params.spatialize.value() : SpatializeMode::Auto;
    }

    bool AudioSource::GetLoop() const {
        return m_params.loop.has_value() ? m_params.loop.value() : false;
    }

    float_t AudioSource::GetPitch() const {
        return m_params.pitch.has_value() ? m_params.pitch.value() : 0.1f;
    }

    float_t AudioSource::GetConeInnerAngle() const {
        return m_params.coneInnerAngle.has_value() ? m_params.coneInnerAngle.value() : 0.f;
    }

    void AudioSource::SetPitch(float_t pitch) {
        m_params.pitch = pitch;
        UpdateParams();
    }

    void AudioSource::SetLoop(bool loop) {
        m_params.loop = loop;
        UpdateParams();
    }

    void AudioSource::SetConeInnerAngle(float_t Angle) {
        m_params.coneInnerAngle = Angle;
        UpdateParams();
    }

    void AudioSource::SetVolume(float_t volume) {
        m_params.gain = volume;
        UpdateParams();
    }

    void AudioSource::SetMaxDistance(float_t maxDistance) {
        m_params.maxDistance = maxDistance;
        UpdateParams();
    }

    void AudioSource::SetRolloffFactor(float_t rolloffFactor) {
        m_params.rolloffFactor = rolloffFactor;
        UpdateParams();
    }

    void AudioSource::SetReferenceDistance(float_t referenceDistance) {
        m_params.referenceDistance = referenceDistance;
        UpdateParams();
    }

    void AudioSource::SetDirection(const SR_MATH_NS::FVector3& direction) {
        m_params.direction = direction;
        UpdateParams();
    }

    void AudioSource::SetSpatialize(SpatializeMode spatialize) {
        m_params.spatialize = spatialize;
        UpdateParams();
    }

    SR_UTILS_NS::Path AudioSource::GetPath() const {
        return m_path;
    }

    void AudioSource::SetPath(const SR_UTILS_NS::Path& path) {
        m_path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        if (IsActive() && !m_path.empty()) {
            if (m_handle) {
                SoundManager::Instance().Stop(m_handle);
            }
            m_params.MarkAsChanged();
            m_handle = SoundManager::Instance().Play(m_path.ToString(), m_params);
        }
    }

    void AudioSource::UpdateParams() {
        if (!m_handle) {
            return;
        }
        SoundManager::Instance().ApplyParams(m_handle, m_params);
    }

    void AudioSource::OnEnable() {
        if (!m_path.IsEmpty()) {
            m_params.MarkAsChanged();
            m_handle = SoundManager::Instance().Play(m_path.ToString(), m_params);
        }
        Component::OnEnable();
    }

    void AudioSource::OnDestroy() {
        if (m_handle) {
            SoundManager::Instance().Stop(m_handle);
            m_handle = nullptr;
        }

        Super::OnDestroy();
    }

    void AudioSource::OnDisable() {
        if (m_handle) {
            SoundManager::Instance().Stop(m_handle);
            m_handle = nullptr;
        }
        Super::OnDisable();
    }
}
