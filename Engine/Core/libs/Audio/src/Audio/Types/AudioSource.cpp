//
// Created by Danilka000novishok on 08.08.2023.
//

#include <Audio/Types/AudioSource.h>
#include <Utils/ECS/ComponentManager.h>
#include <Audio/SoundManager.h>
#include <Utils/ECS/Transform.h>

namespace SR_AUDIO_NS {
    AudioSource::AudioSource()
        : Super()
    { }

    bool AudioSource::InitializeEntity() noexcept {
        m_params = PlayParams::GetDefault();

        GetComponentProperties().AddStandardProperty<bool>("Loop")
            .SetGetter([this](void* pData) { *static_cast<bool*>(pData) = GetLoop(); })
            .SetSetter([this](void* pData) { SetLoop(*static_cast<bool*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Cone Inner Angle")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetConeInnerAngle(); })
            .SetSetter([this](void* pData) { SetConeInnerAngle(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Pitch")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetPitch(); })
            .SetSetter([this](void* pData) { SetPitch(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Volume")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetVolume(); })
            .SetSetter([this](void* pData) { SetVolume(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Max distance")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetMaxDistance(); })
            .SetSetter([this](void* pData) { SetMaxDistance(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Rolloff factor")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetRolloffFactor(); })
            .SetSetter([this](void* pData) { SetRolloffFactor(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<float_t>("Reference distance")
            .SetGetter([this](void* pData) { *static_cast<float_t*>(pData) = GetReferenceDistance(); })
            .SetSetter([this](void* pData) { SetReferenceDistance(*static_cast<float_t*>(pData)); });

        GetComponentProperties().AddStandardProperty<SR_MATH_NS::FVector3>("Direction")
            .SetGetter([this](void* pData) { *static_cast<SR_MATH_NS::FVector3*>(pData) = GetDirection(); })
            .SetSetter([this](void* pData) { SetDirection(*static_cast<SR_MATH_NS::FVector3*>(pData)); });

        GetComponentProperties().AddEnumProperty<SpatializeMode>("Spatialize")
            .SetGetter([this]() { return SR_UTILS_NS::EnumReflector::ToStringAtom(GetSpatialize()); })
            .SetSetter([this](const SR_UTILS_NS::StringAtom& value) { SetSpatialize(SR_UTILS_NS::EnumReflector::FromString<SpatializeMode>(value)); });

        GetComponentProperties().AddCustomProperty<SR_UTILS_NS::PathProperty>("Path")
            .AddFileFilter("Sound", SR_SUPPORTED_AUDIO_FORMATS)
            .SetGetter([this]() -> SR_UTILS_NS::Path { return GetPath(); })
            .SetSetter([this](const SR_UTILS_NS::Path& path) { SetPath(path); });

        return Super::InitializeEntity();
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

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void AudioSource::OnDisable() {
        if (m_handle) {
            SoundManager::Instance().Stop(m_handle);
            m_handle = nullptr;
        }
        Super::OnDisable();
    }
}
