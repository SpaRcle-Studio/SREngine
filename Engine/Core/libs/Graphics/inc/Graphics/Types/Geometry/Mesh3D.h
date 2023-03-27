//
// Created by Nikita on 01.06.2021.
//

#ifndef SRENGINE_GRAPHICS_MESH3D_H
#define SRENGINE_GRAPHICS_MESH3D_H

#include <Utils/Types/IRawMeshHolder.h>
#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class Mesh3D final : public MeshComponent, public SR_HTYPES_NS::IRawMeshHolder {
        using Super = MeshComponent;
        SR_ENTITY_SET_VERSION(1001);
        SR_INITIALIZE_COMPONENT(Mesh3D);
    public:
        Mesh3D();

    private:
        ~Mesh3D() override = default;

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void UseMaterial() override;
        void UseModelMatrix() override;

        void OnRawMeshChanged() override;

        SR_NODISCARD bool IsCanCalculate() const override;
        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD std::string GetMeshIdentifier() const override;

        SR_NODISCARD Component* CopyComponent() const override;

    private:
        bool Calculate() override;
        void Draw() override;

    };
}

#endif //SRENGINE_GRAPHICS_MESH3D_H
