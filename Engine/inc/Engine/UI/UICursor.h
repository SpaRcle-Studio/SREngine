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
    class UICursor : public SR_UTILS_NS::Component, public SR_GRAPH_NS::UI::IFindCanvasOwner {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

    };
}

#endif //SR_ENGINE_UI_CURSOR_H
