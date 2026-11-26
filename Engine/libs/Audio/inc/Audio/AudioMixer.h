//
// Created by Codex on 15.11.2026.
//

#ifndef SR_ENGINE_AUDIO_MIXER_H
#define SR_ENGINE_AUDIO_MIXER_H

#include <Audio/macros.h>
#include <Utils/Common/Singleton.h>
#include <Utils/TypeTraits/SRClass.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/Map.h>

namespace SR_AUDIO_NS {
    struct SR_AUDIO_DLL_API AudioMixerGroup : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    public:
        /// @property
        SR_UTILS_NS::StringAtom name;
        /// @property
        SR_UTILS_NS::StringAtom parent;
        /// @property
        float_t volume = 1.f;
        /// @property
        bool muted = false;
    };

    /// @noCopyable @noMovable
    class SR_AUDIO_DLL_API AudioMixer : public SR_UTILS_NS::Singleton<AudioMixer>, public SR_UTILS_NS::SRClass {
        SR_CLASS()
        SR_REGISTER_SINGLETON(AudioMixer)
    public:
        /// @method
        void SetMasterVolume(float_t value);
        /// @method @evaluate
        float_t GetMasterVolume() const noexcept { return m_master; }
        /// @method
        void SetMuted(bool muted);
        /// @method @evaluate
        bool IsMuted() const noexcept { return m_muted; }
        /// @method
        void SetPlayInBackground(bool enabled);
        /// @method @evaluate
        bool IsPlayInBackground() const;
        /// @method
        bool AddGroup(const AudioMixerGroup& group);
        /// @method
        bool RemoveGroup(SR_UTILS_NS::StringAtom group);
        /// @method @evaluate
        bool HasGroup(SR_UTILS_NS::StringAtom group) const;
        /// @method @evaluate
        uint32_t GetGroupCount() const noexcept {
            return static_cast<uint32_t>(m_groups.size());
        }
        /// @method @evaluate
        SR_UTILS_NS::StringAtom GetGroupName(uint32_t index) const;
        /// @method @evaluate
        SR_UTILS_NS::StringAtom GetGroupParent(SR_UTILS_NS::StringAtom group) const;
        /// @method @evaluate
        bool IsGroupMuted(SR_UTILS_NS::StringAtom group) const;
        /// @method
        bool SetGroupParent(SR_UTILS_NS::StringAtom group, SR_UTILS_NS::StringAtom parent);
        /// @method
        bool SetGroupVolume(SR_UTILS_NS::StringAtom group, float_t value);
        /// @method @evaluate
        float_t GetGroupVolume(SR_UTILS_NS::StringAtom group) const;
        /// @method
        bool SetGroupMuted(SR_UTILS_NS::StringAtom group, bool muted);
        /// @method @evaluate
        float_t GetGain(SR_UTILS_NS::StringAtom group) const;

    private:
        float_t m_master = 1.f;
        SR_UTILS_NS::Map<SR_UTILS_NS::StringAtom, AudioMixerGroup> m_groups;
        bool m_muted = false;
    };
}

#endif // SR_ENGINE_AUDIO_MIXER_H
