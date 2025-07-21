

# File Animator.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**Animator.h**](Animator_8h.md)

[Go to the documentation of this file](Animator_8h.md)


```C++
//
// Created by Monika on 07.01.2023.
//

#ifndef SR_ENGINE_ANIMATOR_H
#define SR_ENGINE_ANIMATOR_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/AnimationGraph.h>
#include <Graphics/Animations/AnimationStateMachine.h>

namespace SR_ANIMATIONS_NS {
    class AnimationClip;
    class AnimationChannel;

    class Animator : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        ~Animator() override;

    public:
        void FixedUpdate() override;
        void Update(float_t dt) override;

        void OnAttached() override;
        void OnDestroy() override;

        void Start() override;

        void SetGraph(const SR_UTILS_NS::Path& path);

        SR_NODISCARD SR_UTILS_NS::Path GetGraphPath() const noexcept;
        SR_NODISCARD AnimationGraph* GetGraph() const noexcept { return m_graph; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Skeleton>& GetSkeleton() noexcept { return m_skeleton; }

    private:
        void UpdateInternal(float_t dt);

    private:
        uint32_t m_frameRate = 1;
        float_t m_tolerance = 0.1f;
        bool m_sync = false;
        bool m_fpsCompensation = false;

        SR_VIRTUAL_PROPERTY

        AnimationGraph* m_graph = nullptr;

        SR_HTYPES_NS::SharedPtr<Skeleton> m_skeleton;

    };
}

#endif //SR_ENGINE_ANIMATOR_H
```


