//
// Created by Nikita on 01.06.2021.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_3D_H
#define SR_ENGINE_GRAPHICS_MESH_3D_H

#include <Utils/Types/IRawMeshHolder.h>
#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class Mesh3D final : public MeshComponent, public SR_HTYPES_NS::IRawMeshHolder {
        using Super = MeshComponent;
        SR_REGISTER_NEW_COMPONENT(Mesh3D, 1002);
    public:
        Mesh3D();

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        SR_NODISCARD bool InitializeEntity() noexcept override;

        void UseMaterial() override;
        void UseModelMatrix() override;

        void OnRawMeshChanged() override;
        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource) override;

        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD std::string GetMeshIdentifier() const override;

    private:
        bool Calculate() override;
        void Draw() override;

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_3D_H
