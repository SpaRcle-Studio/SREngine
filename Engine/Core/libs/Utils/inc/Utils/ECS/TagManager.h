//
// Created by Monika on 01.01.2023.
//

#ifndef SRENGINE_TAGMANAGER_H
#define SRENGINE_TAGMANAGER_H

#include <Utils/Settings.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    typedef uint64_t Tag;

    class TagManager : public GlobalSettings<TagManager> {
        SR_REGISTER_SINGLETON(TagManager)
        friend class GlobalSettings<TagManager>;
        using Hash = uint64_t;
    public:
        SR_INLINE_STATIC const std::string UNTAGGED = "Untagged"; /** NOLINT */

    public:
        SR_NODISCARD const std::string& GetTag(Tag tag) const;
        SR_NODISCARD const std::string& GetTagByIndex(uint16_t index) const;
        SR_NODISCARD uint16_t GetTagIndex(Tag tag) const;
        SR_NODISCARD const std::vector<std::string>& GetTags() const { return m_tags; }

        SR_NODISCARD Hash HashTag(const std::string& tag) const;

    protected:
        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

        Hash RegisterTag(const std::string& tag);

    private:
        std::map<Hash, std::string> m_tagNames;
        std::map<Hash, uint16_t> m_indices;
        std::vector<std::string> m_tags;

    };
}

#endif //SRENGINE_TAGMANAGER_H
