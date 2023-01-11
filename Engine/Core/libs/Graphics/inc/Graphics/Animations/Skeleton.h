//
// Created by Igor on 08/12/2022.
//

#ifndef SRENGINE_SKELETON_H
#define SRENGINE_SKELETON_H

#include <Graphics/Animations/Bone.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Skeleton);
        using Super = SR_UTILS_NS::Component;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        ~Skeleton() override;

    public:
        SR_NODISCARD Component* CopyComponent() const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void OnLoaded() override;
        void OnDestroy() override;

    private:
        std::vector<Bone*> m_bonesById;
        ska::flat_hash_map<uint64_t, Bone*> m_bonesByName;

        Bone* m_rootBone = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SR_DEPRECATED AssimpSkeleton {
        std::vector<BoneComponent> bones;
    };

}

#endif //SRENGINE_SKELETON_H
