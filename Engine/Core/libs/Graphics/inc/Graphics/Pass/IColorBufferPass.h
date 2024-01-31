//
// Created by Monika on 16.11.2023.
//

#ifndef SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H
#define SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H

#include <Utils/Math/Vector4.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class IColorBufferPass {
    public:
        SR_NODISCARD virtual SR_GTYPES_NS::Framebuffer* GetColorFrameBuffer() const noexcept = 0;

        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(float_t x, float_t y) const;
        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(SR_MATH_NS::FVector2 pos) const;
        SR_NODISCARD SR_MATH_NS::FColor GetColor(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetIndex(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetColorIndex() const noexcept { return m_colorId; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetMeshColor() const noexcept;

    protected:
        void SetMeshIndex(SR_GTYPES_NS::Mesh* pMesh, uint32_t colorId);
        void IncrementColorIndex() noexcept { ++m_colorId; }
        void ResetColorIndex() noexcept { m_colorId = 0; }

    private:
        std::vector<SR_GTYPES_NS::Mesh*> m_table;
        uint32_t m_colorId = 0;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H
