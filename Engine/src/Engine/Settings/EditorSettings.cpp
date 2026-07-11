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
}