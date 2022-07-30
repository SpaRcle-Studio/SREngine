//
// Created by Monika on 30.07.2022.
//

#ifndef SRENGINE_SPRITE2D_H
#define SRENGINE_SPRITE2D_H

#include <Types/Geometry/IndexedMesh.h>

namespace SR_GRAPH_NS::UI {
    class Sprite2D final : public Types::IndexedMesh {
        SR_ENTITY_SET_VERSION(1000);
    public:
        Sprite2D();

    private:
        ~Sprite2D() override = default;

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        IResource* Copy(IResource* destination) const override;

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    private:
        bool Calculate() override;
        void FreeVideoMemory() override;
        void Draw() override;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SR_UTILS_NS::SavableFlags flags) const override;

    };
}

#endif //SRENGINE_SPRITE2D_H
