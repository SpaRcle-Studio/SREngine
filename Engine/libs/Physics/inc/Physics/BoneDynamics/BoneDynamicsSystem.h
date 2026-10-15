//
// Created by Monika on 15.10.2026.
//

#ifndef SR_ENGINE_PHYSICS_BONE_DYNAMICS_SYSTEM_H
#define SR_ENGINE_PHYSICS_BONE_DYNAMICS_SYSTEM_H

#include <Physics/BoneDynamics/XPBDSolver.h>
#include <Physics/BoneDynamics/BoneDynamicsCollider.h>

#include <Utils/Animations/PosePostProcessor.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/GameObject.h>

namespace SR_PTYPES_NS {
    class CollisionShape;
}

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS_T(BoneDynamicsLateralMode, uint8_t,
        None,
        Open,
        Closed
    )

    /// Физика костей (юбки, волосы, хвосты) на XPBD.
    /// Каждый элемент m_roots - корень цепочки, цепочка идёт по первому ребёнку до конца иерархии.
    /// @displayName(Bone Dynamics) @category(Physics)
    class BoneDynamicsSystem : public SR_ANIMATIONS_NS::PosePostProcessor {
        SR_CLASS()
        using Super = SR_ANIMATIONS_NS::PosePostProcessor;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<BoneDynamicsSystem>;

        struct Bone {
            SR_UTILS_NS::GameObject::Ptr pGameObject;
            uint32_t particle = 0;
            /// Локальный поворот кости в позе покоя
            SR_MATH_NS::Quaternion restRotation;
            /// Локальный поворот, который система записала в прошлый раз
            SR_MATH_NS::Quaternion writtenRotation;
            /// Направление кости в её локальном пространстве по анимированной позе
            SR_MATH_NS::FVector3 localDirection;
            bool hasWritten = false;
        };

        struct Chain {
            SR_UTILS_NS::Vector<Bone> bones;
            /// Индекс последней виртуальной частицы на кончике
            uint32_t endParticle = 0;
        };

    public:
        void OnEnable() override;
        void OnDisable() override;
        void OnDestroy() override;

        void UpdatePose(float_t dt) override;

        /// В редакторе без симуляции только рисуется отладка, кости не трогаются
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD BoneDynamicsLateralMode GetLateralMode() const noexcept { return m_lateralMode; }

    private:
        /// @method @editorButton
        void Rebuild();
        /// @method @editorButton
        void ResetPose();
        /// @method @editorButton
        void SwitchDebug();

        void BuildChains();
        void RestoreUnanimatedBones();
        void ReadAnimatedPose();
        void UpdateConstraintParams();
        void UpdateCollisionShapes();
        void ApplyToBones();
        void UpdateDebug();
        void ClearDebug();

        SR_NODISCARD SR_UTILS_NS::GameObject::Ptr GetRootObject() const;
        SR_NODISCARD float_t GetChainFactor(uint32_t index, uint32_t count) const;

    private:
        XPBDSolver m_solver;
        SR_UTILS_NS::Vector<Chain> m_chains;
        SR_UTILS_NS::Vector<uint64_t> m_debugIds;
        SR_UTILS_NS::Vector<XPBDCollisionShape> m_prevCollisionShapes;

        float_t m_accumulator = 0.f;
        SR_MATH_NS::FVector3 m_lastRootPosition;
        bool m_isBuilt = false;
        bool m_needReset = true;

        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject>> m_roots;
        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<BoneDynamicsCollider>> m_colliders;
        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<SR_PTYPES_NS::CollisionShape>> m_physicsShapes;

        /// @property @tooltip(Объект движение которого считается движением персонажа. Если не задан - объект с компонентом)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> m_rootObject;

        /// @property @range(0.f, 1.f) @drag(0.01f)
        float_t m_weight = 1.f;
        /// @property @range(10.f, 240.f)
        float_t m_fixedRate = 60.f;
        /// @property @range(1, 32)
        uint32_t m_subSteps = 4;
        /// @property @range(1, 8)
        uint32_t m_maxStepsPerFrame = 4;

        /// @property @drag(0.01f)
        SR_MATH_NS::FVector3 m_gravity = SR_MATH_NS::FVector3(0.f, -9.81f, 0.f);
        /// @property @drag(0.01f)
        SR_MATH_NS::FVector3 m_wind;
        /// @property @range(0.f, 1.f) @drag(0.001f)
        float_t m_damping = 0.02f;
        /// @property @range(0.f, 1.f) @drag(0.01f)
        float_t m_inertia = 0.5f;

        /// @property @drag(0.0001f) @range(0.f, 1.f)
        float_t m_stiffnessComplianceRoot = 0.0001f;
        /// @property @drag(0.0001f) @range(0.f, 1.f)
        float_t m_stiffnessComplianceTip = 0.01f;
        /// @property @drag(0.0001f) @range(0.f, 1.f)
        float_t m_bendComplianceRoot = 0.f;
        /// @property @drag(0.0001f) @range(0.f, 1.f)
        float_t m_bendComplianceTip = 0.001f;
        /// @property @drag(0.001f) @range(0.f, 10.f)
        float_t m_radiusRoot = 0.02f;
        /// @property @drag(0.001f) @range(0.f, 10.f)
        float_t m_radiusTip = 0.02f;
        /// @property @range(0.f, 180.f)
        float_t m_maxAngle = 0.f;

        /// @property
        BoneDynamicsLateralMode m_lateralMode = BoneDynamicsLateralMode::None;
        /// @property @drag(0.0001f) @range(0.f, 1.f) @condition(This.GetLateralMode() != SR_PHYSICS_NS::BoneDynamicsLateralMode::None)
        float_t m_lateralCompliance = 0.0001f;

        /// @property @tooltip(Сталкивать с коллайдерами отрезки костей и связей между цепочками. Для юбок и плащей. Горизонтальные отрезки есть только при Lateral Mode Open или Closed)
        bool m_collideEdges = false;

        /// @property @drag(0.01f)
        float_t m_endLength = 0.1f;
        /// @property @drag(0.1f)
        float_t m_teleportDistance = 1.f;

        /// @property
        bool m_simulateInEditor = false;
        /// @property
        bool m_debug = false;

    };
}

#endif //SR_ENGINE_PHYSICS_BONE_DYNAMICS_SYSTEM_H
