//
// Created by innerviewer on 3/4/2023.
//

#include <Physics/PhysX/PhysXMaterialImpl.h>

namespace SR_PTYPES_NS {
    PhysXMaterialImpl::PhysXMaterialImpl(LibraryPtr pLibrary)
        : Super(pLibrary)
    {
        m_physics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();
    }

    PhysXMaterialImpl::~PhysXMaterialImpl() {
        SR_TRACY_ZONE;

        if (m_pxMaterial) {
            m_pxMaterial->release();
            m_pxMaterial = nullptr;
        }
    }

    bool PhysXMaterialImpl::Init() {
        SR_TRACY_ZONE;
        if (!m_material) {
            SRHalt("PhysXMaterialImpl::Init() : no material provided.");
            return false;
        }

        m_pxMaterial = m_physics->createMaterial(
            m_material->GetStaticFriction(),
            m_material->GetDynamicFriction(),
            m_material->GetBounciness()
        );

        m_pxMaterial->setFrictionCombineMode(SR_PHYSICS_UTILS_NS::CombineToPxCombine(m_material->GetFrictionCombine()));
        m_pxMaterial->setRestitutionCombineMode(SR_PHYSICS_UTILS_NS::CombineToPxCombine(m_material->GetBounceCombine()));

        return true;
    }

    bool PhysXMaterialImpl::ReInit() {
        SR_TRACY_ZONE;

        DeInit();
        Init();

        return true;
    }

    void PhysXMaterialImpl::DeInit() {
        SR_TRACY_ZONE;

        if (m_pxMaterial) {
            m_pxMaterial->release();
            m_pxMaterial = nullptr;
        }
    }
}