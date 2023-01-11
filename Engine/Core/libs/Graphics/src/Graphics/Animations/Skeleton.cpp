//
// Created by Monika on 11.01.2023.
//

#include <Graphics/Animations/Skeleton.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Skeleton);

    Skeleton::~Skeleton() {
        m_bonesById.clear();
        m_bonesByName.clear();
        delete m_rootBone;
    }

    SR_UTILS_NS::Component* Skeleton::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new Skeleton();
        return pComponent;
    }

    SR_UTILS_NS::Component* Skeleton::CopyComponent() const {
        auto&& pComponent = new Skeleton();
        return pComponent;
    }

    SR_HTYPES_NS::Marshal::Ptr Skeleton::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }

    void Skeleton::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }

    void Skeleton::OnLoaded() {
        Super::OnLoaded();
    }
}