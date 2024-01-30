//
// Created by Monika on 12.08.2023.
//

#ifndef SR_ENGINE_RENDERTECHNIQUEEDITOR_H
#define SR_ENGINE_RENDERTECHNIQUEEDITOR_H

#include <Utils/Common/Enumerations.h>

#include <Graphics/GUI/NodeWidget.h>

namespace SR_CORE_GUI_NS {
    class RenderTechniqueEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
    public:
        RenderTechniqueEditor();
        ~RenderTechniqueEditor() override = default;

    public:
        void OnOpen() override;
        void InitCreationPopup() override;
        void DrawLeftPanel() override;

    };
}

#endif //SR_ENGINE_RENDERTECHNIQUEEDITOR_H
