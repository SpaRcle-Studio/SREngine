//
// Created by Monika on 20.03.2023.
//

#ifndef SRENGINE_MESHUTILS_H
#define SRENGINE_MESHUTILS_H

#include <Graphics/Utils/MeshTypes.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class MeshComponent;
}

namespace SR_GRAPH_NS {
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_MESH_FORMATS = "obj,pmx,fbx,blend,stl,dae,3ds";

    SR_GTYPES_NS::Mesh* CreateMeshByType(MeshType type);
    SR_GTYPES_NS::MeshComponent* CreateMeshComponentByType(MeshType type);
    uint16_t RoundBonesCount(uint16_t count);
}

#endif //SRENGINE_MESHUTILS_H
