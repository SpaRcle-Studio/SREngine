//
// Created by innerviewer on 3/4/2023.
//

#include <Physics/PhysX/PhysXMaterialImpl.h>

namespace SR_PTYPES_NS {
    PhysXMaterialImpl::PhysXMaterialImpl(LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXMaterialImpl::~PhysXMaterialImpl() {
        if (m_material) {
            m_material->release();
            m_material = nullptr;
        }
    }

    bool PhysXMaterialImpl::Init(PhysicsMaterial* pMaterial){
        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        m_material = pPhysics->createMaterial(
            pMaterial->GetStaticFriction(),
            pMaterial->GetDynamicFriction(),
            pMaterial->GetBounciness()
        );

        m_material->setFrictionCombineMode(SR_PHYSICS_UTILS_NS::CombineToPxCombine(pMaterial->GetFrictionCombine()));
        m_material->setRestitutionCombineMode(SR_PHYSICS_UTILS_NS::CombineToPxCombine(pMaterial->GetBounceCombine()));

        return true;
    }

    void PhysXMaterialImpl::DeInit() {
        if (m_material) {
            m_material->release();
            m_material = nullptr;
        }
    }
}