

# File DebugLine.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**DebugLine.h**](DebugLine_8h.md)

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


