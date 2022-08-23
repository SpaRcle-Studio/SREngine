//
// Created by Monika on 23.08.2022.
//

#ifndef SRENGINE_SCENEALLOCATOR_H
#define SRENGINE_SCENEALLOCATOR_H

#include <Utils/Types/SharedPtr.h>

namespace SR_WORLD_NS {
    class SR_DLL_EXPORT SceneAllocator : public SR_UTILS_NS::Singleton<SceneAllocator> {
        friend class SR_UTILS_NS::Singleton<SceneAllocator>;
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

#endif //SRENGINE_SCENEALLOCATOR_H
