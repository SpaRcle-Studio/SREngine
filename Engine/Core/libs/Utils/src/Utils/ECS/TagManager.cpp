//
// Created by Monika on 01.01.2023.
//

#include <Utils/ECS/TagManager.h>
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    TagManager::Hash TagManager::RegisterTag(const std::string &tag) {
        SR_LOCK_GUARD;

        if (UNTAGGED == tag) {
            return 0;
        }

        const auto hash = HashTag(tag);

        m_tagNames[hash] = tag;

        m_tags.emplace_back(tag);
        m_indices[hash] = m_indices.size();

        return hash;
    }

    const std::string& TagManager::GetTag(Tag tag) const {
        SR_LOCK_GUARD;

        if (tag == 0) {
            return UNTAGGED;
        }

        auto&& pIt = m_tagNames.find(tag);

        if (pIt == m_tagNames.end()) {
            SRHalt("TagManager::GetTagName() : unknown tag!");
            static const std::string def;
            return def;
        }

        return pIt->second;
    }

    SR_UTILS_NS::Path TagManager::InitializeResourcePath() const {
        return "Engine/Configs/TagManagerSettings.xml";
    }

    void TagManager::ClearSettings() {
        SR_LOCK_GUARD;

        m_tagNames.clear();
        m_tags.clear();
        m_indices.clear();

        Settings::ClearSettings();
    }

    bool TagManager::LoadSettings(const Xml::Node &node) {
        SR_LOCK_GUARD;

        m_tags.emplace_back(UNTAGGED);
        m_indices[HashTag(UNTAGGED)] = m_indices.size();

        if (auto&& tagsNode = node.GetNode("Tags")) {
            for (auto&& tagNode : tagsNode.GetNodes()) {
                RegisterTag(tagNode.Name());
            }
        }

        return Settings::LoadSettings(node);
    }

    TagManager::Hash TagManager::HashTag(const std::string &tag) const {
        SR_LOCK_GUARD;

        if (tag == UNTAGGED) {
            return 0;
        }

        return SR_HASH_STR(tag);
    }

    uint16_t TagManager::GetTagIndex(Tag tag) const {
        SR_LOCK_GUARD;

        if (tag == 0) {
            return 0;
        }

        auto&& pIt = m_indices.find(tag);

        if (pIt == m_indices.end()) {
            SRHalt("TagManager::GetTagIndex() : unknown tag!");
            return SR_ID_INVALID;
        }

        return pIt->second;
    }

    const std::string &TagManager::GetTagByIndex(uint16_t index) const {
        SR_LOCK_GUARD;

        if (index >= m_tags.size()) {
            SRHalt("TagManager::GetTagByIndex() : out of range!");
            static const std::string def;
            return def;
        }

        return m_tags.at(index);
    }
}