//
// Created by Monika on 12.08.2023.
//

#ifndef SRENGINE_RENDERTECHNIQUEEDITOR_H
#define SRENGINE_RENDERTECHNIQUEEDITOR_H

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

#endif //SRENGINE_RENDERTECHNIQUEEDITOR_H
