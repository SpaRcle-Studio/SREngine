//
// Created by Monika on 20.03.2023.
//

#ifndef SRENGINE_MESHUTILS_H
#define SRENGINE_MESHUTILS_H

#include <Graphics/Utils/MeshTypes.h>

namespace SR_GTYPES_NS {
    class Mesh;
}

namespace SR_GRAPH_NS {
    SR_GTYPES_NS::Mesh* CreateMeshByType(MeshType type);
}

#endif //SRENGINE_MESHUTILS_H
