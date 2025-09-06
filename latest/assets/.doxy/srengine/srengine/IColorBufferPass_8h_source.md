

# File IColorBufferPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**IColorBufferPass.h**](IColorBufferPass_8h.md)

[Go to the documentation of this file](IColorBufferPass_8h.md)


```C++
//
// Created by Monika on 16.11.2023.
//

#ifndef SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H
#define SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H

#include <Graphics/macros.h>

#include <Utils/Math/Vector4.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class IColorBufferPass {
    public:
        SR_NODISCARD virtual const SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer>& GetColorFrameBuffer() const noexcept = 0;

        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(float_t x, float_t y) const;
        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(SR_MATH_NS::FVector2 pos) const;
        SR_NODISCARD SR_MATH_NS::FColor GetColor(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetIndex(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetColorIndex() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetMeshColor() const noexcept;
        SR_NODISCARD uint32_t GetColorMultiplier() const noexcept { return m_multiplier; }

        void SetColorMultiplier(uint32_t multiplier) { m_multiplier = SR_MAX(1, multiplier); }

    protected:
        void ClearTable();
        void SetMeshIndex(SR_GTYPES_NS::Mesh* pMesh);
        void IncrementColorIndex() noexcept;
        void ResetColorIndex() noexcept { m_colorId = 0; }

    private:
        std::vector<SR_GTYPES_NS::Mesh*> m_table;
        uint32_t m_colorId = 0;
        uint32_t m_multiplier = 1;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H
```


