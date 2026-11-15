//
// Created by Danilka000novishok on 08.08.2023.
//

#include <Audio/Types/AudioSource.h>
#include <Audio/SoundManager.h>

#include <Utils/ECS/Transform.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/FileSystem/PathDataAccessor.h>
#include <Utils/Events/Broadcaster.h>

#include <Codegen/AudioSource.generated.hpp>

namespace SR_AUDIO_NS {
    bool AudioSource::SetGroup(SR_UTILS_NS::StringAtom group) {
        if (!AudioMixer::Instance().HasGroup(group)) {
            SR_ERROR("AudioSource::SetGroup() : unknown group {}", group);
            return false;
        }
        if (m_group != group) {
            m_group = group;
            UpdateParams();
        }
        return true;
    }

    bool AudioSource::Play() {
        SR_TRACY_ZONE;
        Stop();
        if (m_path.empty()) {
            SR_ERROR("AudioSource::Play() : empty resource path");
            return false;
        }
        if (!AudioMixer::Instance().HasGroup(m_group)) {
            SR_ERROR("AudioSource::Play() : unknown group {} for {}", m_group, m_path);
            return false;
        }
        auto params = m_params;
        params.gain = GetVolume() * AudioMixer::Instance().GetGain(m_group);
        if (GetSpatialize() == SpatializeMode::Off) {
            params.relative = 1.f;
            params.position = SR_MATH_NS::FVector3::Zero();
            params.rolloffFactor = 0.f;
        }
        params.MarkAsChanged();
        m_handle = SoundManager::Instance().Play(m_path.View(), params);
        m_startedPlayback = m_handle != nullptr;
        if (!m_handle) {
            SR_ERROR("AudioSource::Play() : failed resource {}", m_path);
        }
        return m_handle != nullptr;
    }

    void AudioSource::Stop() {
        if (m_handle) {
            SoundManager::Instance().Stop(m_handle);
            m_handle = nullptr;
        }
        m_startedPlayback = false;
    }

    bool AudioSource::Pause() {
        return m_handle && SoundManager::Instance().SetPaused(m_handle, true);
    }

    bool AudioSource::Resume() {
        return m_handle && SoundManager::Instance().SetPaused(m_handle, false);
    }

    bool AudioSource::Seek(float_t seconds) {
        if (!m_handle || !SoundManager::Instance().Seek(m_handle, seconds)) {
            SR_ERROR("AudioSource::Seek() : invalid position {} for {}", seconds, m_path);
            return false;
        }
        return true;
    }

    float_t AudioSource::GetPlaybackPosition() const {
        return m_handle ? SoundManager::Instance().GetPlaybackPosition(m_handle) : 0.f;
    }

    bool AudioSource::IsPlaying() const {
        return m_handle && SoundManager::Instance().IsPlaying(m_handle);
    }

    bool AudioSource::IsPaused() const {
        return m_handle && SoundManager::Instance().IsPaused(m_handle);
    }

    bool AudioSource::HasFinished() const {
        return m_startedPlayback && m_handle && !SoundManager::Instance().IsExists(m_handle);
    }

    AudioSource::AudioSource()
        : SR_UTILS_NS::Component()
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

        SR_UTILS_NS::Component::OnMatrixDirty();
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
        if (!std::isfinite(volume)) {
            SR_ERROR("AudioSource::SetVolume() : non-finite volume");
            return;
        }
        m_params.gain = std::clamp(volume, 0.f, 1.f);
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
        m_params.relative = spatialize == SpatializeMode::Off ? 1.f : 0.f;
        UpdateParams();
    }

    SR_UTILS_NS::Path AudioSource::GetPath() const {
        return m_path;
    }

    void AudioSource::SetPath(const SR_UTILS_NS::Path& path) {
        SR_TRACY_ZONE;

        m_path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        if (IsActive() && m_playOnEnable && !m_path.empty()) {
            Play();
        }
        else {
            Stop();
        }
    }

    void AudioSource::UpdateParams() {
        if (!m_handle) {
            return;
        }
        auto params = m_params;
        params.gain = GetVolume() * AudioMixer::Instance().GetGain(m_group);
        if (GetSpatialize() == SpatializeMode::Off) {
            params.relative = 1.f;
            params.position = SR_MATH_NS::FVector3::Zero();
            params.rolloffFactor = 0.f;
        }
        params.MarkAsChanged();
        SoundManager::Instance().ApplyParams(m_handle, params);
    }

    void AudioSource::OnEnable() {
        if (!m_mixerSubscription.IsValid()) {
            m_mixerSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe("AudioMixerChanged", [this](auto&&) {
                UpdateParams();
            });
        }
        if (!m_path.IsEmpty() && m_playOnEnable && !SoundManager::Instance().IsExists(m_handle)) {
            Play();
        }
        Component::OnEnable();
    }

    void AudioSource::OnDestroy() {
        m_mixerSubscription.Reset();
        Stop();
        SR_UTILS_NS::Component::OnDestroy();
    }

    void AudioSource::OnDisable() {
        if (m_handle && !m_continueOnDisable) {
            Stop();
        }
        SR_UTILS_NS::Component::OnDisable();
    }

    void AudioSource::SetContinueOnDisable(bool continueOnDisable) {
        m_continueOnDisable = continueOnDisable;
    }

    bool AudioSource::GetContinueOnDisable() const {
        return m_continueOnDisable;
    }
}
