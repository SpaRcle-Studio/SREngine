//
// Created by Monika on 15.10.2026.
//

#include <Physics/BoneDynamics/XPBDSolver.h>

#include <Utils/Profile/TracyContext.h>

namespace SR_PHYSICS_NS {
    void XPBDSolver::Clear() {
        m_particles.clear();
        m_distanceConstraints.clear();
        m_bendConstraints.clear();
        m_lateralConstraints.clear();
        m_attachConstraints.clear();
        m_collisionShapes.clear();
    }

    uint32_t XPBDSolver::AddParticle(const XPBDParticle& particle) {
        m_particles.push_back(particle);
        return static_cast<uint32_t>(m_particles.size() - 1);
    }

    void XPBDSolver::AddDistanceConstraint(const uint32_t a, const uint32_t b) {
        XPBDDistanceConstraint constraint;
        constraint.a = a;
        constraint.b = b;
        m_distanceConstraints.push_back(constraint);
    }

    void XPBDSolver::AddBendConstraint(const uint32_t a, const uint32_t b) {
        XPBDDistanceConstraint constraint;
        constraint.a = a;
        constraint.b = b;
        m_bendConstraints.push_back(constraint);
    }

    void XPBDSolver::AddLateralConstraint(const uint32_t a, const uint32_t b) {
        XPBDDistanceConstraint constraint;
        constraint.a = a;
        constraint.b = b;
        m_lateralConstraints.push_back(constraint);
    }

    void XPBDSolver::AddAttachConstraint(const uint32_t particle) {
        XPBDAttachConstraint constraint;
        constraint.particle = particle;
        m_attachConstraints.push_back(constraint);
    }

    void XPBDSolver::UpdateRestLengths() {
        auto&& update = [this](SR_UTILS_NS::Vector<XPBDDistanceConstraint>& constraints) {
            for (auto&& constraint : constraints) {
                constraint.restLength = SR_MATH_NS::FVector3::Distance(m_particles[constraint.a].animPosition, m_particles[constraint.b].animPosition);
            }
        };

        update(m_distanceConstraints);
        update(m_bendConstraints);
        update(m_lateralConstraints);
    }

    void XPBDSolver::Reset() {
        for (auto&& particle : m_particles) {
            particle.position = particle.animPosition;
            particle.prevPosition = particle.animPosition;
            particle.prevAnimPosition = particle.animPosition;
            particle.stepAnimPosition = particle.animPosition;
            particle.lastStepPosition = particle.animPosition;
            particle.lastStepAnimPosition = particle.animPosition;
            particle.velocity = SR_MATH_NS::FVector3::Zero();
        }
    }

    SR_MATH_NS::FVector3 XPBDSolver::GetInterpolatedOffset(const uint32_t index, const float_t alpha) const {
        auto&& particle = m_particles[index];
        const SR_MATH_NS::FVector3 lastOffset = particle.lastStepPosition - particle.lastStepAnimPosition;
        const SR_MATH_NS::FVector3 offset = particle.position - particle.stepAnimPosition;
        return lastOffset + (offset - lastOffset) * SR_CLAMP01(alpha);
    }

    void XPBDSolver::SyncTargetToFrame() {
        for (auto&& particle : m_particles) {
            particle.prevAnimPosition = particle.animPosition;
        }
        for (auto&& shape : m_collisionShapes) {
            shape.prevA = shape.a;
            shape.prevB = shape.b;
        }
    }

