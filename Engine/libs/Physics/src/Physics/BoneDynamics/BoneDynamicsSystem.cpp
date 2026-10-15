//
// Created by Monika on 15.10.2026.
//

#include <Physics/BoneDynamics/BoneDynamicsSystem.h>
#include <Physics/CollisionShape.h>

#include <Utils/ECS/Transform.h>
#include <Utils/DebugDraw.h>

#include <Codegen/BoneDynamicsSystem.generated.hpp>

namespace SR_PHYSICS_NS {
    void BoneDynamicsSystem::OnEnable() {
        m_needReset = true;
        Super::OnEnable();
    }

    void BoneDynamicsSystem::OnDisable() {
        ClearDebug();
        Super::OnDisable();
    }

    void BoneDynamicsSystem::OnDestroy() {
        ClearDebug();
        Super::OnDestroy();
    }

    void BoneDynamicsSystem::Rebuild() {
        m_isBuilt = false;
        m_needReset = true;
    }

    void BoneDynamicsSystem::ResetPose() {
        m_needReset = true;
    }

    void BoneDynamicsSystem::SwitchDebug() {
        m_debug = !m_debug;
        if (!m_debug) {
            ClearDebug();
        }
    }

    SR_UTILS_NS::GameObject::Ptr BoneDynamicsSystem::GetRootObject() const {
        if (auto&& pRoot = m_rootObject.Get()) {
            return pRoot;
        }
        return GetGameObject();
    }

    float_t BoneDynamicsSystem::GetChainFactor(const uint32_t index, const uint32_t count) const {
        if (count <= 1) {
            return 0.f;
        }
        return static_cast<float_t>(index) / static_cast<float_t>(count - 1);
    }

    void BoneDynamicsSystem::BuildJiggle() {
        /// Каждая кость - одна свободная частица, привязанная пружиной к анимированной позиции.
        /// Виртуального кончика нет, поэтому ориентация осей кости в риге не важна
        for (auto&& rootRef : m_roots) {
            auto&& pRoot = rootRef.Get();
            if (!pRoot) {
                continue;
            }

            Chain chain;

            Bone bone;
            bone.pGameObject = pRoot;
            bone.restRotation = pRoot->GetTransform()->GetQuaternion();
            bone.restTranslation = pRoot->GetTransform()->GetTranslation();

            XPBDParticle particle;
            particle.invMass = 1.f;

            bone.particle = m_solver.AddParticle(particle);
            chain.endParticle = bone.particle;
            m_solver.AddAttachConstraint(bone.particle);

            chain.bones.push_back(bone);
            m_chains.push_back(chain);
        }
    }

