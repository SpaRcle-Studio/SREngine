

# File Allocator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Memory**](dir_6c2eca2af3b09130c469ec03e9c2b107.md) **>** [**Allocator.h**](Allocator_8h.md)

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


