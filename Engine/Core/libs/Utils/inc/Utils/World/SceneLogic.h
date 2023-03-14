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

    class SceneLogic : public SR_HTYPES_NS::SafePtr<SceneLogic> {
    public:
        using Ptr = SR_HTYPES_NS::SafePtr<SceneLogic>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<Scene>;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using GameObjects = std::vector<GameObjectPtr>;

    public:
        explicit SceneLogic(const ScenePtr& scene);
        virtual ~SceneLogic() = default;

    public:
        /// Метод всегда вернет валидную логику сцены
        static SceneLogic::Ptr CreateByExt(const ScenePtr& scene, const std::string& ext);

    public:
        SR_NODISCARD virtual bool IsDefault() const noexcept { return false; }
        SR_NODISCARD virtual bool IsDebugEnabled() const noexcept { return m_debugEnabled; }

        virtual void Update(float_t dt) { }
        virtual void Destroy() { }
        virtual void PostLoad() { }

        virtual bool Reload() { return true; }

        virtual void SetDebugEnabled(bool enabled) { m_debugEnabled = enabled; }

        virtual bool Load(const Path& path) { return false; }
        virtual bool Save(const Path& path) { return false; }

    protected:
        bool m_debugEnabled = true;
        ScenePtr m_scene;
        mutable std::recursive_mutex m_mutex;

    };
}

#endif //SRENGINE_SCENELOGIC_H
