//
// Created by Monika on 12.09.2023.
//

#include <ImmediateGUI/Impl/ImGUI.h>

namespace SR_GRAPH_GUI_NS {
    std::atomic<bool> gIgnoreImGuiAsserts = false;
    void SetIgnoreImGuiAsserts(bool ignore) {
        gIgnoreImGuiAsserts = ignore;
    }
}