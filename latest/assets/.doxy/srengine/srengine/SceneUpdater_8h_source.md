

# File SceneUpdater.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneUpdater.h**](SceneUpdater_8h.md)

[Go to the documentation of this file](SceneUpdater_8h.md)


```C++
//
// Created by Monika on 18.12.2022.
//

#ifndef SR_ENGINE_UTILS_SCENE_UPDATER_H
#define SR_ENGINE_UTILS_SCENE_UPDATER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Time.h>

namespace SR_UTILS_NS {
    class Component;
}

namespace SR_WORLD_NS {
    class Scene;

    class SceneUpdater : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        explicit SceneUpdater(Scene* pScene);

    public:
        void Build(bool isPaused);
        void Update(float_t dt, bool isPaused);
        void FixedUpdate(bool isPaused);
        void LateUpdate(bool isPaused);

        void SetDirty();

        void RegisterComponent(SR_UTILS_NS::Component* pComponent);
        void UnRegisterComponent(SR_UTILS_NS::Component* pComponent);

        SR_NODISCARD SR_UTILS_NS::TimePointType GetLastBuildTime() const { return m_lastBuildTimePoint; }

    private:
        std::recursive_mutex m_mutex;
        Scene* m_scene = nullptr;

        SR_UTILS_NS::TimePointType m_lastBuildTimePoint;
        bool m_dirty = false;

        uint32_t m_componentsPoolSize = 0;
        std::vector<SR_UTILS_NS::Component*> m_updatableComponents;
        std::list<uint32_t> m_freeComponentIds;

    };
}

#endif //SR_ENGINE_UTILS_SCENE_UPDATER_H
```


