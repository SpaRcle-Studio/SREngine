//
// Created by Monika on 17.06.2022.
//

#include <Engine/Settings/EditorSettings.h>

#include <Utils/FileSystem/PathDataAccessor.h>

#include <Codegen/EditorSettings.generated.hpp>

namespace SR_CORE_NS {
    void EditorSettings::OnThemeChanged() {
        if (auto&& pTheme = GetTheme().GetResource()) {
            pTheme->Apply();
        }
    }

    bool EditorPackage::operator==(const EditorPackage& other) const noexcept {
        return name == other.name
            && description == other.description
            && url == other.url
            && dependencies == other.dependencies;
    }
}