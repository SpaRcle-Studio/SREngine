

# File Skeleton.h

[**File List**](files.md) **>** [**Animations**](dir_417ea13389e3cbd1256e515e0204a036.md) **>** [**Skeleton.h**](Skeleton_8h.md)

[Go to the documentation of this file](Skeleton_8h.md)


```C++
//
// Created by Igor on 08/12/2022.
//

#ifndef SR_ENGINE_SKELETON_H
#define SR_ENGINE_SKELETON_H

#include <Graphics/Animations/Bone.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Skeleton>;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;

    public:
        ~Skeleton() override;

    public:
        void Update(float_t dt) override;

        void OnPostLoad() override;

        void OnAttached() override;
        void OnDestroy() override;

        bool ReCalculateSkeleton();
        void CalculateMatrices();

        void ResetSkeleton();

        void SetOptimizedBones(const ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint16_t>& bones);
        void SetBonesOffsets(const std::vector<SR_MATH_NS::Matrix4x4>& offsets);

        Bone* AddBone(Bone* pParent, SR_UTILS_NS::StringAtom name, bool recalculate);
        SR_NODISCARD const Bone* GetRootBone() const noexcept { return m_rootBone.Get(); }
        SR_NODISCARD Bone* GetRootBone() noexcept { return m_rootBone.Get(); }

        const SR_MATH_NS::Matrix4x4& GetMatrixByIndex(uint16_t index) noexcept;
        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetMatrices() noexcept;
        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetOffsets() noexcept { return m_skeletonOffsets; }
        SR_UTILS_NS::Transform* GetTransformByIndex(uint16_t index) noexcept;
        SR_NODISCARD const std::vector<Bone*>& GetBones() const noexcept { return m_bonesByIndex; };
        SR_NODISCARD Bone* TryGetBone(SR_UTILS_NS::StringAtom name);
        SR_NODISCARD Bone* GetBone(SR_UTILS_NS::StringAtom name);
        SR_NODISCARD Bone* GetBoneByIndex(uint16_t index) const;
        SR_NODISCARD uint64_t GetBoneIndex(SR_UTILS_NS::StringAtom name);
        SR_NODISCARD bool IsDebugEnabled() const noexcept { return m_debugEnabled; }
        SR_NODISCARD bool IsDirtyMatrices() const noexcept { return m_dirtyMatrices; }
        SR_NODISCARD const ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint16_t>& GetOptimizedBones() const noexcept { return m_optimizedBones; }
        void SetDebugEnabled(bool enabled) { m_debugEnabled = enabled; }

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

    private:
        void UpdateDebug();
        void DisableDebug();

    private:
        ska::flat_hash_map<Bone*, uint64_t> m_debugLines;
        ska::flat_hash_map<SR_UTILS_NS::StringAtom, Bone*> m_bonesByName;

        std::vector<Bone*> m_bonesByIndex;

        ska::flat_hash_map<SR_UTILS_NS::StringAtom, uint16_t> m_optimizedBones;

        std::vector<SR_MATH_NS::Matrix4x4> m_matrices;
        std::vector<SR_MATH_NS::Matrix4x4> m_skeletonOffsets;

    private:
        Bone::Ptr m_rootBone = nullptr;
        bool m_debugEnabled = false;
        bool m_dirtyMatrices = false;

    };
}

#endif //SR_ENGINE_SKELETON_H
```


