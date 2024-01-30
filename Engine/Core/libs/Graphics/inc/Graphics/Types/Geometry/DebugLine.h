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
        DebugLine();
        DebugLine(SR_MATH_NS::FVector3 startPoint, SR_MATH_NS::FVector3 endPoint, SR_MATH_NS::FVector4 color);

    public:
        void SetStartPoint(const SR_MATH_NS::FVector3& startPoint);
        void SetEndPoint(const SR_MATH_NS::FVector3& endPoint);
        void SetColor(const SR_MATH_NS::FVector4& color);

        void Draw() override;

        void UseMaterial() override;

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
