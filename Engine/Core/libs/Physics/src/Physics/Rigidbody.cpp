//
// Created by Monika on 28.07.2022.
//

#include <Utils/ECS/Transform.h>
#include <Utils/World/Scene.h>
#include <Utils/DebugDraw.h>

#include <Physics/Rigidbody.h>
#include <Physics/PhysicsScene.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody::Rigidbody(ShapeType type)
        : SR_UTILS_NS::Component()
    {
        SR_UTILS_NS::Component::InitComponent<Rigidbody>();
        SetType(type);
    }

    Rigidbody::Rigidbody()
        : Rigidbody(Tools::GetDefaultShape())
    { }

    Rigidbody::~Rigidbody() {
        SRAssert2(!m_motionState && !m_rigidbody && !m_shape, "Not all data deleted!");
    }

    Rigidbody::ComponentPtr Rigidbody::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& type = static_cast<ShapeType>(marshal.Read<int32_t>());
        const auto&& center = marshal.Read<SR_MATH_NS::FVector3>();
        const auto&& mass = marshal.Read<float_t>();

        auto&& pComponent = new Rigidbody(type);

        pComponent->SetCenter(center);
        pComponent->SetMass(mass);

        return pComponent;
    }

    SR_HTYPES_NS::Marshal::Ptr Rigidbody::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write<int32_t>(static_cast<int32_t>(m_type));
        pMarshal->Write(m_center);
        pMarshal->Write(m_mass);

        return pMarshal;
    }

    void Rigidbody::OnDestroy() {
        DeInitBody();
        Component::OnDestroy();
        delete this;
    }

    void Rigidbody::OnAttached() {
        Component::OnAttached();
    }

    void Rigidbody::DeInitBody() {
        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }

        if (auto&& physicsScene = GetPhysicsScene()) {
            if (m_rigidbody) {
                physicsScene->Remove(this);
            }
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        SR_SAFE_DELETE_PTR(m_motionState);
        SR_SAFE_DELETE_PTR(m_rigidbody);
        SR_SAFE_DELETE_PTR(m_shape);
    }

    bool Rigidbody::InitBody() {
        auto&& pTransform = GetTransform();

        if (!pTransform) {
            return false;
        }

        UpdateShape();

        auto&& localInertia = m_shape->CalculateLocalInertia(m_mass);

        btTransform startTransform;
        startTransform.setIdentity();

        SRAssert2(!m_motionState && !m_rigidbody, "Rigidbody is already initialized!");

        m_motionState = new btDefaultMotionState(startTransform);

        m_dirty = true;

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                m_mass,        /// mass, in kg. 0 -> Static object, will never move.
                m_motionState,
                (btCollisionShape*)m_shape->GetHandle(), /// collision shape of body
                Tools::FV3ToBtV3(localInertia)   /// local inertia
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
            pTransform->GetMatrix().Decompose(
                    m_translation,
                    m_rotation,
                    m_scale
            );
            UpdateDebugShape();
        }

        m_dirty = true;
        Component::OnMatrixDirty();
    }

    void Rigidbody::UpdateMatrix() {
        if (!m_rigidbody || !m_dirty || !m_shape) {
            return;
        }

        m_dirty = false;

        auto&& translation = m_translation + GetCenterDirection();

        m_shape->SetScale(m_scale);
        m_shape->Update();

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

    SR_MATH_NS::FVector3 Rigidbody::GetCenter() const noexcept {
        return m_center;
    }

    float_t Rigidbody::GetMass() const noexcept {
        return m_mass;
    }

    void Rigidbody::SetCenter(const SR_MATH_NS::FVector3& center) {
        m_center = center;
        m_dirty = true;
        UpdateDebugShape();
    }

    void Rigidbody::SetMass(float_t mass) {
        m_mass = mass;
        m_dirty = true;

        if (m_rigidbody) {
            auto&& inertia = m_shape ? m_shape->CalculateLocalInertia(m_mass) : SR_MATH_NS::FVector3(0, 0, 0);
            m_rigidbody->setMassProps(m_mass, Tools::FV3ToBtV3(inertia));
        }
    }

    void Rigidbody::UpdateDebugShape() {
        if (!m_shape) {
            return;
        }

        if (Tools::IsBox(GetType())) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                    m_debugId,
                    m_translation + GetCenterDirection(),
                    m_rotation,
                    m_scale * m_shape->GetSize(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }

        if (Tools::IsSphere(GetType())) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawSphere(
                    m_debugId,
                    m_translation + GetCenterDirection(),
                    m_rotation,
                    (m_scale * m_shape->GetSize()).Max3(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenterDirection() const noexcept {
        return m_rotation * m_center;
    }

    ShapeType Rigidbody::GetType() const noexcept {
        return m_type;
    }

    void Rigidbody::SetType(ShapeType type) {
        if (m_shape && m_shape->GetType() == type) {
            return;
        }

        m_type = type;

        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }

        UpdateShape();

        m_dirty = true;
    }

    void Rigidbody::UpdateShape() {
        if (!m_shape || m_shape->GetType() != m_type) {
            SR_SAFE_DELETE_PTR(m_shape)

            if (!Tools::IsShapeSupported(m_type)) {
                m_type = Tools::GetDefaultShape();
            }

            m_shape = new CollisionShape(m_type);
            if (m_rigidbody) {
                m_rigidbody->setCollisionShape(static_cast<btCollisionShape *>(m_shape->GetHandle()));
            }
            UpdateDebugShape();
        }
    }

    void Rigidbody::AddLocalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(m_rigidbody->getLinearVelocity() + Tools::FV3ToBtV3(m_rotation * velocity));
        }
    }

    void Rigidbody::AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(m_rigidbody->getLinearVelocity() + Tools::FV3ToBtV3(velocity));
        }
    }

    void Rigidbody::SetVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(Tools::FV3ToBtV3(velocity));
        }
    }

    void Rigidbody::OnEnable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            InitBody();
            physicsScene->Register(this);
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        Component::OnEnable();
    }

    void Rigidbody::OnDisable() {
        DeInitBody();
        Component::OnDisable();
    }
}