    void BoneDynamicsSystem::BuildChains() {
        SR_TRACY_ZONE;

        m_solver.Clear();
        m_chains.clear();
        m_isBuilt = true;

        if (m_mode == BoneDynamicsMode::Jiggle) {
            BuildJiggle();
            UpdateConstraintParams();
            ReadAnimatedPose();
            m_needReset = true;
            return;
        }

        for (auto&& rootRef : m_roots) {
            auto&& pRoot = rootRef.Get();
            if (!pRoot) {
                continue;
            }

            Chain chain;

            SR_UTILS_NS::GameObject::Ptr pCurrent = pRoot;
            while (pCurrent) {
                Bone bone;
                bone.pGameObject = pCurrent;
                bone.restRotation = pCurrent->GetTransform()->GetQuaternion();
                chain.bones.push_back(bone);

                SR_UTILS_NS::GameObject::Ptr pNext;
                for (auto&& pChild : pCurrent->GetChildrenRef()) {
                    if (auto&& pChildGameObject = SR_UTILS_NS::DynamicPointerCast<SR_UTILS_NS::GameObject>(pChild)) {
                        pNext = pChildGameObject;
                        break;
                    }
                }
                pCurrent = pNext;
            }

            /// Частицы стоят на началах костей, плюс одна виртуальная на кончике последней кости
            const uint32_t particlesCount = static_cast<uint32_t>(chain.bones.size()) + 1;
            int32_t parent = SR_ID_INVALID;

            for (uint32_t i = 0; i < particlesCount; ++i) {
                XPBDParticle particle;
                particle.invMass = i == 0 ? 0.f : 1.f;
                particle.parent = parent;

                const uint32_t index = m_solver.AddParticle(particle);
                if (i < chain.bones.size()) {
                    chain.bones[i].particle = index;
                }
                else {
                    chain.endParticle = index;
                }

                if (parent != SR_ID_INVALID) {
                    m_solver.AddDistanceConstraint(static_cast<uint32_t>(parent), index);
                    m_solver.AddAttachConstraint(index);
                }

                if (i >= 2) {
                    m_solver.AddBendConstraint(index - 2, index);
                }

                parent = static_cast<int32_t>(index);
            }

            m_chains.push_back(chain);
        }

        if (m_lateralMode != BoneDynamicsLateralMode::None && m_chains.size() > 1) {
            const uint32_t chainsCount = static_cast<uint32_t>(m_chains.size());
            const uint32_t pairsCount = m_lateralMode == BoneDynamicsLateralMode::Closed ? chainsCount : chainsCount - 1;

            for (uint32_t i = 0; i < pairsCount; ++i) {
                auto&& chainA = m_chains[i];
                auto&& chainB = m_chains[(i + 1) % chainsCount];

                const uint32_t depth = static_cast<uint32_t>(SR_MIN(chainA.bones.size(), chainB.bones.size()));

                /// Корни закреплены, поэтому связи начинаются со второй частицы
                for (uint32_t j = 1; j < depth; ++j) {
                    m_solver.AddLateralConstraint(chainA.bones[j].particle, chainB.bones[j].particle);
                }

                if (chainA.bones.size() == chainB.bones.size()) {
                    m_solver.AddLateralConstraint(chainA.endParticle, chainB.endParticle);
                }
            }
        }

        UpdateConstraintParams();
        ReadAnimatedPose();
        m_solver.UpdateRestLengths();
        m_needReset = true;
    }

    void BoneDynamicsSystem::RestoreUnanimatedBones() {
        /// Если аниматор не писал в кость, в ней осталось наше значение с прошлого кадра.
        /// Тогда возвращаем позу покоя, иначе симуляция будет накапливаться сама на себя.
        for (auto&& chain : m_chains) {
            for (auto&& bone : chain.bones) {
                if (!bone.pGameObject || !bone.hasWritten) {
                    continue;
                }

                auto&& pTransform = bone.pGameObject->GetTransform();

                if (m_mode == BoneDynamicsMode::Jiggle) {
                    if (pTransform->GetTranslation() == bone.writtenTranslation) {
                        pTransform->SetTranslation(bone.restTranslation);
                    }
                    continue;
                }

                if (pTransform->GetQuaternion() == bone.writtenRotation) {
                    pTransform->SetRotation(bone.restRotation);
                }
            }
        }
    }

    void BoneDynamicsSystem::ReadAnimatedPose() {
        auto&& particles = m_solver.GetParticles();

        for (auto&& chain : m_chains) {
            if (chain.bones.empty()) {
                continue;
            }

            for (auto&& bone : chain.bones) {
                if (bone.pGameObject) {
                    particles[bone.particle].animPosition = bone.pGameObject->GetTransform()->GetGlobalTranslation();
                }
            }

            if (m_mode == BoneDynamicsMode::Jiggle) {
                continue;
            }

            /// Направление виртуальной частицы берётся из последней кости
            auto&& lastBone = chain.bones[chain.bones.size() - 1];
            auto&& lastPos = particles[lastBone.particle].animPosition;

            SR_MATH_NS::FVector3 dir;
            if (chain.bones.size() > 1) {
                dir = (lastPos - particles[chain.bones[chain.bones.size() - 2].particle].animPosition).NormalizeSafe();
            }
            if (dir.IsZero() && lastBone.pGameObject) {
                dir = lastBone.pGameObject->GetTransform()->GetGlobalRotation() * SR_MATH_NS::FVector3::Up();
            }

            particles[chain.endParticle].animPosition = lastPos + dir * m_endLength;

            for (uint32_t i = 0; i < chain.bones.size(); ++i) {
                auto&& bone = chain.bones[i];
                if (!bone.pGameObject) {
                    continue;
                }

                const uint32_t childParticle = i + 1 < chain.bones.size() ? chain.bones[i + 1].particle : chain.endParticle;
                const SR_MATH_NS::FVector3 animDir = particles[childParticle].animPosition - particles[bone.particle].animPosition;
                bone.localDirection = bone.pGameObject->GetTransform()->GetGlobalRotation().Inverse() * animDir;
            }
        }
    }

