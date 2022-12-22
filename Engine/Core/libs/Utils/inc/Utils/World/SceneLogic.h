//
// Created by Monika on 22.12.2022.
//

#ifndef SRENGINE_SCENELOGIC_H
#define SRENGINE_SCENELOGIC_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_WORLD_NS {
    class Scene;

    class SceneLogic : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        using ScenePtr = SR_HTYPES_NS::SafePtr<Scene>;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using GameObjects = std::vector<GameObjectPtr>;

    public:
        explicit SceneLogic(const ScenePtr& scene);
        ~SceneLogic() override = default;

    public:
        virtual void Update(float_t dt) { }
        virtual void Destroy() { }

        virtual bool Reload() { return true; }

        virtual bool Save(const Path& path) { return false; }

    protected:
        ScenePtr m_scene;

    };
}

#endif //SRENGINE_SCENELOGIC_H
