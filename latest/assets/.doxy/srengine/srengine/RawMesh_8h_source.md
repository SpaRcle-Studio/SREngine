

# File RawMesh.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**RawMesh.h**](RawMesh_8h.md)

[Go to the documentation of this file](RawMesh_8h.md)


```C++
//
// Created by Monika on 24.03.2022.
//

#ifndef SR_ENGINE_RAWMESH_H
#define SR_ENGINE_RAWMESH_H

#include <Utils/Resources/IResource.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Map.h>
#include <Utils/Common/Vertices.h>
#include <Utils/Math/Matrix4x4.h>

#ifdef SR_UTILS_ASSIMP
namespace Assimp {
    class Importer;
}

class aiScene;
class aiAnimation;
class aiMesh;
#endif

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_HTYPES_NS {
    struct RawMeshParams {
        bool animation = false;
        bool convexHull = false;

        bool operator==(const RawMeshParams& rhs) const {
            return animation == rhs.animation && convexHull == rhs.convexHull;
        }
    };

    class SR_DLL_EXPORT RawMesh : public IResource {
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
        using Ptr = RawMesh*;
        using Hash = uint64_t;
    private:
        RawMesh();
        ~RawMesh() override;

    public:
        static RawMesh* Load(const SR_UTILS_NS::Path &path, RawMeshParams params);
        static RawMesh* Load(const SR_UTILS_NS::Path &path);

    public:
        void ComputeConvexHull();

        SR_NODISCARD uint32_t GetMeshesCount() const;
        SR_NODISCARD std::string_view GetGeometryName(uint32_t id) const;

        SR_NODISCARD std::vector<SR_UTILS_NS::Vertex> GetVertices(uint32_t id) const;
        SR_NODISCARD const std::vector<uint32_t>& GetIndices(uint32_t id) const;
        SR_NODISCARD const ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint32_t>& GetBones(uint32_t id) const;
        SR_NODISCARD const ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint16_t>& GetOptimizedBones() const { return m_optimizedBones; }
        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetBoneOffset(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetBoneTransform(uint32_t index) const;
        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetBoneTransform(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD uint32_t GetBoneIndex(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetBoneOffsets() const { return m_boneOffsets; }

        SR_NODISCARD uint32_t GetVerticesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetIndicesCount(uint32_t id) const;
        SR_NODISCARD uint32_t GetAnimationsCount() const;
        SR_NODISCARD std::vector<SR_UTILS_NS::StringAtom> GetAnimationNames() const;
        SR_UTILS_NS::Path InitializeResourcePath() const override;
        SR_NODISCARD int32_t GetMeshId(SR_UTILS_NS::StringAtom name) const;

        SR_NODISCARD float_t GetScaleFactor() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

    #ifdef SR_UTILS_ASSIMP
        SR_NODISCARD const aiScene* GetAssimpScene() const noexcept { return m_scene; }
    #endif

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        void NormalizeWeights();
        void CalculateBones();
        void OptimizeSkeleton();
        void CalculateOffsets();
        void CalculateTransforms();
        void CalculateAnimations();

    #ifdef SR_UTILS_ASSIMP
        uint32_t NormalizeWeights(const aiMesh* pMesh);
    #endif

    private:
        std::vector<ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint32_t>> m_bones;
        ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint16_t> m_optimizedBones;

        ska::flat_hash_map<SR_UTILS_NS::StringAtom, SR_MATH_NS::Matrix4x4> m_boneOffsetsMap;
        ska::flat_hash_map<SR_UTILS_NS::StringAtom, SR_MATH_NS::Matrix4x4> m_boneTransformsMap;

        std::vector<SR_MATH_NS::Matrix4x4> m_boneOffsets;
        std::vector<SR_MATH_NS::Matrix4x4> m_boneTransforms;

        mutable std::vector<std::vector<uint32_t>> m_indices;

        RawMeshParams m_params;

        bool m_fromCache = false;

    #ifdef SR_UTILS_ASSIMP
        ska::flat_hash_map<Hash, aiAnimation*> m_animations;
        const aiScene* m_scene = nullptr;
        Assimp::Importer* m_importer = nullptr;
    #endif

    };
}

template<> struct SR_UTILS_NS::SRHash<SR_HTYPES_NS::RawMeshParams> {
    size_t operator()(SR_HTYPES_NS::RawMeshParams const& params) const {
        std::size_t res = 0;

        std::hash<bool> hBool;

        res ^= hBool(params.animation) + 0x9e3779b9 + (res << 6u) + (res >> 2u);
        res ^= hBool(params.convexHull) + 0x9e3779b9 + (res << 6u) + (res >> 2u);

        return res;
    }
};

#endif //SR_ENGINE_RAWMESH_H
```


