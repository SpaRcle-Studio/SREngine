//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H
#define SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(OverlayType, uint8_t,
        None, All,
        ImGui, Steam, EpicGames
    );
}

#endif //SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H