    void BoneDynamicsSystem::UpdateConstraintParams() {
        auto&& particles = m_solver.GetParticles();
        auto&& attachConstraints = m_solver.GetAttachConstraints();
        auto&& bendConstraints = m_solver.GetBendConstraints();
        auto&& lateralConstraints = m_solver.GetLateralConstraints();

        if (m_mode == BoneDynamicsMode::Jiggle) {
            for (auto&& particle : particles) {
                particle.radius = m_radiusRoot;
            }
            for (auto&& constraint : attachConstraints) {
                constraint.compliance = m_stiffnessComplianceRoot / STIFFNESS_EDITOR_SCALE;
            }
        }
        else {
            for (auto&& chain : m_chains) {
                const uint32_t count = static_cast<uint32_t>(chain.bones.size()) + 1;
                const uint32_t first = chain.bones.empty() ? chain.endParticle : chain.bones[0].particle;

                for (uint32_t i = 0; i < count; ++i) {
                    const float_t t = GetChainFactor(i, count);
                    particles[first + i].radius = SR_MATH_NS::Mix(m_radiusRoot, m_radiusTip, t);
                }
            }
        }

        for (auto&& constraint : attachConstraints) {
            if (m_mode == BoneDynamicsMode::Jiggle) {
                break;
            }

            float_t t = 0.f;
            for (auto&& chain : m_chains) {
                const uint32_t first = chain.bones.empty() ? chain.endParticle : chain.bones[0].particle;
                if (constraint.particle >= first && constraint.particle <= chain.endParticle) {
                    t = GetChainFactor(constraint.particle - first, chain.endParticle - first + 1);
                    break;
                }
            }
            constraint.compliance = SR_MATH_NS::Mix(m_stiffnessComplianceRoot, m_stiffnessComplianceTip, t) / STIFFNESS_EDITOR_SCALE;
        }

        for (auto&& constraint : bendConstraints) {
            float_t t = 0.f;
            for (auto&& chain : m_chains) {
                const uint32_t first = chain.bones.empty() ? chain.endParticle : chain.bones[0].particle;
                if (constraint.b >= first && constraint.b <= chain.endParticle) {
                    t = GetChainFactor(constraint.b - first, chain.endParticle - first + 1);
                    break;
                }
            }
            constraint.compliance = SR_MATH_NS::Mix(m_bendComplianceRoot, m_bendComplianceTip, t);
        }

        for (auto&& constraint : lateralConstraints) {
            constraint.compliance = m_lateralCompliance;
        }

        XPBDSolverParams params;
        params.gravity = m_gravity;
        params.force = m_wind;
        params.damping = m_damping;
        params.contactDamping = m_contactDamping;
        params.maxAngle = m_mode == BoneDynamicsMode::Chain ? m_maxAngle : 0.f;
        params.maxDistance = m_maxDistance;
        params.subSteps = m_subSteps;
        params.collideEdges = m_mode == BoneDynamicsMode::Chain && m_collideEdges;
        m_solver.SetParams(params);
    }

