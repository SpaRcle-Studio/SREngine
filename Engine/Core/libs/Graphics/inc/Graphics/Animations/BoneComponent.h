//
// Created by Monika on 28.07.2023.
//

#ifndef SR_ENGINE_BONECOMPONENT_H
#define SR_ENGINE_BONECOMPONENT_H

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/Component.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;

    class BoneComponent : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(BoneComponent);
        using Super = SR_UTILS_NS::Component;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    public:
        BoneComponent();

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* pDataStorage);

    public:
        SR_NODISCARD Component* CopyComponent() const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

        void OnMatrixDirty() override;

        void Initialize(Skeleton* pSkeleton, uint16_t boneIndex);

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

    private:
        uint16_t m_boneIndex = 0;
        SR_UTILS_NS::EntityRef m_skeleton;

    };
}

#endif //SR_ENGINE_BONECOMPONENT_H
