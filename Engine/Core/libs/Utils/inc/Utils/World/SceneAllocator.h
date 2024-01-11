//
// Created by Monika on 23.08.2022.
//

#ifndef SR_ENGINE_SCENEALLOCATOR_H
#define SR_ENGINE_SCENEALLOCATOR_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/SafePointer.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_WORLD_NS {
    class Scene;

    class SR_DLL_EXPORT SceneAllocator : public SR_UTILS_NS::Singleton<SceneAllocator> {
        SR_REGISTER_SINGLETON(SceneAllocator)
        typedef std::function<Scene*(void)> Allocator;
        using ScenePtr = Types::SafePtr<Scene>;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
    protected:
        ~SceneAllocator() override = default;

    public:
        bool Init(const Allocator& allocator);
        ScenePtr Allocate();

    private:
        Allocator m_allocator;

    };
}

#endif //SR_ENGINE_SCENEALLOCATOR_H
