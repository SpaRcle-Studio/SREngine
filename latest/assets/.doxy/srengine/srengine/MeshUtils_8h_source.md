

# File MeshUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Utils**](dir_1d6f88bd3f47a17aa2fb3667e19494af.md) **>** [**MeshUtils.h**](MeshUtils_8h.md)

[Go to the documentation of this file](MeshUtils_8h.md)


```C++
//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_MESH_UTILS_H
#define SR_ENGINE_MESH_UTILS_H

#include <Graphics/Utils/MeshTypes.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(FrustumCullingType, uint8_t,
        None = 0,
        Sphere,
        AABB,
        OBB,
        DOP8,
        ConvexHull
    );

    class RenderScene;
    class MeshRenderStage;
    class BaseMaterial;
    class RenderQueue;

    struct MeshRegistrationInfo {
        uint32_t poolId = static_cast<uint32_t>(SR_ID_INVALID);
        SR_GTYPES_NS::Mesh* pMesh = nullptr;
        BaseMaterial* pMaterial = nullptr;
        SR_UTILS_NS::StringAtom layer;
        std::optional<int32_t> VBO;
        std::optional<int64_t> priority;
        SR_GRAPH_NS::RenderScene* pScene = nullptr;
    };

    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_MESH_FORMATS = "obj,pmx,fbx,blend,stl,dae,3ds";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_SUPPORTED_FONT_FORMATS = "ttf";

    SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Mesh> CreateMeshByType(MeshType type);
}

#endif //SR_ENGINE_MESH_UTILS_H
```