    void BoneDynamicsSystem::UpdateCollisionShapes() {
        /// m_prevCollisionShapes - набор прошлого кадра, его prevA/prevB хранят положение на конце последнего шага
        auto&& shapes = m_solver.GetCollisionShapes();
        shapes.clear();

        for (auto&& colliderRef : m_colliders) {
            auto&& pCollider = colliderRef.Get();
            if (!pCollider || !pCollider->IsActive()) {
                continue;
            }
            shapes.push_back(pCollider->GetCollisionShape());
            if (m_debug) {
                pCollider->RequestDebug();
            }
        }

        for (auto&& shapeRef : m_physicsShapes) {
            auto&& pShape = shapeRef.Get();
            if (!pShape || !pShape->IsActive()) {
                continue;
            }

            const ShapeType type = pShape->GetType();
            const SR_MATH_NS::FVector3& scale = pShape->GetScale();
            const SR_MATH_NS::Quaternion& rotation = pShape->GetRotation();
            const SR_MATH_NS::FVector3 center = pShape->GetTranslation() + pShape->GetCenterDirection();
            const SR_MATH_NS::FVector3 up = rotation * SR_MATH_NS::FVector3::Up();

            XPBDCollisionShape shape;

            switch (type) {
                case ShapeType::Sphere3D:
                    shape.type = XPBDCollisionShapeType::Sphere;
                    shape.a = center;
                    shape.radius = pShape->GetRadius() * scale.Max();
                    break;
                case ShapeType::Capsule3D: {
                    const float_t halfHeight = pShape->GetHeight() * scale.y;
                    shape.type = XPBDCollisionShapeType::Capsule;
                    shape.a = center - up * halfHeight;
                    shape.b = center + up * halfHeight;
                    shape.radius = pShape->GetRadius() * SR_MAX(scale.x, scale.z);
                    break;
                }
                case ShapeType::Plane3D:
                    shape.type = XPBDCollisionShapeType::Plane;
                    shape.a = center;
                    shape.b = up;
                    break;
                default:
                    continue;
            }

            shapes.push_back(shape);
        }

        /// Коллайдер интерполируется по подшагам от положения на конце последнего шага, иначе быстрая нога
        /// за кадр перепрыгивает через ткань. Если набор коллайдеров поменялся, интерполяции нет
        const bool canInterpolate = !m_needReset && m_prevCollisionShapes.size() == shapes.size();

        for (uint32_t i = 0; i < shapes.size(); ++i) {
            auto&& shape = shapes[i];
            if (canInterpolate && m_prevCollisionShapes[i].type == shape.type) {
                shape.prevA = m_prevCollisionShapes[i].prevA;
                shape.prevB = m_prevCollisionShapes[i].prevB;
            }
            else {
                shape.prevA = shape.a;
                shape.prevB = shape.b;
            }
        }
    }

    void BoneDynamicsSystem::UpdatePose(const float_t dt) {
        SR_TRACY_ZONE;

        if (!m_isBuilt) {
            BuildChains();
        }

        if (m_chains.empty()) {
            return;
        }

        SR_MATH_NS::FVector3 rootPosition;
        if (auto&& pRootObject = GetRootObject()) {
            rootPosition = pRootObject->GetTransform()->GetGlobalTranslation();
        }

        const bool isTeleport = (rootPosition - m_frameRootPosition).Length() > m_teleportDistance;
        m_frameRootPosition = rootPosition;

        RestoreUnanimatedBones();
        ReadAnimatedPose();
        UpdateConstraintParams();
        UpdateCollisionShapes();

        if (IsScenePaused() && !m_simulateInEditor) {
            /// Только отладка: частицы стоят в анимированной позе, кости не трогаем
            m_solver.Reset();
            m_needReset = true;

            if (m_debug) {
                UpdateDebug();
            }
            else {
                ClearDebug();
            }
            return;
        }

        if (m_needReset || isTeleport) {
            m_solver.Reset();
            m_solver.SyncTargetToFrame();
            m_stepRootPosition = rootPosition;
            m_accumulator = 0.f;
            m_needReset = false;
        }

        const float_t fixedDt = 1.f / SR_MAX(1.f, m_fixedRate);
        const float_t follow = 1.f - SR_CLAMP01(m_inertia);

        /// m_accumulator - время от конца последнего шага до текущего кадра. Шаг заканчивается не в момент кадра,
        /// поэтому цель шага (анимированная поза, коллайдеры, корень) берётся интерполяцией на момент его конца:
        /// от состояния на конце прошлого шага к состоянию кадра. Иначе ошибка цели зависит от того,
        /// где кадр попал между шагами, и при частоте кадров выше частоты шагов частицы дребезжат
        m_accumulator += dt;

        uint32_t steps = 0;
        while (m_accumulator >= fixedDt && steps < m_maxStepsPerFrame) {
            const float_t t = fixedDt / m_accumulator;

            const SR_MATH_NS::FVector3 stepRoot = m_stepRootPosition + (rootPosition - m_stepRootPosition) * t;
            m_solver.Translate((stepRoot - m_stepRootPosition) * follow);
            m_stepRootPosition = stepRoot;

            m_solver.Step(fixedDt, t);
            m_accumulator -= fixedDt;
            ++steps;
        }

        /// Не даём копиться отставанию, если кадр был слишком долгим
        if (steps == m_maxStepsPerFrame && m_accumulator >= fixedDt) {
            m_accumulator = 0.f;
            m_stepRootPosition = rootPosition;
            m_solver.SyncTargetToFrame();
        }

        m_prevCollisionShapes = m_solver.GetCollisionShapes();

        /// Доля пути до следующего шага, вывод интерполируется между двумя последними шагами
        m_outputAlpha = m_accumulator / fixedDt;

        if (m_mode == BoneDynamicsMode::Jiggle) {
            ApplyJiggle();
        }
        else {
            ApplyToBones();
        }

        if (m_debug) {
            UpdateDebug();
        }
        else if (!m_debugIds.empty()) {
            ClearDebug();
        }
    }

