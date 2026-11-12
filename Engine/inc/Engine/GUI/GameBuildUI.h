#ifndef SR_ENGINE_GAME_BUILD_UI_H
#define SR_ENGINE_GAME_BUILD_UI_H

#include <ImmediateGUI/GUI/ImmediateGUI.h>

namespace SR_CORE_GUI_NS {
    template<typename Draw> void BuildField(const char* label, Draw&& draw) {
        const float_t start = SR_IMMEDIATE_GUI_NS::GetCursorPos().x;
        const float_t width = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x;
        const float_t labelWidth = width * 0.3f;
        SR_UTILS_NS::String title(label);
        if (SR_IMMEDIATE_GUI_NS::CalcTextSize(title.c_str()).x > labelWidth - 8.f) {
            while (!title.empty() && SR_IMMEDIATE_GUI_NS::CalcTextSize((title + "...").c_str()).x > labelWidth - 8.f) {
                title.resize(title.size() - 1);
            }
            title += "...";
        }
        SR_IMMEDIATE_GUI_NS::AlignTextToFramePadding();
        SR_IMMEDIATE_GUI_NS::Text("%s", title.c_str());
        SR_IMMEDIATE_GUI_NS::SameLine(start + labelWidth);
        SR_IMMEDIATE_GUI_NS::PushID(label);
        SR_IMMEDIATE_GUI_NS::PushItemWidth(-1.f);
        draw();
        SR_IMMEDIATE_GUI_NS::PopItemWidth();
        SR_IMMEDIATE_GUI_NS::PopID();
    }
}

#endif
