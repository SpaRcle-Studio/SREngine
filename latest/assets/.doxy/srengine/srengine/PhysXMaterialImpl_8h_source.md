

# File PhysXMaterialImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXMaterialImpl.h**](PhysXMaterialImpl_8h.md)

[Go to the documentation of this file](PhysXMaterialImpl_8h.md)


```C++
//
// Created by innerviewer on 3/4/2023.
//

#ifndef SR_ENGINE_PHYSXMATERIALIMPL_H
#define SR_ENGINE_PHYSXMATERIALIMPL_H

#include <Physics/PhysicsMaterialImpl.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;
}

namespace SR_PTYPES_NS {
    class PhysicsMaterial;

    class PhysXMaterialImpl : public PhysicsMaterialImpl {
        using Super = PhysicsMaterialImpl;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
    public:
        explicit PhysXMaterialImpl(LibraryPtr pLibrary);
        ~PhysXMaterialImpl() override;

    public:
        bool Init() override;
        bool ReInit();
        void DeInit() override;

    public:
        void SetMaterial(PhysicsMaterial* pMaterial) override { m_material = pMaterial; }

    public:
        SR_NODISCARD void* GetHandle() override { return m_pxMaterial; }

    private:
        physx::PxMaterial* m_pxMaterial = nullptr;
        PhysicsMaterial* m_material = nullptr;

        physx::PxPhysics* m_physics = nullptr;
    };
}

#endif //SR_ENGINE_PHYSXMATERIALIMPL_H
```


