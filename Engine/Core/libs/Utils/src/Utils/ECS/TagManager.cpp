//
// Created by Monika on 01.01.2023.
//

#include <Utils/ECS/TagManager.h>
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    void TagManager::RegisterTag(StringAtom tag) {
        SR_LOCK_GUARD;

        if (m_indices.count(tag) == 0) {
            m_tags.emplace_back(tag);
            m_indices[tag] = m_indices.size();
        }
    }

    SR_UTILS_NS::Path TagManager::InitializeResourcePath() const {
        return "Engine/Configs/TagManagerSettings.xml";
    }

    void TagManager::ClearSettings() {
        SR_LOCK_GUARD;

        m_tags.clear();
        m_indices.clear();

        Super::ClearSettings();
    }

    bool TagManager::LoadSettings(const Xml::Node &node) {
        SR_LOCK_GUARD;

        m_tags.clear();
        m_indices.clear();

        RegisterTag(UNTAGGED);

        if (auto&& tagsNode = node.GetNode("Tags")) {
            for (auto&& tagNode : tagsNode.GetNodes()) {
                RegisterTag(tagNode.Name());
            }
        }

        return Super::LoadSettings(node);
    }

    uint16_t TagManager::GetTagIndex(StringAtom tag) const {
        SR_LOCK_GUARD;

        if (tag == StringAtom()) {
            return 0;
        }

        auto&& pIt = m_indices.find(tag);

        if (pIt == m_indices.end()) {
            SRHalt("TagManager::GetTagIndex() : unknown tag!");
            return SR_ID_INVALID;
        }

        return pIt->second;
    }

    StringAtom TagManager::GetTagByIndex(uint16_t index) const {
        SR_LOCK_GUARD;

        if (index >= m_tags.size()) {
            SRHalt("TagManager::GetTagByIndex() : out of range!");
            static const StringAtom def;
            return def;
        }

        return m_tags.at(index);
    }

    StringAtom TagManager::GetDefaultTag() const {
        if (m_tags.empty()) {
            return "Default";
        }
        return m_tags[0];
    }
}