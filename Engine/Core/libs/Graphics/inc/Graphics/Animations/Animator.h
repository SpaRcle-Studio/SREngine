//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATOR_H
#define SRENGINE_ANIMATOR_H

#include <Utils/ECS/Component.h>
#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/AnimationGraph.h>
#include <Graphics/Animations/AnimationStateMachine.h>

namespace SR_ANIMATIONS_NS {
    class AnimationClip;
    class AnimationChannel;

    class Animator : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Animator);
        using Super = SR_UTILS_NS::Component;
    protected:
        ~Animator() override;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD Component* CopyComponent() const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

        void FixedUpdate() override;
        void Update(float_t dt) override;

        void OnAttached() override;
        void OnDestroy() override;

        void Start() override;

    private:
        void UpdateInternal(float_t dt);

    public:
        float_t m_weight = 1.f;

    private:
        bool m_sync = false;
        bool m_allowOverride = true;

        AnimationPose* m_workingPose = nullptr;
        AnimationPose* m_staticPose = nullptr;

        AnimationGraph* m_graph = nullptr;

        Skeleton* m_skeleton = nullptr;

    };
}

#endif //SRENGINE_ANIMATOR_H
