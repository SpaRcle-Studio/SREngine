//
// Created by Monika on 26.03.2026.
//

#include <Physics/PhysX/PhysXCharacterControllerImpl.h>

#include <Enum/CharacterControllerCollisionFlags.hpp>

namespace SR_PHYSICS_NS {
    class GroundQueryFilter final : public physx::PxQueryFilterCallback {
    public:
        explicit GroundQueryFilter(const physx::PxActor* ignoreActor)
            : m_ignoreActor(ignoreActor)
        {}

        physx::PxQueryHitType::Enum preFilter(
            const physx::PxFilterData& filterData,
            const physx::PxShape* shape,
            const physx::PxRigidActor* actor,
            physx::PxHitFlags& queryFlags
        ) override {
            if (actor == m_ignoreActor) {
                return physx::PxQueryHitType::eNONE;
            }
            return physx::PxQueryHitType::eBLOCK;
        }

        physx::PxQueryHitType::Enum postFilter(const physx::PxFilterData& filterData, const physx::PxQueryHit& hit) override {
            return physx::PxQueryHitType::eBLOCK;
        }

    private:
        const physx::PxActor* m_ignoreActor;
    };

    class GroundSweepCallback final : public physx::PxSweepCallback {
    public:
        GroundSweepCallback(physx::PxSweepHit* hits, physx::PxU32 maxHits)
            : physx::PxSweepCallback(hits, maxHits)
        {}

        bool processTouches(const physx::PxSweepHit* buffer, physx::PxU32 nbHits) override {
            for (physx::PxU32 i = 0; i < nbHits; ++i) {
                auto&& pActor = buffer[i].actor;
                auto&& pUserData = pActor ? static_cast<RigidActorUserData*>(pActor->userData) : nullptr;

                if (!hasHit || buffer[i].distance < hit.distance) {
                    hit = buffer[i];
                    hasHit = true;
                }
            }

            return true;
        }

        void finalizeQuery() override {
            if (hasBlock) {
                hit = block;
                hasHit = true;
            }
        }

        physx::PxSweepHit hit{};
        bool hasHit = false;
    };

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

    bool PhysXCharacterControllerImpl::IsGrounded() const {
        SR_TRACY_ZONE;

        if (!m_pxController) {
            return false;
        }

        auto&& position = SR_PHYSICS_UTILS_NS::PxExtendedV3ToPxV3(m_pxController->getFootPosition());
        auto&& pScene = m_pxController->getScene();
        auto&& config = m_controller->GetConfig();

        const float_t groundProbeRadius = config.radius * 1.0f;
        const float_t minGroundNormalY = cosf(SR_MATH_NS::ToRad(config.slopeLimit));

        physx::PxSphereGeometry geometry(groundProbeRadius);
        physx::PxTransform pose(position + physx::PxVec3(0.0f, -config.groundProbeOffset, 0.0f));

        physx::PxSweepHit hits[16];
        GroundSweepCallback callback(hits, 16);

        physx::PxQueryFilterData filterData;
        filterData.flags = physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC | physx::PxQueryFlag::ePREFILTER;

        GroundQueryFilter filter(m_pxController->getActor());

        const bool hasHit = pScene->sweep(
            geometry,
            pose,
            physx::PxVec3(0.0f, -1.0f, 0.0f),
            config.groundProbeDistance,
            callback,
            physx::PxHitFlag::eDEFAULT,
            filterData,
            &filter
        );

        if (!hasHit || !callback.hasHit) {
            return false;
        }

        return callback.hit.normal.y >= minGroundNormalY;
    }
}
