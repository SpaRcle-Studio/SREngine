//
// Created by Monika on 01.01.2023.
//

#ifndef SR_ENGINE_TAG_MANAGER_H
#define SR_ENGINE_TAG_MANAGER_H

#include <Utils/Settings.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    class TagManager : public GlobalSettings<TagManager> {
        SR_REGISTER_SINGLETON(TagManager)
        friend class GlobalSettings<TagManager>;
        using Super = GlobalSettings<TagManager>;
        using Hash = uint64_t;
    public:
        SR_INLINE_STATIC const StringAtom UNTAGGED = "Untagged"; /** NOLINT */

    public:
        SR_NODISCARD StringAtom GetTagByIndex(uint16_t index) const;
        SR_NODISCARD StringAtom GetDefaultTag() const;
        SR_NODISCARD uint16_t GetTagIndex(StringAtom tag) const;
        SR_NODISCARD const std::vector<StringAtom>& GetTags() const { return m_tags; }

    protected:
        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

        void RegisterTag(StringAtom tag);

    private:
        std::map<StringAtom, uint16_t> m_indices;
        std::vector<StringAtom> m_tags;

    };
}

#endif //SR_ENGINE_TAGMANAGER_H
