

# File SceneAllocator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneAllocator.h**](SceneAllocator_8h.md)

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

    class SR_COMMON_DLL_API SceneAllocator : public SR_UTILS_NS::Singleton<SceneAllocator> {
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


