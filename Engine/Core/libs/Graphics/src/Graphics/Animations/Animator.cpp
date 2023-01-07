//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/Animator.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Animator);

    Animator::~Animator() {
        for (auto&& [timePoint, keys] : m_timeline) {
            for (auto&& key : keys) {
                delete key;
            }
        }

        m_timeline.clear();
    }

    SR_UTILS_NS::Component* Animator::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pController = new Animator();
        return pController;
    }

    SR_UTILS_NS::Component* Animator::CopyComponent() const {
        auto&& pController = new Animator();
        return pController;
    }

    SR_HTYPES_NS::Marshal::Ptr Animator::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }

    void Animator::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }

    void Animator::Update(float_t dt) {
        auto&& pParent = dynamic_cast<SR_UTILS_NS::GameObject*>(GetParent());
        if (!pParent) {
            return;
        }

        TimePoint* pPrevTimePoint = nullptr;

        for (auto&& timePoint : m_timeline) {
            auto&& [time, keys] = timePoint;

            if (m_time > time) {
                pPrevTimePoint = &timePoint;
                continue;
            }

            const float_t interval = pPrevTimePoint ? (m_time - pPrevTimePoint->first) / time : 1.f;

            for (auto&& key : keys) {
                key->Update(interval, pParent);
            }

            break;
        }

        m_time += dt / 1000.f;
        m_time = SR_CLAMP(m_time, m_duration, 0.f);

        if (SR_EQUALS(m_time, m_duration)) {
            m_time = 0.f;
        }

        Super::Update(dt);
    }

    void Animator::OnAttached() {
        m_timeline.emplace_back(0.f, Animator::Keys {
            new TranslationKey(SR_MATH_NS::FVector3(0, 1, 0))
        });

        m_timeline.emplace_back(0.5f, Animator::Keys {
            new TranslationKey(SR_MATH_NS::FVector3(0, 2, 0))
        });

        m_timeline.emplace_back(1.5f, Animator::Keys {
            new TranslationKey(SR_MATH_NS::FVector3(2, 2, 0))
        });

        m_timeline.emplace_back(2.5f, Animator::Keys {
            new TranslationKey(SR_MATH_NS::FVector3(2, 2, 2))
        });

        m_timeline.emplace_back(3.5f, Animator::Keys {
            new TranslationKey(SR_MATH_NS::FVector3(0, 1, 0))
        });

        m_duration = 0.f;

        for (auto&& [time, keys] : m_timeline) {
            m_duration = SR_MAX(m_duration, time);
        }

        Super::OnAttached();
    }
}