

# File IRawMeshHolder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**IRawMeshHolder.h**](IRawMeshHolder_8h.md)

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
        using RawMeshPtr = SR_HTYPES_NS::SharedPtr<SR_HTYPES_NS::RawMesh>;
        using MeshIndex = int32_t;

        virtual ~IRawMeshHolder();

    public:
        SR_NODISCARD MeshIndex GetMeshId() const noexcept { return m_meshId; }
        SR_NODISCARD const RawMeshPtr& GetRawMesh() const noexcept { return m_rawMesh; }
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


