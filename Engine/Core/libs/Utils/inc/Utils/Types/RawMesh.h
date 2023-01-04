//
// Created by Monika on 24.03.2022.
//

#ifndef SRENGINE_RAWMESH_H
#define SRENGINE_RAWMESH_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Common/Vertices.hpp>

namespace Assimp {
    class Importer;
}

class aiScene;

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS::Types {
    class SR_DLL_EXPORT RawMesh : public IResource {
        using CallbackFn = std::function<bool(const aiScene*)>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;

    private:
        RawMesh();
        ~RawMesh() override;

    public:
        static RawMesh *Load(const SR_UTILS_NS::Path &path);

    public:
        bool Access(const CallbackFn& fn) const;
        uint32_t GetMeshesCount() const;
        std::string GetGeometryName(uint32_t id) const;

        std::vector<SR_UTILS_NS::Vertex> GetVertices(uint32_t id) const;
        std::vector<uint32_t> GetIndices(uint32_t id) const;

        SR_NODISCARD uint32_t GetVerticesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetIndicesCount(uint32_t id) const;

        SR_NODISCARD float_t GetScaleFactor() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        SR_NODISCARD bool IsAllowRevive() const override { return true; }

    protected:
        bool Reload() override;
        bool Unload() override;
        bool Load() override;

    private:
        const aiScene* m_scene;
        Assimp::Importer* m_importer;

    };
}

#endif //SRENGINE_RAWMESH_H
