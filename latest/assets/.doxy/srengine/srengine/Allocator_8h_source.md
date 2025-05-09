

# File Allocator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Memory**](dir_a7ee2ebe23408af25e9b8f5a8e783a39.md) **>** [**Allocator.h**](Allocator_8h.md)

[Go to the documentation of this file](Allocator_8h.md)


```C++
//
// Created by Monika on 27.04.2025.
//

#ifndef SR_ENGINE_UTILS_MEMORY_ALLOCATOR_H
#define SR_ENGINE_UTILS_MEMORY_ALLOCATOR_H

void* SRMalloc(SR_UTILS_NS::SizeType size);
void* SRReAlloc(void* pMemory, SR_UTILS_NS::SizeType size);
void SRFree(void* pMemory);

template<typename T, typename... Args> T* SRNew(Args&& ...args) {
    void* pMemory = SRMalloc(sizeof(T));
    T* pObject = new(pMemory) T(Forward<Args>(args)...);
    if constexpr (requires(T t) { t.InitializeClass(); }) {
        pObject->InitializeClass();
    }
    return pObject;
}

template<typename T> void SRDelete(T* pObject) {
    if constexpr (requires(T t) { t.DeinitializeClass(); }) {
        pObject->DeinitializeClass();
    }
    pObject->~T();
    SRFree(pObject);
}

void* operator new(SR_UTILS_NS::SizeType size);
void operator delete(void* pMemory) noexcept;
void* operator new[](SR_UTILS_NS::SizeType size);
void operator delete[](void* pMemory) noexcept;

#else
    #error "Allocator.h already included!"
#endif //SR_ENGINE_UTILS_MEMORY_ALLOCATOR_H
```


