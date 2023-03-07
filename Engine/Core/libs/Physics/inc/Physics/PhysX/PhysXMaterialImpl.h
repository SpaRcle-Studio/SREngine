//
// Created by innerviewer on 3/4/2023.
//

#ifndef SRENGINE_PHYSXMATERIALIMPL_H
#define SRENGINE_PHYSXMATERIALIMPL_H

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
        bool Init(PhysicsMaterial* pMaterial) override;

        SR_NODISCARD physx::PxMaterial* GetHandle() const noexcept { return m_material; }

    private:
        physx::PxMaterial* m_material = nullptr;
    };
}

#endif //SRENGINE_PHYSXMATERIALIMPL_H
