

# File MeshUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Utils**](dir_08379350d528ecfd47c79c18ec259ee8.md) **>** [**MeshUtils.h**](MeshUtils_8h.md)

[Go to the documentation of this file](MeshUtils_8h.md)


```C++
//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_MESH_UTILS_H
#define SR_ENGINE_MESH_UTILS_H

#include <Graphics/macros.h>

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
        const BaseMaterial* pMaterial = nullptr;
        SR_GTYPES_NS::Shader* pShader = nullptr;
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


