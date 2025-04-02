

# File IRawMeshHolder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**IRawMeshHolder.h**](IRawMeshHolder_8h.md)

[Go to the documentation of this file](IRawMeshHolder_8h.md)


```C++
//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_UTILS_I_RAW_MESH_HOLDER_H
#define SR_ENGINE_UTILS_I_RAW_MESH_HOLDER_H

#include <Utils/TypeTraits/SRClass.h>
#include <Utils/Common/Vertices.h>
#include <Utils/Common/SubscriptionHolder.h>

namespace SR_HTYPES_NS {
    class RawMesh;

    class IRawMeshHolder {
    public:
        using RawMeshPtr = SR_HTYPES_NS::RawMesh*;
        using MeshIndex = int32_t;

        virtual ~IRawMeshHolder();

    public:
        SR_NODISCARD MeshIndex GetMeshId() const noexcept { return m_meshId; }
        SR_NODISCARD RawMeshPtr GetRawMesh() const noexcept { return m_rawMesh; }
        SR_NODISCARD SR_UTILS_NS::Path GetMeshPath() const noexcept;
        SR_NODISCARD std::string GetMeshStringPath() const noexcept;
        SR_NODISCARD bool IsValidMeshId() const noexcept;
        SR_NODISCARD std::vector<SR_UTILS_NS::Vertex> GetVertices() const noexcept;
        SR_NODISCARD std::string_view GetGeometryName() const noexcept;

        virtual void OnRawMeshChanged() { }

        void SetRawMesh(const SR_UTILS_NS::Path& path);
        void SetRawMesh(RawMeshPtr pRawMesh);
        void SetMeshId(MeshIndex meshIndex, bool forceReload = false);

    private:
        SR_UTILS_NS::Subscription m_reloadSubscription;
        RawMeshPtr m_rawMesh = nullptr;
        MeshIndex m_meshId = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_UTILS_I_RAW_MESH_HOLDER_H
```