    void XPBDSolver::Translate(const SR_MATH_NS::FVector3& delta) {
        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f) {
                continue;
            }
            particle.position += delta;
            particle.prevPosition += delta;
        }
    }

    void XPBDSolver::Step(const float_t dt, const float_t t) {
        SR_TRACY_ZONE;

        if (dt <= 0.f || m_particles.empty()) {
            return;
        }

        const uint32_t subSteps = SR_MAX(1u, m_params.subSteps);
        const float_t h = dt / static_cast<float_t>(subSteps);
        const float_t stepT = SR_CLAMP01(t);

        for (auto&& particle : m_particles) {
            particle.lastStepPosition = particle.position;
            particle.lastStepAnimPosition = particle.stepAnimPosition;
        }

        for (uint32_t i = 0; i < subSteps; ++i) {
            const float_t subFrom = stepT * static_cast<float_t>(i) / static_cast<float_t>(subSteps);
            const float_t subTo = stepT * static_cast<float_t>(i + 1) / static_cast<float_t>(subSteps);
            UpdateStepTarget(subFrom, subTo);
            SubStep(h);
        }

        /// Цель на конце этого шага - начало интерполяции следующего, так цель непрерывна во времени
        for (auto&& particle : m_particles) {
            particle.prevAnimPosition = particle.stepAnimPosition;
        }
        for (auto&& shape : m_collisionShapes) {
            shape.prevA = shape.stepA;
            shape.prevB = shape.stepB;
        }
    }

    void XPBDSolver::UpdateStepTarget(const float_t from, const float_t to) {
        for (auto&& particle : m_particles) {
            particle.stepAnimPosition = particle.prevAnimPosition + (particle.animPosition - particle.prevAnimPosition) * to;
        }

        for (auto&& shape : m_collisionShapes) {
            shape.stepPrevA = shape.prevA + (shape.a - shape.prevA) * from;
            shape.stepPrevB = shape.prevB + (shape.b - shape.prevB) * from;
            shape.stepA = shape.prevA + (shape.a - shape.prevA) * to;
            shape.stepB = shape.prevB + (shape.b - shape.prevB) * to;

            if (shape.type == XPBDCollisionShapeType::Plane) {
                shape.stepB = shape.stepB.NormalizeSafe();
            }
        }
    }

    void XPBDSolver::SubStep(const float_t h) {
        const SR_MATH_NS::FVector3 acceleration = m_params.gravity + m_params.force;

        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f) {
                particle.prevPosition = particle.position;
                particle.position = particle.stepAnimPosition;
                continue;
            }

            particle.velocity += acceleration * h;
            particle.prevPosition = particle.position;
            particle.position += particle.velocity * h;
            particle.inContact = false;
        }

        for (auto&& constraint : m_distanceConstraints) { constraint.lambda = 0.f; }
        for (auto&& constraint : m_bendConstraints) { constraint.lambda = 0.f; }
        for (auto&& constraint : m_lateralConstraints) { constraint.lambda = 0.f; }
        for (auto&& constraint : m_attachConstraints) { constraint.lambda = 0.f; }

        SolveAttachConstraints(h);
        SolveDistanceConstraints(m_bendConstraints, h);
        SolveDistanceConstraints(m_lateralConstraints, h);
        SolveAngleLimits();
        SolveDistanceConstraints(m_distanceConstraints, h);
        SolveMaxDistance();
        /// Коллизии решаются последними, иначе остальные ограничения возвращают частицы обратно в коллайдер
        if (m_params.collideEdges) {
            SolveEdgeCollisions(m_lateralConstraints, h);
            SolveEdgeCollisions(m_distanceConstraints, h);
        }
        SolveCollisions(h);

        /// damping задан как потеря скорости за 1/60 секунды, пересчитываем под длину подшага,
        /// иначе результат зависит от частоты и числа подшагов и быстро становится вязким
        const float_t damping = SR_CLAMP(m_params.damping, 0.f, 0.999f);
        const float_t keep = SR_MATH_NS::Pow(1.f - damping, h * 60.f);

        const float_t contactDamping = SR_CLAMP(m_params.contactDamping, 0.f, 1.f);
        const float_t contactKeep = SR_MATH_NS::Pow(1.f - SR_MIN(contactDamping, 0.999f), h * 60.f);

        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f) {
                particle.velocity = SR_MATH_NS::FVector3::Zero();
                continue;
            }

            particle.velocity = (particle.position - particle.prevPosition) / h * keep;

            /// Толчок коллайдера превращается в скорость частицы, и ткань отлетает от ноги рывком.
            /// Гасим скорость относительно коллайдера только у частиц, которых он касается
            if (particle.inContact && contactDamping > 0.f) {
                const SR_MATH_NS::FVector3 relative = particle.velocity - particle.contactVelocity;
                particle.velocity = particle.contactVelocity + relative * (contactDamping >= 1.f ? 0.f : contactKeep);
            }
        }
    }

    void XPBDSolver::SolveDistanceConstraints(SR_UTILS_NS::Vector<XPBDDistanceConstraint>& constraints, const float_t h) {
        const float_t h2 = h * h;

        for (auto&& constraint : constraints) {
            auto&& a = m_particles[constraint.a];
            auto&& b = m_particles[constraint.b];

            const float_t w = a.invMass + b.invMass;
            if (w == 0.f) {
                continue;
            }

            const SR_MATH_NS::FVector3 delta = a.position - b.position;
            const float_t length = delta.Length();
            if (length < SR_EPSILON) {
                continue;
            }

            const SR_MATH_NS::FVector3 n = delta / length;
            const float_t c = length - constraint.restLength;
            const float_t alpha = constraint.compliance / h2;
            const float_t dLambda = (-c - alpha * constraint.lambda) / (w + alpha);

            constraint.lambda += dLambda;

            a.position += n * (dLambda * a.invMass);
            b.position -= n * (dLambda * b.invMass);
        }
    }

    void XPBDSolver::SolveAttachConstraints(const float_t h) {
        const float_t h2 = h * h;

        for (auto&& constraint : m_attachConstraints) {
            if (constraint.compliance < 0.f) {
                continue;
            }

            auto&& particle = m_particles[constraint.particle];
            if (particle.invMass == 0.f) {
                continue;
            }

            const SR_MATH_NS::FVector3 delta = particle.position - particle.stepAnimPosition;
            const float_t length = delta.Length();
            if (length < SR_EPSILON) {
                continue;
            }

            const SR_MATH_NS::FVector3 n = delta / length;
            const float_t alpha = constraint.compliance / h2;
            const float_t dLambda = (-length - alpha * constraint.lambda) / (particle.invMass + alpha);

            constraint.lambda += dLambda;
            particle.position += n * (dLambda * particle.invMass);
        }
    }

    void XPBDSolver::SolveAngleLimits() {
        if (m_params.maxAngle <= 0.f) {
            return;
        }

        const float_t cosLimit = SR_COS(m_params.maxAngle * SR_MATH_NS::Deg2Rad);
        const float_t sinLimit = SR_SIN(m_params.maxAngle * SR_MATH_NS::Deg2Rad);

        /// Частицы добавляются от корня к кончику, поэтому родитель уже обработан
        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f || particle.parent == SR_ID_INVALID) {
                continue;
            }

            auto&& parent = m_particles[particle.parent];

            const SR_MATH_NS::FVector3 animDir = (particle.stepAnimPosition - parent.stepAnimPosition).NormalizeSafe();
            const SR_MATH_NS::FVector3 delta = particle.position - parent.position;
            const float_t length = delta.Length();

            if (length < SR_EPSILON || animDir.IsZero()) {
                continue;
            }

            const SR_MATH_NS::FVector3 dir = delta / length;
            if (dir.Dot(animDir) >= cosLimit) {
                continue;
            }

            SR_MATH_NS::FVector3 ortho = (dir - animDir * dir.Dot(animDir)).NormalizeSafe();
            if (ortho.IsZero()) {
                ortho = animDir.ArbitraryPerpendicular();
            }

            particle.position = parent.position + (animDir * cosLimit + ortho * sinLimit) * length;
        }
    }

    void XPBDSolver::SolveMaxDistance() {
        if (m_params.maxDistance <= 0.f) {
            return;
        }

        const float_t maxDistanceSq = m_params.maxDistance * m_params.maxDistance;

        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f) {
                continue;
            }

            const SR_MATH_NS::FVector3 delta = particle.position - particle.stepAnimPosition;
            const float_t distanceSq = delta.LengthSq();
            if (distanceSq <= maxDistanceSq) {
                continue;
            }

            particle.position = particle.stepAnimPosition + delta * (m_params.maxDistance / SR_SQRT(distanceSq));
        }
    }

    void XPBDSolver::SolveCollisions(const float_t h) {
        if (m_collisionShapes.empty()) {
            return;
        }

        const float_t invH = 1.f / h;

        for (auto&& particle : m_particles) {
            if (particle.invMass == 0.f) {
                continue;
            }

            for (auto&& shape : m_collisionShapes) {
                switch (shape.type) {
                    case XPBDCollisionShapeType::Sphere:
                    case XPBDCollisionShapeType::Capsule: {
                        SR_MATH_NS::FVector3 closest = shape.stepA;
                        float_t t = 0.f;

                        if (shape.type == XPBDCollisionShapeType::Capsule) {
                            const SR_MATH_NS::FVector3 segment = shape.stepB - shape.stepA;
                            const float_t segmentLengthSq = segment.LengthSq();
                            if (segmentLengthSq > SR_EPSILON) {
                                t = SR_CLAMP((particle.position - shape.stepA).Dot(segment) / segmentLengthSq, 0.f, 1.f);
                                closest = shape.stepA + segment * t;
                            }
                        }

                        const SR_MATH_NS::FVector3 delta = particle.position - closest;
                        const float_t minDistance = shape.radius + particle.radius;
                        const float_t distanceSq = delta.LengthSq();

                        if (distanceSq >= minDistance * minDistance) {
                            break;
                        }

                        const float_t distance = SR_SQRT(distanceSq);
                        if (distance < SR_EPSILON) {
                            break;
                        }

                        particle.position = closest + delta * (minDistance / distance);

                        const SR_MATH_NS::FVector3 prevClosest = shape.stepPrevA + ((shape.type == XPBDCollisionShapeType::Capsule ? shape.stepPrevB : shape.stepPrevA) - shape.stepPrevA) * t;
                        particle.contactVelocity = (closest - prevClosest) * invH;
                        particle.inContact = true;
                        break;
                    }
                    case XPBDCollisionShapeType::Plane: {
                        const float_t distance = (particle.position - shape.stepA).Dot(shape.stepB) - particle.radius;
                        if (distance < 0.f) {
                            particle.position -= shape.stepB * distance;
                            particle.contactVelocity = (shape.stepA - shape.stepPrevA) * invH;
                            particle.inContact = true;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    /// Параметры ближайших точек двух отрезков p1-q1 и p2-q2 (Ericson, Real-Time Collision Detection 5.1.9)
    static void ClosestPointsSegmentSegment(
        const SR_MATH_NS::FVector3& p1, const SR_MATH_NS::FVector3& q1,
        const SR_MATH_NS::FVector3& p2, const SR_MATH_NS::FVector3& q2,
        float_t& s, float_t& t
    ) {
        const SR_MATH_NS::FVector3 d1 = q1 - p1;
        const SR_MATH_NS::FVector3 d2 = q2 - p2;
        const SR_MATH_NS::FVector3 r = p1 - p2;

        const float_t a = d1.Dot(d1);
        const float_t e = d2.Dot(d2);
        const float_t f = d2.Dot(r);

        if (a <= SR_EPSILON && e <= SR_EPSILON) {
            s = 0.f;
            t = 0.f;
            return;
        }

        if (a <= SR_EPSILON) {
            s = 0.f;
            t = SR_CLAMP(f / e, 0.f, 1.f);
            return;
        }

        const float_t c = d1.Dot(r);

        if (e <= SR_EPSILON) {
            t = 0.f;
            s = SR_CLAMP(-c / a, 0.f, 1.f);
            return;
        }

        const float_t b = d1.Dot(d2);
        const float_t denom = a * e - b * b;

        s = denom != 0.f ? SR_CLAMP((b * f - c * e) / denom, 0.f, 1.f) : 0.f;
        t = (b * s + f) / e;

        if (t < 0.f) {
            t = 0.f;
            s = SR_CLAMP(-c / a, 0.f, 1.f);
        }
        else if (t > 1.f) {
            t = 1.f;
            s = SR_CLAMP((b - c) / a, 0.f, 1.f);
        }
    }

    void XPBDSolver::SolveEdgeCollisions(const SR_UTILS_NS::Vector<XPBDDistanceConstraint>& edges, const float_t h) {
        if (m_collisionShapes.empty()) {
            return;
        }

        const float_t invH = 1.f / h;

        for (auto&& shape : m_collisionShapes) {
            /// Плоскость отдельно не проверяется: если оба конца отрезка над ней, то и весь отрезок над ней
            if (shape.type == XPBDCollisionShapeType::Plane) {
                continue;
            }

            const bool isCapsule = shape.type == XPBDCollisionShapeType::Capsule;
            const SR_MATH_NS::FVector3& shapeA = shape.stepA;
            const SR_MATH_NS::FVector3& shapeB = isCapsule ? shape.stepB : shape.stepA;
            const SR_MATH_NS::FVector3& prevShapeA = shape.stepPrevA;
            const SR_MATH_NS::FVector3& prevShapeB = isCapsule ? shape.stepPrevB : shape.stepPrevA;

            for (auto&& edge : edges) {
                auto&& p0 = m_particles[edge.a];
                auto&& p1 = m_particles[edge.b];

                const float_t w0 = p0.invMass;
                const float_t w1 = p1.invMass;
                if (w0 + w1 == 0.f) {
                    continue;
                }

                float_t s = 0.f;
                float_t t = 0.f;
                ClosestPointsSegmentSegment(p0.position, p1.position, shapeA, shapeB, s, t);

                const SR_MATH_NS::FVector3 edgePoint = p0.position + (p1.position - p0.position) * s;
                const SR_MATH_NS::FVector3 shapePoint = shapeA + (shapeB - shapeA) * t;

                const SR_MATH_NS::FVector3 delta = edgePoint - shapePoint;
                const float_t minDistance = shape.radius + SR_MATH_NS::Mix(p0.radius, p1.radius, s);
                const float_t distanceSq = delta.LengthSq();

                if (distanceSq >= minDistance * minDistance) {
                    continue;
                }

                /// С какой стороны коллайдера отрезок был на прошлом подшаге. Если ось коллайдера прошла
                /// через отрезок, текущая нормаль смотрит в обратную сторону и вытолкнула бы ткань насквозь
                const SR_MATH_NS::FVector3 prevEdgePoint = p0.prevPosition + (p1.prevPosition - p0.prevPosition) * s;
                const SR_MATH_NS::FVector3 prevShapePoint = prevShapeA + (prevShapeB - prevShapeA) * t;
                const SR_MATH_NS::FVector3 prevDelta = prevEdgePoint - prevShapePoint;

                const float_t distance = SR_SQRT(distanceSq);

                SR_MATH_NS::FVector3 n;
                float_t penetration = 0.f;

                if (distance < SR_EPSILON) {
                    n = prevDelta.NormalizeSafe();
                    if (n.IsZero()) {
                        continue;
                    }
                    penetration = minDistance;
                }
                else {
                    n = delta / distance;
                    penetration = minDistance - distance;

                    if (n.Dot(prevDelta) < 0.f) {
                        n = -n;
                        penetration = minDistance + distance;
                    }
                }

                const float_t b0 = 1.f - s;
                const float_t b1 = s;

                /// Ограничение снизу не даёт выталкивать конец отрезка на большое расстояние,
                /// когда точка контакта почти у закреплённого конца
                const float_t denom = SR_MAX(w0 * b0 * b0 + w1 * b1 * b1, 0.04f);
                const float_t lambda = penetration / denom;

                p0.position += n * (lambda * w0 * b0);
                p1.position += n * (lambda * w1 * b1);

                const SR_MATH_NS::FVector3 shapeVelocity = (shapePoint - prevShapePoint) * invH;
                if (w0 > 0.f) {
                    p0.contactVelocity = shapeVelocity;
                    p0.inContact = true;
                }
                if (w1 > 0.f) {
                    p1.contactVelocity = shapeVelocity;
                    p1.inContact = true;
                }
            }
        }
    }
}
