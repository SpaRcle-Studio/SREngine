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
