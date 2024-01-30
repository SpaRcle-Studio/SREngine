//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_MESH_UTILS_H
#define SR_ENGINE_MESH_UTILS_H

#include <Graphics/Utils/MeshTypes.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class Shader;
    class MeshComponent;
}

namespace SR_GRAPH_NS {
    class RenderScene;

    struct MeshRegistrationInfo {
        SR_GTYPES_NS::Mesh* pMesh = nullptr;
        SR_GTYPES_NS::Shader* pShader = nullptr;
        SR_UTILS_NS::StringAtom layer;
        std::optional<int32_t> VBO;
        std::optional<int64_t> priority;
        SR_GRAPH_NS::RenderScene* pScene = nullptr;
    };

    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_MESH_FORMATS = "obj,pmx,fbx,blend,stl,dae,3ds";

    SR_GTYPES_NS::Mesh* CreateMeshByType(MeshType type);
    SR_GTYPES_NS::MeshComponent* CreateMeshComponentByType(MeshType type);
    uint16_t RoundBonesCount(uint16_t count);
}

#endif //SR_ENGINE_MESH_UTILS_H
