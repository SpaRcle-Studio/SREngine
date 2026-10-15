//
// Created by Monika on 15.10.2026.
//

#ifndef SR_ENGINE_PHYSICS_XPBD_SOLVER_H
#define SR_ENGINE_PHYSICS_XPBD_SOLVER_H

#include <Physics/stdInclude.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_PHYSICS_NS {
    struct XPBDParticle {
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector3 prevPosition;
        SR_MATH_NS::FVector3 velocity;
        /// Позиция, в которую частицу ставит анимация в текущем кадре
        SR_MATH_NS::FVector3 animPosition;
        /// Анимированная позиция в прошлом кадре. Цель подшагов интерполируется от неё к animPosition
        SR_MATH_NS::FVector3 prevAnimPosition;
        /// Анимированная позиция на текущем подшаге
        SR_MATH_NS::FVector3 stepAnimPosition;
        /// 0 - частица закреплена и всегда стоит в animPosition
        float_t invMass = 1.f;
        float_t radius = 0.f;
        int32_t parent = SR_ID_INVALID;
        /// Скорость коллайдера в точке контакта на текущем подшаге
        SR_MATH_NS::FVector3 contactVelocity;
        bool inContact = false;
    };

    /// Ограничение расстояния, используется для костей, изгиба и связей между цепочками
    struct XPBDDistanceConstraint {
        uint32_t a = 0;
        uint32_t b = 0;
        float_t restLength = 0.f;
        float_t compliance = 0.f;
        float_t lambda = 0.f;
    };

    /// Притяжение частицы к анимированной позиции
    struct XPBDAttachConstraint {
        uint32_t particle = 0;
        /// Отрицательное значение отключает ограничение
        float_t compliance = -1.f;
        float_t lambda = 0.f;
    };

    enum class XPBDCollisionShapeType : uint8_t {
        Sphere, Capsule, Plane
    };

    struct XPBDCollisionShape {
        XPBDCollisionShapeType type = XPBDCollisionShapeType::Sphere;
        /// Sphere - центр, Capsule - начало отрезка, Plane - точка на плоскости
        SR_MATH_NS::FVector3 a;
        /// Capsule - конец отрезка, Plane - нормаль
        SR_MATH_NS::FVector3 b;
        /// Положение в прошлом кадре, коллайдер интерполируется от него к текущему по подшагам
        SR_MATH_NS::FVector3 prevA;
        SR_MATH_NS::FVector3 prevB;
        float_t radius = 0.f;

        /// Положение на текущем и предыдущем подшаге, считается солвером
        SR_MATH_NS::FVector3 stepA;
        SR_MATH_NS::FVector3 stepB;
        SR_MATH_NS::FVector3 stepPrevA;
        SR_MATH_NS::FVector3 stepPrevB;
    };

    struct XPBDSolverParams {
        SR_MATH_NS::FVector3 gravity = SR_MATH_NS::FVector3(0.f, -9.81f, 0.f);
        SR_MATH_NS::FVector3 force;
        /// Доля скорости, теряемая за 1/60 секунды, не зависит от частоты и подшагов
        float_t damping = 0.f;
        /// Гашение скорости относительно коллайдера у частиц в контакте, 1 - частица движется вместе с коллайдером
        float_t contactDamping = 0.f;
        /// Максимальный угол отклонения от анимированного направления в градусах, 0 - без ограничения
        float_t maxAngle = 0.f;
        /// Максимальное расстояние частицы от анимированной позиции, 0 - без ограничения
        float_t maxDistance = 0.f;
        /// Максимальная длина подшага в секундах. Кадр делится на столько подшагов, чтобы не превысить её
        float_t maxSubStepTime = 1.f / 240.f;
        /// Ограничение числа подшагов за кадр, на случай очень длинного кадра
        uint32_t maxSubSteps = 32;
        /// Сталкивать с коллайдерами не только частицы, но и отрезки костей и связей между цепочками
        bool collideEdges = false;
    };

    class XPBDSolver : public SR_UTILS_NS::NonCopyable {
    public:
        void Clear();

        uint32_t AddParticle(const XPBDParticle& particle);
        void AddDistanceConstraint(uint32_t a, uint32_t b);
        void AddBendConstraint(uint32_t a, uint32_t b);
        void AddLateralConstraint(uint32_t a, uint32_t b);
        void AddAttachConstraint(uint32_t particle);

        /// Пересчитывает длины ограничений по анимированной позе
        void UpdateRestLengths();
        /// Ставит частицы в анимированную позу и обнуляет скорости
        void Reset();
        /// Считает цель текущего кадра (анимированную позу и коллайдеры) целью прошлого кадра, чтобы не интерполировать
        void SyncTargetToFrame();

        /// Симулирует ровно время кадра dt, разбитое на подшаги. После шага частицы находятся в момент кадра,
        /// цель подшагов (анимированная поза и коллайдеры) интерполируется от прошлого кадра к текущему.
        /// follow - сдвиг, который свободные частицы повторяют за кадр (часть движения персонажа), без изменения скорости
        void Step(float_t dt, const SR_MATH_NS::FVector3& follow);

        void SetParams(const XPBDSolverParams& params) noexcept { m_params = params; }

        SR_NODISCARD SR_UTILS_NS::Vector<XPBDParticle>& GetParticles() noexcept { return m_particles; }
        SR_NODISCARD const SR_UTILS_NS::Vector<XPBDParticle>& GetParticles() const noexcept { return m_particles; }
        SR_NODISCARD SR_UTILS_NS::Vector<XPBDDistanceConstraint>& GetBendConstraints() noexcept { return m_bendConstraints; }
        SR_NODISCARD SR_UTILS_NS::Vector<XPBDDistanceConstraint>& GetLateralConstraints() noexcept { return m_lateralConstraints; }
        SR_NODISCARD SR_UTILS_NS::Vector<XPBDAttachConstraint>& GetAttachConstraints() noexcept { return m_attachConstraints; }
        SR_NODISCARD SR_UTILS_NS::Vector<XPBDCollisionShape>& GetCollisionShapes() noexcept { return m_collisionShapes; }

    private:
        void SubStep(float_t h);
        void UpdateStepTarget(float_t from, float_t to);
        void SolveDistanceConstraints(SR_UTILS_NS::Vector<XPBDDistanceConstraint>& constraints, float_t h);
        void SolveAttachConstraints(float_t h);
        void SolveAngleLimits();
        void SolveMaxDistance();
        void SolveCollisions(float_t h);
        void SolveEdgeCollisions(const SR_UTILS_NS::Vector<XPBDDistanceConstraint>& edges, float_t h);

    private:
        XPBDSolverParams m_params;

        SR_UTILS_NS::Vector<XPBDParticle> m_particles;
        SR_UTILS_NS::Vector<XPBDDistanceConstraint> m_distanceConstraints;
        SR_UTILS_NS::Vector<XPBDDistanceConstraint> m_bendConstraints;
        SR_UTILS_NS::Vector<XPBDDistanceConstraint> m_lateralConstraints;
        SR_UTILS_NS::Vector<XPBDAttachConstraint> m_attachConstraints;
        SR_UTILS_NS::Vector<XPBDCollisionShape> m_collisionShapes;

    };
}

#endif //SR_ENGINE_PHYSICS_XPBD_SOLVER_H