    void BoneDynamicsSystem::ApplyJiggle() {
        auto&& particles = m_solver.GetParticles();
        const float_t weight = SR_CLAMP01(m_weight);

        for (auto&& chain : m_chains) {
            for (auto&& bone : chain.bones) {
                if (!bone.pGameObject) {
                    continue;
                }

                auto&& pTransform = bone.pGameObject->GetTransform();
                auto&& particle = particles[bone.particle];

                /// Здесь в кости либо свежая поза аниматора, либо восстановленная поза покоя
                bone.restTranslation = pTransform->GetTranslation();

                const SR_MATH_NS::FVector3 globalOffset = m_solver.GetInterpolatedOffset(bone.particle, m_outputAlpha) * weight;

                /// Смещение переводим в пространство родителя с учётом его масштаба
                SR_MATH_NS::FVector3 localOffset = globalOffset;
                if (auto&& pParent = pTransform->GetParentTransform()) {
                    SR_MATH_NS::FVector3 parentTranslation;
                    SR_MATH_NS::Quaternion parentRotation;
                    SR_MATH_NS::FVector3 parentScale;
                    pParent->GetMatrix().Decompose(parentTranslation, parentRotation, parentScale);

                    localOffset = parentRotation.Inverse() * globalOffset;
                    localOffset = SR_MATH_NS::FVector3(
                        parentScale.x != 0.f ? localOffset.x / parentScale.x : 0.f,
                        parentScale.y != 0.f ? localOffset.y / parentScale.y : 0.f,
                        parentScale.z != 0.f ? localOffset.z / parentScale.z : 0.f
                    );
                }

                pTransform->SetTranslation(bone.restTranslation + localOffset);

                bone.writtenTranslation = pTransform->GetTranslation();
                bone.hasWritten = true;
            }
        }
    }

