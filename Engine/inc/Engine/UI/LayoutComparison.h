//
// Created by Codex on 15.11.2026.
//

#ifndef SR_ENGINE_CORE_UI_LAYOUT_COMPARISON_H
#define SR_ENGINE_CORE_UI_LAYOUT_COMPARISON_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/FileSystem/PathDataAccessor.h>

namespace SR_CORE_UI_NS {
    /// @category(Tests)
    class LayoutComparison final : public SR_UTILS_NS::Component {
        SR_CLASS()
    public:
        bool ExecuteInEditMode() const override { return true; }
        /// @method @editorButton
        void ExportCases();
        /// @method @editorButton
        void CheckDirtyScheduling();

    private:
        /// @property
        SR_UTILS_NS::Path m_input;
        /// @property
        SR_UTILS_NS::Path m_output;
    };
}

#endif // SR_ENGINE_CORE_UI_LAYOUT_COMPARISON_H
