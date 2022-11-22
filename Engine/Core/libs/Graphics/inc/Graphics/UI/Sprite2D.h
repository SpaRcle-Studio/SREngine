//
// Created by Monika on 30.07.2022.
//

#ifndef SRENGINE_SPRITE2D_H
#define SRENGINE_SPRITE2D_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GRAPH_UI_NS {
    const std::vector<uint32_t> SPRITE_INDICES = { 0, 1, 2, 0, 2, 3 };

    const std::vector<Vertices::UIVertex> SPRITE_VERTICES = {
            { { 1.000000, 1.000000, 0.000000 }, { 0.000000, 1.000000 } },
            { { -1.000000, 1.000000, -0.000000 }, { 1.000000, 1.000000 } },
            { { -1.000000, -1.000000, -0.000000 }, { 1.000000, 0.000000 } },
            { { 1.000000, -1.000000, 0.000000 }, { 0.000000, 0.000000 } }
    };

    class Sprite2D : public SR_GTYPES_NS::MeshComponent {
        SR_ENTITY_SET_VERSION(1000);
        using Super = SR_GTYPES_NS::MeshComponent;
    public:
        Sprite2D();

    protected:
        ~Sprite2D() override = default;

    public:
        typedef Vertices::UIVertex VertexType;

    public:
        IResource* Copy(IResource* destination) const override;

        void UseMaterial() override;
        void UseModelMatrix() override;

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    protected:
        bool Calculate() override;
        void FreeVideoMemory() override;
        void Draw() override;

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

    };
}

#endif //SRENGINE_SPRITE2D_H
