

# File Bone.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**Bone.h**](Bone_8h.md)

[Go to the documentation of this file](Bone_8h.md)


```C++
//
// Created by Monika on 19.08.2021.
//

#ifndef SR_ENGINE_BONE_H
#define SR_ENGINE_BONE_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

#include <Graphics/Types/Mesh.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;
    class BoneComponent;

    struct Bone final : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<Bone> {
        SR_CLASS()
    public:
        Bone()
            : SR_HTYPES_NS::SharedPtr<Bone>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

        void SetSkeleton(Skeleton* pSkeleton) {
            this->pSkeleton = pSkeleton;
        }

        bool Initialize();
        void InitTreeIfNeed();

    private:
        void InitTree(Bone* pParent);

    public:
        SR_UTILS_NS::StringAtom name;
        std::vector<Bone::Ptr> bones;

        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject> gameObject;
        Bone* pParent = nullptr;
        Bone* pRoot = nullptr;
        bool hasError = false;
        Skeleton* pSkeleton = nullptr;

    };
}

#endif //SR_ENGINE_BONE_H
```


