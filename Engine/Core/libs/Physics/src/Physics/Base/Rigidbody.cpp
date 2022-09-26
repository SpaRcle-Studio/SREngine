//
// Created by Monika on 28.07.2022.
//

#include <Physics/Base/Rigidbody.h>
#include <Physics/PhysicsScene.h>
#include <Utils/ECS/Transform.h>
#include <Utils/World/Scene.h>
#include <Utils/DebugDraw.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody::Rigidbody()
        : SR_UTILS_NS::Component()
        , m_size(SR_MATH_NS::FVector3::One())
    { }

    Rigidbody::~Rigidbody() {
        SR_SAFE_DELETE_PTR(m_motionState);
        SR_SAFE_DELETE_PTR(m_rigidbody);
        SR_SAFE_DELETE_PTR(m_shape);
    }

    void Rigidbody::OnDestroy() {
        if (m_debugId == SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().DrawCube(m_debugId);
            m_debugId = SR_ID_INVALID;
        }

        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }

        Component::OnDestroy();
    }

    void Rigidbody::OnAttached() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            InitShape();
            InitBody();

            physicsScene->Register(this);
        }

        Component::OnAttached();
    }

    bool Rigidbody::InitShape() {
        m_shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
        return true;
    }

    bool Rigidbody::InitBody() {
        auto&& pTransform = GetTransform();

        if (!pTransform) {
            return false;
        }

        btScalar mass(1.f);

        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            m_shape->calculateLocalInertia(mass, localInertia);

        btTransform startTransform;
        startTransform.setIdentity();

        m_motionState = new btDefaultMotionState(startTransform);

        m_dirty = true;

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                mass,          /// mass, in kg. 0 -> Static object, will never move.
                m_motionState,
                m_shape,       /// collision shape of body
                localInertia   /// local inertia
        );
        m_rigidbody = new btRigidBody(rigidBodyCI);

        m_rigidbody->setActivationState(DISABLE_DEACTIVATION);

        m_rigidbody->setUserPointer(this);

        return true;
    }

    Rigidbody::PhysicsScenePtr Rigidbody::GetPhysicsScene() {
        if (!m_physicsScene.Valid()) {
            m_physicsScene = GetScene().Do<PhysicsScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<PhysicsScenePtr>();
            }, PhysicsScenePtr());
        }

        return m_physicsScene;
    }

    void Rigidbody::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            m_translation = pTransform->GetTranslation();
            m_rotation = pTransform->GetQuaternion();
            m_scale = pTransform->GetScale();
            UpdateDebugShape();
        }

        m_dirty = true;
        Component::OnMatrixDirty();
    }

    void Rigidbody::UpdateMatrix() {
        if (!m_rigidbody || !m_dirty) {
            return;
        }

        m_dirty = false;

        auto&& translation = m_translation + GetCenterDirection();
        auto&& scale = m_scale * GetSizeDirection();

        m_shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
        startTransform.setRotation(btQuaternion(m_rotation.X(), m_rotation.Y(), m_rotation.Z(), m_rotation.W()));

        m_rigidbody->setWorldTransform(startTransform);

        if (m_rigidbody->getMotionState()) {
            m_rigidbody->getMotionState()->setWorldTransform(startTransform);
        }

        m_rigidbody->clearForces();
        m_rigidbody->setAngularVelocity(btVector3(0, 0, 0));
        m_rigidbody->setLinearVelocity(btVector3(0, 0, 0));
    }

    SR_MATH_NS::FVector3 Rigidbody::GetSize() const noexcept {
        return m_size;
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenter() const noexcept {
        return m_center;
    }

    float_t Rigidbody::GetMass() const noexcept {
        return m_mass;
    }

    void Rigidbody::SetSize(const SR_MATH_NS::FVector3 &size) {
        m_size = size;
        m_dirty = true;
        UpdateDebugShape();
    }

    void Rigidbody::SetCenter(const SR_MATH_NS::FVector3& center) {
        m_center = center;
        m_dirty = true;
        UpdateDebugShape();
    }

    void Rigidbody::SetMass(float_t mass) {
        m_mass = mass;
        m_dirty = true;
    }

    void Rigidbody::UpdateDebugShape() {
        m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                m_scale * GetSizeDirection(),
                SR_MATH_NS::FColor(0, 255, 0, 255),
                SR_FLOAT_MAX
        );
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenterDirection() const noexcept {
        return m_rotation * m_center;
    }

    SR_MATH_NS::FVector3 Rigidbody::GetSizeDirection() const noexcept {
        return m_size;
    }
}
