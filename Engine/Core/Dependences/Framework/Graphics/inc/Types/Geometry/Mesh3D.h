//
// Created by Nikita on 01.06.2021.
//

#ifndef GAMEENGINE_MESH3D_H
#define GAMEENGINE_MESH3D_H

#include <Types/Geometry/IndexedMesh.h>

namespace SR_GRAPH_NS::Memory {
    class MeshAllocator;
}

namespace SR_GRAPH_NS::Types {
    class Mesh3D final : public IndexedMesh {
        friend class Memory::MeshAllocator;
    private:
        explicit Mesh3D(const std::string& name = "UnnamedMesh3D")
            : IndexedMesh(MeshType::Static, name)
        {
            /// override component
            Component::Init<Mesh3D>();
        }

        ~Mesh3D() override = default;

    public:
        typedef Vertices::Mesh3DVertex VertexType;

    public:
        IResource* Copy(IResource* destination) const override;

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    private:
        void UpdateUBO() override;
        bool Calculate() override;
        bool FreeVideoMemory() override;
        void DrawVulkan() override;
        void DrawOpenGL() override;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SR_UTILS_NS::SavableFlags flags) const override;

    };
}

#endif //GAMEENGINE_MESH3D_H
