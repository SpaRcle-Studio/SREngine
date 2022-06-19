//
// Created by Monika on 17.06.2022.
//

#ifndef SRENGINE_EDITORSETTINGS_H
#define SRENGINE_EDITORSETTINGS_H

#include <Utils/Settings.h>

namespace SR_CORE_NS {
    SR_ENUM_CLASS_T(EditorIcon, uint32_t,
          Unknown,
          Material,
          File,
          Folder
    );

    class EditorSettings : public SR_UTILS_NS::GlobalSettings<EditorSettings> {
        friend class SR_UTILS_NS::GlobalSettings<EditorSettings>;
        friend class SR_UTILS_NS::Singleton<EditorSettings>;
        using Icons = std::map<EditorIcon, SR_UTILS_NS::Path>;
        using Super = SR_UTILS_NS::GlobalSettings<EditorSettings>;
    protected:
        ~EditorSettings() override = default;

    public:
        SR_NODISCARD Icons GetIcons() const;
        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const override;

    protected:
        void ClearSettings() override;
        void LoadSettings(const SR_XML_NS::Node& node) override;

    private:
        Icons m_icons;

    };
}

#endif //SRENGINE_EDITORSETTINGS_H
