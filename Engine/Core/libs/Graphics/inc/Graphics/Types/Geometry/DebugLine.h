//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_DEBUGLINE_H
#define SRENGINE_DEBUGLINE_H

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
        DebugLine();
        DebugLine(SR_MATH_NS::FVector3 startPoint, SR_MATH_NS::FVector3 endPoint, SR_MATH_NS::FVector4 color);

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsDebugMesh() const noexcept override { return true; }

        void SetStartPoint(const SR_MATH_NS::FVector3& startPoint);
        void SetEndPoint(const SR_MATH_NS::FVector3& endPoint);
        void SetColor(const SR_MATH_NS::FVector4& color);

        void Draw() override;

        IResource* CopyResource(IResource* destination) const override;

        bool Calculate() override;
        void FreeVideoMemory() override;

        void UseMaterial() override;

    private:
        SR_MATH_NS::FVector3 m_startPoint;
        SR_MATH_NS::FVector3 m_endPoint;
        SR_MATH_NS::FVector4 m_color;

    };
}

#endif //SRENGINE_DEBUGLINE_H
