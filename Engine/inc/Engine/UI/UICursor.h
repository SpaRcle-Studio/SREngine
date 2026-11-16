//
// Created by Monika on 28.04.2026.
//

#ifndef SR_ENGINE_UI_CURSOR_H
#define SR_ENGINE_UI_CURSOR_H

#include <Engine/stdInclude.h>

#include <Graphics/UI/Canvas.h>

#include <Utils/ECS/SceneObject.h>

namespace SR_CORE_UI_NS {
    /// @category(UI)
    class UICursor : public SR_UTILS_NS::UIComponent, public SR_GRAPH_NS::UI::IFindCanvasOwner {
        SR_CLASS()
    public:
        bool ExecuteInEditMode() const override { return true; }
        void AfterLayout() override;
        void OnDisable() override;
        void OnDetached() override;

    private:
        bool m_positionInitialized = false;

    };
}

#endif //SR_ENGINE_UI_CURSOR_H
