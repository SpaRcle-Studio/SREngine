

# File DebugWireframeMesh.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**DebugWireframeMesh.h**](DebugWireframeMesh_8h.md)

[Go to the documentation of this file](DebugWireframeMesh_8h.md)


```C++
//
// Created by Monika on 05.10.2021.
//

#ifndef SR_ENGINE_DEBUGWIREFRAMEMESH_H
#define SR_ENGINE_DEBUGWIREFRAMEMESH_H

#include <Utils/Types/IRawMeshHolder.h>

#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Uniforms.h>

namespace SR_GTYPES_NS {
    class DebugWireframeMesh final : public IndexedMesh, public SR_HTYPES_NS::IRawMeshHolder {
        SR_CLASS()
        using Super = IndexedMesh;
    public:
        typedef Vertices::SimpleVertex VertexType;

    public:
        DebugWireframeMesh() = default;
        ~DebugWireframeMesh() override = default;

    public:
        void SetColor(const SR_MATH_NS::FVector4& color);

        bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource) override;

        void OnRawMeshChanged() override;

        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Wireframe; }

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD std::string GetMeshIdentifier() const override;

        SR_NODISCARD SR_UTILS_NS::StringAtom GetMeshLayer() const override {
            const static SR_UTILS_NS::StringAtom debugLayer = "Debug";
            return debugLayer;
        }

        void SetMatrix(const SR_MATH_NS::Matrix4x4& matrix) override;
        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() const override { return m_modelMatrix; }

        bool Calculate() override;

        void UseMaterial() override;

    private:
        SR_MATH_NS::FVector4 m_color;
        SR_MATH_NS::Matrix4x4 m_modelMatrix;

    };
}

#endif //SR_ENGINE_DEBUGWIREFRAMEMESH_H
```


