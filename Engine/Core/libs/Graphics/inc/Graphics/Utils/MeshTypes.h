//
// Created by Monika on 20.03.2023.
//

#ifndef SRENGINE_MESHTYPES_H
#define SRENGINE_MESHTYPES_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(MeshType, uint8_t,
         Unknown = 0,
         Static = 1,
         Wireframe = 2,
         Skinned = 3,
         Sprite2D = 4,
         Procedural = 5,
         Line = 6
    )
}

#endif //SRENGINE_MESHTYPES_H
