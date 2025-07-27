//
// Created by Monika on 17.06.2022.
//

#include <Engine/Settings/EditorSettings.h>

#include <Codegen/EditorSettings.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::Path EditorSettings::GetRenderTechnique() const {
        return m_renderTechnique;
    }

    SR_UTILS_NS::Path EditorSettings::GetPrefabEditorRenderTechnique() const {
        return m_prefabEditorRenderTechnique;
    }
}