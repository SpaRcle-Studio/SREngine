

# File DebugLine.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**DebugLine.h**](DebugLine_8h.md)

[Go to the documentation of this file](DebugLine_8h.md)


```C++
//
// Created by Monika on 19.09.2022.
//

#ifndef SR_ENGINE_DEBUG_LINE_H
#define SR_ENGINE_DEBUG_LINE_H

#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Uniforms.h>

namespace SR_GTYPES_NS {
    class DebugLine final : public Mesh {
        friend class Mesh;
        using Super = Mesh;
    public:
        typedef Vertices::SimpleVertex VertexType;

    public:
        DebugLine() = default;
        DebugLine(SR_MATH_NS::FVector3 startPoint, SR_MATH_NS::FVector3 endPoint, SR_MATH_NS::FVector4 color);

    public:
        void SetStartPoint(const SR_MATH_NS::FVector3& startPoint);
        void SetEndPoint(const SR_MATH_NS::FVector3& endPoint);
        void SetColor(const SR_MATH_NS::FVector4& color);

        void UseMaterial() override;

        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Line; }

        SR_NODISCARD uint32_t GetIndicesCount() const override { return 2; }
        SR_NODISCARD bool IsSupportVBO() const override { return false; }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetMeshLayer() const override {
            const static SR_UTILS_NS::StringAtom debugLayer = "Debug";
            return debugLayer;
        }

    private:
        SR_MATH_NS::FVector3 m_startPoint;
        SR_MATH_NS::FVector3 m_endPoint;
        SR_MATH_NS::FVector4 m_color;

    };
}

#endif //SR_ENGINE_DEBUG_LINE_H
```