    void BoneDynamicsSystem::ApplyToBones() {
        auto&& particles = m_solver.GetParticles();
        const float_t weight = SR_CLAMP01(m_weight);

        for (auto&& chain : m_chains) {
            for (uint32_t i = 0; i < chain.bones.size(); ++i) {
                auto&& bone = chain.bones[i];
                if (!bone.pGameObject) {
                    continue;
                }

                const uint32_t childParticle = i + 1 < chain.bones.size() ? chain.bones[i + 1].particle : chain.endParticle;

                /// Родитель уже повёрнут, поэтому позицию и направление кости берём текущие, а не анимированные
                auto&& pTransform = bone.pGameObject->GetTransform();
                const SR_MATH_NS::Quaternion globalRotation = pTransform->GetGlobalRotation();
                const SR_MATH_NS::FVector3 bonePosition = pTransform->GetGlobalTranslation();

                /// Частица шага привязана к позе, интерполированной от прошлого кадра, поэтому переносим её смещение
                /// на позу текущего кадра, иначе цепочка дёргается в кадрах с разным числом шагов
                const SR_MATH_NS::FVector3 childPosition = particles[childParticle].animPosition + m_solver.GetInterpolatedOffset(childParticle, m_outputAlpha);

                const SR_MATH_NS::FVector3 currentDir = globalRotation * bone.localDirection;
                const SR_MATH_NS::FVector3 simDir = childPosition - bonePosition;

                if (currentDir.LengthSq() < SR_EPSILON || simDir.LengthSq() < SR_EPSILON) {
                    continue;
                }

                SR_MATH_NS::Quaternion delta = SR_MATH_NS::Quaternion::FromToRotation(currentDir, simDir);
                if (weight < 1.f) {
                    delta = SR_MATH_NS::Quaternion::Slerp(SR_MATH_NS::Quaternion::Identity(), delta, weight);
                }

                /// Здесь в кости либо свежая поза аниматора, либо восстановленная поза покоя
                bone.restRotation = pTransform->GetQuaternion();

                pTransform->SetGlobalRotation(delta * globalRotation);

                bone.writtenRotation = pTransform->GetQuaternion();
                bone.hasWritten = true;
            }
        }
    }

    void BoneDynamicsSystem::UpdateDebug() {
        auto&& particles = m_solver.GetParticles();

        uint32_t debugIndex = 0;
        auto&& nextId = [this, &debugIndex]() -> uint64_t& {
            if (debugIndex >= m_debugIds.size()) {
                m_debugIds.push_back(SR_UINT64_MAX);
            }
            return m_debugIds[debugIndex++];
        };

        const SR_MATH_NS::FColor particleColor = SR_MATH_NS::FColor(0, 200, 255, 255) / 255.f;
        const SR_MATH_NS::FColor lineColor = SR_MATH_NS::FColor(255, 255, 255, 255) / 255.f;

        /// Позиция, которую получила кость: поза кадра плюс интерполированное смещение, в мировых координатах
        auto&& worldPosition = [this, &particles](uint32_t index) {
            return particles[index].animPosition + m_solver.GetInterpolatedOffset(index, m_outputAlpha);
        };

        for (uint32_t i = 0; i < particles.size(); ++i) {
            auto&& particle = particles[i];
            const SR_MATH_NS::FVector3 position = worldPosition(i);

            auto&& id = nextId();
            id = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawSphere(id, position, SR_MATH_NS::Quaternion(),
                SR_MATH_NS::FVector3(SR_MAX(particle.radius, 0.005f)), particleColor, SR_FLOAT_MAX
            );

            if (particle.parent != SR_ID_INVALID) {
                auto&& lineId = nextId();
                lineId = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawLine(lineId, worldPosition(static_cast<uint32_t>(particle.parent)),
                    position, lineColor, SR_FLOAT_MAX
                );
            }
            else if (m_mode == BoneDynamicsMode::Jiggle) {
                /// Отклонение от анимированной позиции
                auto&& lineId = nextId();
                lineId = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawLine(lineId, particle.animPosition,
                    position, lineColor, SR_FLOAT_MAX
                );
            }
        }

        const SR_MATH_NS::FColor lateralColor = SR_MATH_NS::FColor(255, 120, 0, 255) / 255.f;

        for (auto&& constraint : m_solver.GetLateralConstraints()) {
            auto&& lineId = nextId();
            lineId = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawLine(lineId, worldPosition(constraint.a),
                worldPosition(constraint.b), lateralColor, SR_FLOAT_MAX
            );
        }

        /// Если связей стало меньше, например после Rebuild, лишние линии нужно убрать
        for (uint32_t i = debugIndex; i < m_debugIds.size(); ++i) {
            SR_UTILS_NS::DebugOverlayDraw::Instance().TryRemove(&m_debugIds[i]);
        }
        m_debugIds.resize(debugIndex);
    }

    void BoneDynamicsSystem::ClearDebug() {
        for (auto&& id : m_debugIds) {
            SR_UTILS_NS::DebugOverlayDraw::Instance().TryRemove(&id);
        }
        m_debugIds.clear();
    }
}
