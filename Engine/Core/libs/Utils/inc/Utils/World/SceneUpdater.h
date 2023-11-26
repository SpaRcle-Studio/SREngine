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
        void Update(float_t dt);
        void FixedUpdate();

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
