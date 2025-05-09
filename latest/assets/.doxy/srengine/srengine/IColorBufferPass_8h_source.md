

# File IColorBufferPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**IColorBufferPass.h**](IColorBufferPass_8h.md)

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
        SR_NODISCARD virtual SR_GTYPES_NS::Framebuffer* GetColorFrameBuffer() const noexcept = 0;

        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(float_t x, float_t y) const;
        SR_NODISCARD SR_GTYPES_NS::Mesh* GetMesh(SR_MATH_NS::FVector2 pos) const;
        SR_NODISCARD SR_MATH_NS::FColor GetColor(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetIndex(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetColorIndex() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetMeshColor() const noexcept;

    protected:
        void ClearTable();
        void SetMeshIndex(SR_GTYPES_NS::Mesh* pMesh);
        void IncrementColorIndex() noexcept;
        void ResetColorIndex() noexcept { m_colorId = 0; }
        void SetColorMultiplier(uint32_t multiplier) { m_multiplier = SR_MAX(1, multiplier); }

    private:
        std::vector<SR_GTYPES_NS::Mesh*> m_table;
        uint32_t m_colorId = 0;
        uint32_t m_multiplier = 1;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_COLOR_BUFFER_PASS_H
```


