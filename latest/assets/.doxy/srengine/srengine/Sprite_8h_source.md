

# File Sprite.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**Sprite.h**](Sprite_8h.md)

[Go to the documentation of this file](Sprite_8h.md)


```C++
//
// Created by Monika on 30.07.2022.
//

#ifndef SR_ENGINE_SPRITE_H
#define SR_ENGINE_SPRITE_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    const std::vector<uint32_t> SR_SPRITE_INDICES = { 0, 1, 2, 0, 2, 3 }; 

    const std::vector<Vertices::UIVertex> SR_SPRITE_VERTICES = { 
        { {  1.000000,  1.000000,  0.000000 }, { 0.000000, 1.000000 } },
        { { -1.000000,  1.000000, -0.000000 }, { 1.000000, 1.000000 } },
        { { -1.000000, -1.000000, -0.000000 }, { 1.000000, 0.000000 } },
        { {  1.000000, -1.000000,  0.000000 }, { 0.000000, 0.000000 } }
    };

    class Sprite : public SR_GTYPES_NS::Mesh {
        using Super = SR_GTYPES_NS::Mesh;
    public:
        Sprite() = default;
        ~Sprite() override = default;

    public:
        typedef Vertices::UIVertex VertexType;

    public:
        void UseMaterial() override;
        void UseModelMatrix() override;

        bool IsSupportVBO() const override { return false; }

        bool BindMesh() override;

        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Sprite; }

        SR_NODISCARD bool InitializeEntity() noexcept override;

        SR_NODISCARD uint32_t GetIndicesCount() const override { return 4; }
        SR_NODISCARD bool IsFlatMesh() const noexcept override { return true; }
        SR_NODISCARD std::string GetMeshIdentifier() const override;

        SR_NODISCARD SR_MATH_NS::FVector2 GetTextureBorder() const { return m_textureBorder; }
        SR_NODISCARD SR_MATH_NS::FVector2 GetWindowBorder() const { return m_windowBorder; }

        void SetTextureBorder(const SR_MATH_NS::FVector2& border) {
            m_textureBorder = border;
            MarkUniformsDirty();
        }

        void SetWindowBorder(const SR_MATH_NS::FVector2& border) {
            m_windowBorder = border;
            MarkUniformsDirty();
        }

    protected:
        bool Calculate() override;

    protected:
        bool m_sliced = true;
        SR_MATH_NS::FVector2 m_textureBorder = 0.15f;
        SR_MATH_NS::FVector2 m_windowBorder = 0.15f;

    };
}

#endif //SR_ENGINE_SPRITE_H
```


