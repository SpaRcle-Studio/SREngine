#pragma once

#include <ImmediateGUI/stdInclude.h>

#ifdef SR_USE_IMGUI
    #include <ImmediateGUI/Impl/ImGUI.h>
#endif

namespace SR_GRAPH_GUI_NS::Immediate::Experimental {
#ifdef SR_USE_IMGUI
    void BeginHorizontal(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void BeginHorizontal(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void EndHorizontal();

    void BeginVertical(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void BeginVertical(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void EndVertical();

    void Spring(float weight = 1.0f, float spacing = -1.0f);
#endif
}
