//
// Created by Monika on 26.03.2026.
//

#include <Physics/PhysX/PhysXCharacterControllerImpl.h>

#include <Enum/CharacterControllerCollisionFlags.hpp>

namespace SR_PHYSICS_NS {
    CharacterControllerCollisionFlags PhysXCharacterControllerImpl::Move(const SR_MATH_NS::FVector3& displacement, float_t skinWidth, float_t deltaTime) {
        if (!m_pxController) {
            return CharacterControllerCollisionFlags::None;
        }

        physx::PxControllerFilters filters = physx::PxControllerFilters();

        const auto pxDisplacement = SR_PHYSICS_UTILS_NS::FV3ToPxV3(displacement);
        const auto pxSkinWidth = skinWidth;
        const auto pxDeltaTime = deltaTime;

        const auto collisionFlags = m_pxController->move(pxDisplacement, pxSkinWidth, pxDeltaTime, filters);

        CharacterControllerCollisionFlags result = CharacterControllerCollisionFlags::None;

        if (collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_SIDES) {
            result |= CharacterControllerCollisionFlags::Sides;
        }
        if (collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_UP) {
            result |= CharacterControllerCollisionFlags::Up;
        }
        if (collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN) {
            result |= CharacterControllerCollisionFlags::Down;
        }

        return result;
    }

    void PhysXCharacterControllerImpl::Synchronize() {
        SR_TRACY_ZONE;

        auto&& pTransform = m_controller->GetTransform();
        if (!pTransform) {
            return;
        }

        // Получаем позицию и ориентацию капсулы из PhysX
        const physx::PxTransform& globalPose = m_pxController->getActor()->getGlobalPose();

        SR_MATH_NS::FVector3 physxPosition(globalPose.p.x, globalPose.p.y, globalPose.p.z);
        //SR_MATH_NS::Quaternion physxRotation(globalPose.q.x, globalPose.q.y, globalPose.q.z, globalPose.q.w);

        // --------------------------------------------------
        // Синхронизируем позицию напрямую
        pTransform->SetGlobalTranslation(physxPosition - m_controller->GetConfig().offset);

        // --------------------------------------------------
        // Визуальный поворот: добавляем фиксированный оффсет
        // PhysX капсула стоит по Y, модель смотрит вдоль Z
        //static const SR_MATH_NS::Quaternion modelOffset = SR_MATH_NS::Quaternion::FromAxisAngle(
        //    SR_MATH_NS::FVector3(0, 0, 1), SR_DEG(-SR_PI / 2.0)
        //);

        // Итоговая ориентация для визуала
        //pTransform->SetRotation(modelOffset * physxRotation);

        // --------------------------------------------------
        // Обновляем внутренние матрицы трансформа
        m_controller->UpdateMatrix(true);

        // Сохраняем текущие трансформации для внутреннего состояния
        m_translation = m_controller->GetTranslation();
        m_rotation = m_controller->GetRotation();

        Super::Synchronize();
    }
}
