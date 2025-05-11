

# File Sprite.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**Sprite.h**](Sprite_8h.md)

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


