//
// Created by Monika on 30.07.2022.
//

#ifndef SRENGINE_SPRITE_H
#define SRENGINE_SPRITE_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    const std::vector<uint32_t> SR_SPRITE_INDICES = { 0, 1, 2, 0, 2, 3 }; /// NOLINT

    const std::vector<Vertices::UIVertex> SR_SPRITE_VERTICES = { /// NOLINT
        { {  1.000000,  1.000000,  0.000000 }, { 0.000000, 1.000000 } },
        { { -1.000000,  1.000000, -0.000000 }, { 1.000000, 1.000000 } },
        { { -1.000000, -1.000000, -0.000000 }, { 1.000000, 0.000000 } },
        { {  1.000000, -1.000000,  0.000000 }, { 0.000000, 0.000000 } }
    };

    class Sprite : public SR_GTYPES_NS::MeshComponent {
        SR_REGISTER_NEW_COMPONENT(Sprite, 1001)
        using Super = SR_GTYPES_NS::MeshComponent;
    public:
        Sprite();

    protected:
        ~Sprite() override = default;

    public:
        typedef Vertices::UIVertex VertexType;

    public:
        void UseMaterial() override;
        void UseModelMatrix() override;
        void OnPriorityDirty() override;
        SR_NODISCARD bool InitializeEntity() noexcept override;

        SR_NODISCARD bool IsFlatMesh() const noexcept override { return true; }

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD std::string GetMeshIdentifier() const override;

        SR_NODISCARD SR_MATH_NS::FVector2 GetTextureBorder() const { return m_textureBorder; }
        SR_NODISCARD SR_MATH_NS::FVector2 GetWindowBorder() const { return m_windowBorder; }

        void SetTextureBorder(const SR_MATH_NS::FVector2& border) {
            m_textureBorder = border;
        }

        void SetWindowBorder(const SR_MATH_NS::FVector2& border) {
            m_windowBorder = border;
        }

    protected:
        bool Calculate() override;
        void Draw() override;

    protected:
        bool m_sliced = true;
        SR_MATH_NS::FVector2 m_textureBorder = 0.15f;
        SR_MATH_NS::FVector2 m_windowBorder = 0.15f;

    };
}

#endif //SRENGINE_SPRITE_H
