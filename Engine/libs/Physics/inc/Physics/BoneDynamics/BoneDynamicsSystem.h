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

    SR_ENUM_NS_CLASS_T(BoneDynamicsMode, uint8_t,
        Chain,
        Jiggle
    )

    /// Физика костей (юбки, волосы, хвосты, грудь) на XPBD.
    /// Chain - каждый элемент m_roots корень цепочки, цепочка идёт по первому ребёнку до конца иерархии, кости поворачиваются.
    /// Jiggle - каждый элемент m_roots отдельная кость на пружине, кость смещается, а не поворачивается.
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
            /// Jiggle: локальная позиция кости в позе покоя и записанная системой
            SR_MATH_NS::FVector3 restTranslation;
            SR_MATH_NS::FVector3 writtenTranslation;
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
        SR_NODISCARD BoneDynamicsMode GetMode() const noexcept { return m_mode; }
        SR_NODISCARD bool IsChainMode() const noexcept { return m_mode == BoneDynamicsMode::Chain; }

    private:
        /// @method @editorButton
        void Rebuild();
        /// @method @editorButton
        void ResetPose();
        /// @method @editorButton
        void SwitchDebug();

        void BuildChains();
        void BuildJiggle();
        void RestoreUnanimatedBones();
        void ReadAnimatedPose();
        void UpdateConstraintParams();
        void UpdateCollisionShapes();
        void ApplyToBones();
        void ApplyJiggle();
        void UpdateDebug();
        void ClearDebug();

        SR_NODISCARD SR_UTILS_NS::GameObject::Ptr GetRootObject() const;
        SR_NODISCARD float_t GetChainFactor(uint32_t index, uint32_t count) const;

        /// Stiffness в редакторе задаётся в тысячных долях, иначе нужные значения не видны в инспекторе
        static constexpr float_t STIFFNESS_EDITOR_SCALE = 1000.f;

    private:
        XPBDSolver m_solver;
        SR_UTILS_NS::Vector<Chain> m_chains;
        SR_UTILS_NS::Vector<uint64_t> m_debugIds;
        SR_UTILS_NS::Vector<XPBDCollisionShape> m_prevCollisionShapes;

        float_t m_accumulator = 0.f;
        float_t m_outputAlpha = 1.f;

        /// Позиция корня персонажа в текущем кадре и на конце последнего шага симуляции
        SR_MATH_NS::FVector3 m_frameRootPosition;
        SR_MATH_NS::FVector3 m_stepRootPosition;
        bool m_isBuilt = false;
        bool m_needReset = true;

        /// @property @tooltip(Chain - кости поворачиваются по цепочке: юбки и волосы. Jiggle - каждая кость в Roots смещается на пружине: грудь и живот. После смены нажать Rebuild)
        BoneDynamicsMode m_mode = BoneDynamicsMode::Chain;
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
        /// @property @range(0.f, 1.f) @drag(0.001f) @tooltip(Доля скорости которая теряется за 1/60 секунды. Не зависит от Fixed Rate и Sub Steps)
        float_t m_damping = 0.02f;
        /// @property @range(0.f, 1.f) @drag(0.01f) @tooltip(Гашение скорости ткани относительно коллайдера в момент касания. Убирает рывки от ног не делая всю симуляцию вязкой)
        float_t m_contactDamping = 0.f;
        /// @property @range(0.f, 1.f) @drag(0.01f) @tooltip(Насколько частицы отстают от движения персонажа. 0 - едут вместе с ним. 1 - остаются на месте в мире)
        float_t m_inertia = 0.5f;

        /// @property @drag(0.01f) @range(0.f, 1000.f) @tooltip(Податливость притяжения к анимации в тысячных долях. Меньше - жёстче)
        float_t m_stiffnessComplianceRoot = 0.1f;
        /// @property @drag(0.01f) @range(0.f, 1000.f) @tooltip(Податливость притяжения к анимации в тысячных долях. Меньше - жёстче)
        float_t m_stiffnessComplianceTip = 10.f;
        /// @property @drag(0.0001f) @range(0.f, 1.f) @condition(This.IsChainMode())
        float_t m_bendComplianceRoot = 0.f;
        /// @property @drag(0.0001f) @range(0.f, 1.f) @condition(This.IsChainMode())
        float_t m_bendComplianceTip = 0.001f;
        /// @property @drag(0.001f) @range(0.f, 10.f)
        float_t m_radiusRoot = 0.02f;
        /// @property @drag(0.001f) @range(0.f, 10.f) @condition(This.IsChainMode())
        float_t m_radiusTip = 0.02f;
        /// @property @range(0.f, 180.f) @condition(This.IsChainMode())
        float_t m_maxAngle = 0.f;
        /// @property @drag(0.001f) @range(0.f, 10.f) @tooltip(Насколько далеко частица может уйти от анимированной позиции. 0 - без ограничения. Для Jiggle задаёт амплитуду)
        float_t m_maxDistance = 0.f;

        /// @property @condition(This.IsChainMode())
        BoneDynamicsLateralMode m_lateralMode = BoneDynamicsLateralMode::None;
        /// @property @drag(0.0001f) @range(0.f, 1.f) @condition(This.IsChainMode() && This.GetLateralMode() != SR_PHYSICS_NS::BoneDynamicsLateralMode::None)
        float_t m_lateralCompliance = 0.0001f;

        /// @property @condition(This.IsChainMode()) @tooltip(Сталкивать с коллайдерами отрезки костей и связей между цепочками. Для юбок и плащей. Горизонтальные отрезки есть только при Lateral Mode Open или Closed)
        bool m_collideEdges = false;

        /// @property @drag(0.01f) @condition(This.IsChainMode())
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
