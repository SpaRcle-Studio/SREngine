//
// Created by Monika on 26.03.2026.
//

#include <Physics/CharacterController.h>
#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsWorld.h>

#include <Utils/World/Scene.h>
#include <Utils/FileSystem/PathDataAccessor.h>

#include <Codegen/CharacterController.generated.hpp>

namespace SR_PHYSICS_NS {
    void CharacterController::OnEnable() {
        SR_TRACY_ZONE;
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Register(this);
        }
        Super::OnEnable();
    }

    void CharacterController::OnDisable() {
        SR_TRACY_ZONE;
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }
        Super::OnDisable();
    }

    const CharacterController::PhysicsScenePtr& CharacterController::GetPhysicsScene() const {
        if (!m_physicsScene) {
            auto&& pScene = TryGetScene();
            if (!pScene) {
                static PhysicsScenePtr empty;
                return empty;
            }

            m_physicsScene = pScene->GetDataStorage().GetValue<PhysicsScenePtr>();
        }
        return m_physicsScene;
    }

    bool CharacterController::InitController() {
        if (m_impl) {
            SRHalt("CharacterController::InitController() : controller already initialized!");
            return false;
        }

        if (!m_materialData) {
            m_materialData = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetDefaultMaterial();
        }

        if (auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D)) {
            m_impl = pLibrary->CreateCharacterControllerImpl();
            if (m_impl) {
                m_impl->SetCharacterController(this);
            }
        }

        if (!m_impl) {
            SR_ERROR("Failed to create character controller implementation!");
        }
        return m_impl;
    }

    void CharacterController::OnDestroy() {
        SR_TRACY_ZONE;
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }
        Super::OnDestroy();
    }

    void CharacterController::SetMaterial(const SR_UTILS_NS::Path& path) {
        if (m_material == path) {
            return;
        }

        m_material = path;

        if (m_materialData) {
            m_materialData->RemoveUsePoint();
            m_materialData = nullptr;
        }

        if (!m_material.IsEmpty()) {
            if ((m_materialData = SR_UTILS_NS::Asset::Load<SR_PTYPES_NS::PhysicsMaterial>(m_material))) {
                m_materialData->AddUsePoint();
            }
        }
    }

    void CharacterController::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            pTransform->GetMatrix().Decompose(m_translation, m_rotation, m_scale);
        }

        SetMatrixDirty(true);
        Super::OnMatrixDirty();
    }

    bool CharacterController::UpdateMatrix(bool force) {
        SR_TRACY_ZONE;

        if ((!force && !IsMatrixDirty())) {
            return false;
        }

        if (m_impl) {
            m_impl->UpdateMatrix(force);
        }

        SetMatrixDirty(false);

        return true;
    }

    CharacterControllerCollisionFlags CharacterController::Move(const SR_MATH_NS::FVector3& displacement, float_t skinWidth, float_t deltaTime) {
        if (m_impl) {
            return m_impl->Move(displacement, skinWidth, deltaTime);
        }
        return CharacterControllerCollisionFlags::None;
    }
}