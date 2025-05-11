

# File PhysicsMaterialImpl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysicsMaterialImpl.h**](PhysicsMaterialImpl_8h.md)

[Go to the documentation of this file](PhysicsMaterialImpl_8h.md)


```C++
//
// Created by innerviewer on 3/4/2023.
//

#ifndef SR_ENGINE_PHYSICSMATERIALIMPL_H
#define SR_ENGINE_PHYSICSMATERIALIMPL_H

#include <Physics/macros.h>

#include <Utils/Common/NonCopyable.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;
}

namespace SR_PTYPES_NS {
    class PhysicsMaterialImpl : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
    protected:
        explicit PhysicsMaterialImpl(LibraryPtr pLibrary)
            : Super()
            , m_library(pLibrary)
        { }

    public:
        virtual bool Init() = 0;
        virtual void DeInit() = 0;

        template<typename T> SR_NODISCARD T* GetLibrary() const {
            if (auto&& pLibrary = dynamic_cast<T*>(m_library)) {
                return pLibrary;
            }

            SRHalt("Failed to cast library!");

            return nullptr;
        }

        SR_NODISCARD virtual void* GetHandle() = 0;

        virtual void SetMaterial(PhysicsMaterial* pMaterial) = 0;

    private:
        SR_PHYSICS_NS::LibraryImpl* m_library = nullptr;
    };
}

#endif //SR_ENGINE_PHYSICSMATERIALIMPL_H
```


