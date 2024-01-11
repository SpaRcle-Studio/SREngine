//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_MESHTYPES_H
#define SR_ENGINE_MESHTYPES_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(MeshType, uint8_t,
         Unknown,
         Static,
         Wireframe,
         Skinned,
         Sprite,
         Procedural,
         Line
    )
}

#endif //SR_ENGINE_MESHTYPES_H
