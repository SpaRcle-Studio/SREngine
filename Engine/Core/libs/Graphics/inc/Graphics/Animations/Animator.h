//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATOR_H
#define SRENGINE_ANIMATOR_H

#include <Utils/ECS/Component.h>
#include <Graphics/Animations/AnimationKey.h>

namespace SR_ANIMATIONS_NS {
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
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void Update(float_t dt) override;

        void OnAttached() override;
        void OnDestroy() override;

    private:
        float_t m_time = 0.f;
        float_t m_duration = 0.f;

        using Keys = std::vector<AnimationKey*>;
        using TimePoint = std::pair<float_t, Keys>;
        using Timeline = std::vector<TimePoint>;

        Timeline m_timeline;

    };
}

#endif //SRENGINE_ANIMATOR_H
