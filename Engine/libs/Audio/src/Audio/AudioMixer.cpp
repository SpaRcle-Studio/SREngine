//
// Created by Codex on 15.11.2026.
//

#include <Audio/AudioMixer.h>
#include <Audio/SoundManager.h>
#include <Utils/Events/Broadcaster.h>
#include <Codegen/AudioMixer.generated.hpp>

namespace SR_AUDIO_NS {
    SR_MAYBE_UNUSED_VAR AudioMixer::Instance();

    void AudioMixer::SetMasterVolume(float_t value) {
        if (!std::isfinite(value)) {
            SR_ERROR("AudioMixer::SetMasterVolume() : non-finite volume");
            return;
        }
        value = std::clamp(value, 0.f, 1.f);
        if (m_master != value) {
            m_master = value;
            SoundManager::Instance().SetGlobalGain(m_muted ? 0.f : m_master);
            SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        }
    }

    void AudioMixer::SetMuted(bool muted) {
        if (m_muted == muted) {
            return;
        }
        m_muted = muted;
        SoundManager::Instance().SetGlobalGain(m_muted ? 0.f : m_master);
        SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
    }

    bool AudioMixer::AddGroup(const AudioMixerGroup& group) {
        SR_TRACY_ZONE;
        if (group.name.empty() || m_groups.contains(group.name) || !HasGroup(group.parent) || !std::isfinite(group.volume)) {
            SR_ERROR("AudioMixer::AddGroup() : invalid or duplicate group {}", group.name);
            return false;
        }

        AudioMixerGroup value = group;
        value.volume = std::clamp(value.volume, 0.f, 1.f);
        m_groups.insert(value.name, value);
        SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        return true;
    }

    bool AudioMixer::RemoveGroup(SR_UTILS_NS::StringAtom group) {
        if (group.empty() || !m_groups.contains(group)) {
            return false;
        }
        for (auto&& entry : m_groups) {
            if (entry.second.parent == group) {
                SR_ERROR("AudioMixer::RemoveGroup() : group {} has children", group);
                return false;
            }
        }

        m_groups.erase(group);
        SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        return true;
    }

    bool AudioMixer::HasGroup(SR_UTILS_NS::StringAtom group) const {
        return group.empty() || m_groups.contains(group);
    }

    SR_UTILS_NS::StringAtom AudioMixer::GetGroupName(uint32_t index) const {
        if (index >= m_groups.size()) {
            SR_ERROR("AudioMixer::GetGroupName() : index {} is out of range", index);
            return {};
        }
        auto it = m_groups.begin();
        for (uint32_t i = 0; i < index; ++i) {
            ++it;
        }
        return it->first;
    }

    SR_UTILS_NS::StringAtom AudioMixer::GetGroupParent(SR_UTILS_NS::StringAtom group) const {
        const auto found = m_groups.find(group);
        if (found == m_groups.end()) {
            SR_ERROR("AudioMixer::GetGroupParent() : unknown group {}", group);
            return {};
        }
        return found->second.parent;
    }

    bool AudioMixer::IsGroupMuted(SR_UTILS_NS::StringAtom group) const {
        const auto found = m_groups.find(group);
        if (found == m_groups.end()) {
            SR_ERROR("AudioMixer::IsGroupMuted() : unknown group {}", group);
            return false;
        }
        return found->second.muted;
    }

    bool AudioMixer::SetGroupParent(SR_UTILS_NS::StringAtom group, SR_UTILS_NS::StringAtom parent) {
        auto found = m_groups.find(group);
        if (found == m_groups.end() || !HasGroup(parent)) {
            SR_ERROR("AudioMixer::SetGroupParent() : unavailable group or parent for {}", group);
            return false;
        }

        auto ancestor = parent;
        while (!ancestor.empty()) {
            if (ancestor == group) {
                SR_ERROR("AudioMixer::SetGroupParent() : cycle in group {}", group);
                return false;
            }
            ancestor = m_groups.find(ancestor)->second.parent;
        }

        found->second.parent = parent;
        SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        return true;
    }

    bool AudioMixer::SetGroupVolume(SR_UTILS_NS::StringAtom group, float_t value) {
        auto found = m_groups.find(group);
        if (found == m_groups.end() || !std::isfinite(value)) {
            SR_ERROR("AudioMixer::SetGroupVolume() : invalid group or volume for {}", group);
            return false;
        }

        value = std::clamp(value, 0.f, 1.f);
        if (found->second.volume != value) {
            found->second.volume = value;
            SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        }
        return true;
    }

    float_t AudioMixer::GetGroupVolume(SR_UTILS_NS::StringAtom group) const {
        if (group.empty()) {
            return 1.f;
        }
        const auto found = m_groups.find(group);
        if (found == m_groups.end()) {
            SR_ERROR("AudioMixer::GetGroupVolume() : unknown group {}", group);
            return 0.f;
        }
        return found->second.volume;
    }

    bool AudioMixer::SetGroupMuted(SR_UTILS_NS::StringAtom group, bool muted) {
        auto found = m_groups.find(group);
        if (found == m_groups.end()) {
            SR_ERROR("AudioMixer::SetGroupMuted() : unknown group {}", group);
            return false;
        }
        if (found->second.muted != muted) {
            found->second.muted = muted;
            SR_UTILS_NS::Broadcaster::Instance().Broadcast("AudioMixerChanged");
        }
        return true;
    }

    float_t AudioMixer::GetGain(SR_UTILS_NS::StringAtom group) const {
        float_t gain = 1.f;
        while (!group.empty()) {
            const auto found = m_groups.find(group);
            if (found == m_groups.end()) {
                SR_ERROR("AudioMixer::GetGain() : unknown group {}", group);
                return 0.f;
            }
            if (found->second.muted) {
                return 0.f;
            }
            gain *= found->second.volume;
            group = found->second.parent;
        }
        return gain;
    }
}
