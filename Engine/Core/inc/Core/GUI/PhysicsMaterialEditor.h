//
// Created by innerviewer on 6/6/2023.
//

#ifndef SRENGINE_PHYSICSMATERIALEDITOR_H
#define SRENGINE_PHYSICSMATERIALEDITOR_H

namespace SR_CORE_GUI_NS {
class PhysicsMaterialEditor : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        PhysicsMaterialEditor();
        ~PhysicsMaterialEditor() override = default;

    protected:
        void Draw() override;
    };
}

#endif //SRENGINE_PHYSICSMATERIALEDITOR_H
