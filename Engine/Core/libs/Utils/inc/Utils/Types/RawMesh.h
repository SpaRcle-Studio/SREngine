//
// Created by Monika on 24.03.2022.
//

#ifndef SRENGINE_RAWMESH_H
#define SRENGINE_RAWMESH_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Map.h>
#include <Utils/Common/Vertices.hpp>
#include <Utils/Math/Matrix4x4.h>

namespace Assimp {
    class Importer;
}

class aiScene;

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS::Types {
    class SR_DLL_EXPORT RawMesh : public IResource {
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;

    private:
        RawMesh();
        ~RawMesh() override;

    public:
        static RawMesh *Load(const SR_UTILS_NS::Path &path);

    public:
        uint32_t GetMeshesCount() const;
        std::string GetGeometryName(uint32_t id) const;

        std::vector<SR_UTILS_NS::Vertex> GetVertices(uint32_t id) const;
        std::vector<uint32_t> GetIndices(uint32_t id) const;
        const ska::flat_hash_map<uint64_t, uint32_t>& GetBones(uint32_t id) const;
        const SR_MATH_NS::Matrix4x4& GetBoneOffset(uint64_t hashName) const;

        SR_NODISCARD uint32_t GetVerticesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetIndicesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetAnimationsCount() const;

        SR_NODISCARD float_t GetScaleFactor() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        SR_NODISCARD const aiScene* GetAssimpScene() const noexcept { return m_scene; }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        void CalculateBones();

    private:
        ska::flat_hash_map<uint64_t, SR_MATH_NS::Matrix4x4> m_boneOffsets;
        std::vector<ska::flat_hash_map<uint64_t, uint32_t>> m_bones;

        const aiScene* m_scene;
        Assimp::Importer* m_importer;

    };
}

#endif //SRENGINE_RAWMESH_H
