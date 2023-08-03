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
class aiAnimation;

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT RawMesh : public IResource {
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using Ptr = RawMesh*;
        using Hash = uint64_t;
    private:
        RawMesh();
        ~RawMesh() override;

    public:
        static RawMesh* Load(const SR_UTILS_NS::Path &path, bool animation);
        static RawMesh* Load(const SR_UTILS_NS::Path &path);

    public:
        uint32_t GetMeshesCount() const;
        std::string GetGeometryName(uint32_t id) const;

        std::vector<SR_UTILS_NS::Vertex> GetVertices(uint32_t id) const;
        std::vector<uint32_t> GetIndices(uint32_t id) const;
        const ska::flat_hash_map<uint64_t, uint32_t>& GetBones(uint32_t id) const;
        const ska::flat_hash_map<Hash, uint16_t>& GetOptimizedBones() const { return m_optimizedBones; }
        const SR_MATH_NS::Matrix4x4& GetBoneOffset(uint64_t hashName) const;
        const std::vector<SR_MATH_NS::Matrix4x4>& GetBoneOffsets() const { return m_boneOffsets; }

        SR_NODISCARD uint32_t GetVerticesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetIndicesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetAnimationsCount() const;
        SR_UTILS_NS::Path InitializeResourcePath() const override;

        SR_NODISCARD float_t GetScaleFactor() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        SR_NODISCARD const aiScene* GetAssimpScene() const noexcept { return m_scene; }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        void CalculateBones();
        void OptimizeSkeleton();
        void CalculateOffsets();
        void CalculateAnimations();

    private:
        ska::flat_hash_map<Hash, aiAnimation*> m_animations;

        std::vector<ska::flat_hash_map<Hash, uint32_t>> m_bones;
        ska::flat_hash_map<Hash, uint16_t> m_optimizedBones;

        ska::flat_hash_map<Hash, SR_MATH_NS::Matrix4x4> m_boneOffsetsMap;
        std::vector<SR_MATH_NS::Matrix4x4> m_boneOffsets;

        bool m_asAnimation = false;
        const aiScene* m_scene = nullptr;
        bool m_fromCache = false;
        Assimp::Importer* m_importer = nullptr;

    };
}

#endif //SRENGINE_RAWMESH_H
