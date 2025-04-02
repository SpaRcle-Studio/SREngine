

# File SceneUpdater.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**SceneUpdater.h**](SceneUpdater_8h.md)

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


