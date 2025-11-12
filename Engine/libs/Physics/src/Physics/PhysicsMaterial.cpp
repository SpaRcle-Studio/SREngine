//
// Created by innerviewer on 3/4/2023.
//

#include <Utils/Resources/ResourceManager.h>
#include <Utils/Resources/Xml.h>

#include <Physics/PhysicsMaterial.h>
#include <Physics/PhysicsMaterialImpl.h>
#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>
#include <Physics/Rigidbody.h>

#include <Codegen/PhysicsMaterial.generated.hpp>

namespace SR_PTYPES_NS {
    PhysicsMaterial::PhysicsMaterial() = default;

    PhysicsMaterial::~PhysicsMaterial() {
        ResetMaterialImpls();
    }

    void PhysicsMaterial::ResetMaterialImpls() {
        for (auto&& [libraryType, physicsMaterial] : m_implementations) {
            delete physicsMaterial;
        }

        m_implementations.clear();
    }

    void PhysicsMaterial::OnAssetLoaded() {
        SR_TRACY_ZONE;

        for (auto&& libraryType : SR_PHYSICS_NS::PhysicsLibrary::Instance().GetSupportedLibraries()) {
            auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetLibrary(libraryType);

            if (auto&& pMaterial = pLibrary->CreatePhysicsMaterial()) {
                m_implementations[libraryType] = pMaterial;
                pMaterial->SetMaterial(this);
                pMaterial->Init();
            }
        }

        for (auto&& pRigidbody : m_rigidbodies) {
            pRigidbody->SetShapeDirty(true);
        }

        Super::OnAssetLoaded();
    }

    bool PhysicsMaterial::Unload() {
        ResetMaterialImpls();
        return Super::Unload();
    }

    PhysicsMaterialImpl* PhysicsMaterial::GetMaterialImpl(LibraryType libraryType) const {
        if (auto&& pIt = m_implementations.find(libraryType); pIt != m_implementations.end()) {
            return pIt->second;
        }
        return nullptr;
    }

    void PhysicsMaterial::RemoveRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody) {
        if (auto&& pIt = m_rigidbodies.find(pRigidbody); pIt != m_rigidbodies.end()) {
            m_rigidbodies.erase(pIt);
        }
        else {
            SRHalt("PhysicsMaterial::RemoveRigidbody() : rigidbody is not found.");
        }
    }

    void PhysicsMaterial::SetRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody) {
        SRAssert(m_rigidbodies.count(pRigidbody) == 0);
        m_rigidbodies.insert(pRigidbody);
    }
}
