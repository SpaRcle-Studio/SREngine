

# File SceneAllocator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**SceneAllocator.h**](SceneAllocator_8h.md)

[Go to the documentation of this file](SceneAllocator_8h.md)


```C++
//
// Created by Monika on 23.08.2022.
//

#ifndef SR_ENGINE_SCENE_ALLOCATOR_H
#define SR_ENGINE_SCENE_ALLOCATOR_H

#include <Utils/Types/SharedPtr.h>

namespace SR_WORLD_NS {
    class Scene;

    class SR_DLL_EXPORT SceneAllocator : public SR_UTILS_NS::Singleton<SceneAllocator> {
        SR_REGISTER_SINGLETON(SceneAllocator)
        using ScenePtr = SR_HTYPES_NS::SharedPtr<Scene>;
        typedef std::function<ScenePtr(void)> Allocator;

    protected:
        ~SceneAllocator() override = default;

    public:
        bool Init(const Allocator& allocator);
        SR_NODISCARD ScenePtr Allocate() const;

    private:
        Allocator m_allocator;

    };
}

#endif //SR_ENGINE_SCENE_ALLOCATOR_H
```


