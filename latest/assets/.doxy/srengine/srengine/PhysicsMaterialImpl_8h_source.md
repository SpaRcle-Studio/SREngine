

# File PhysicsMaterialImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysicsMaterialImpl.h**](PhysicsMaterialImpl_8h.md)

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


