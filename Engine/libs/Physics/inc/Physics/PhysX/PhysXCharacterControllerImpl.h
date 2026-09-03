//
// Created by Monika on 26.03.2026.
//

#ifndef SR_ENGINE_PHYSX_CHARACTER_CONTROLLER_IMPL_H
#define SR_ENGINE_PHYSX_CHARACTER_CONTROLLER_IMPL_H

#include <Physics/CharacterController.h>

namespace SR_PHYSICS_NS {
    class PhysXCharacterControllerImpl : public CharacterControllerImpl {
        using Super = CharacterControllerImpl;
    public:
        SR_NODISCARD void* GetHandle() const noexcept override { return m_pxController; }

        void SetHandle(void* handle) override {
            m_userData.pUserData = m_controller;
            m_userData.type = RigidActorUserData::Type::CharacterController;

            m_pxController = static_cast<physx::PxController*>(handle);
            m_pxController->setUserData(&m_userData);
            m_pxController->getActor()->userData = &m_userData;
        }

        CharacterControllerCollisionFlags Move(const SR_MATH_NS::FVector3& displacement,
            float_t skinWidth, float_t deltaTime) override;

        SR_NODISCARD bool IsGrounded() const override;

        void Synchronize() override;

    private:
        physx::PxController* m_pxController = nullptr;
        RigidActorUserData m_userData;

        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;

    };
}

#endif //SR_ENGINE_PHYSX_CHARACTER_CONTROLLER_IMPL_H
