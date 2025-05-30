//
// Created by Monika on 28.07.2022.
//

#include <Physics/Rigidbody.h>

#include <Utils/DebugDraw.h>
#include <Utils/ECS/Transform.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/World/Scene.h>

#include <Physics/2D/Rigidbody2D.h>
#include <Physics/3D/Rigidbody3D.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsMaterial.h>
#include <Physics/PhysicsScene.h>
#include <Physics/Utils/Utils.h>

#include <Codegen/Rigidbody.generated.hpp>

namespace SR_PTYPES_NS {
    Rigidbody::Rigidbody() { GetCollisionShape()->SetRigidbody(this); }

    Rigidbody::~Rigidbody() {
        m_shape.AutoFree();
        SR_SAFE_DELETE_PTR(m_impl);
        SetMaterial(nullptr);
    }

    void Rigidbody::OnDestroy() {
        GetCollisionShape()->RemoveDebugShape();

        /// получаем указатель обязательно до OnDestroy
        PhysicsScene::Ptr physicsScene = GetPhysicsScene();

        Super::OnDestroy();

        if (physicsScene) {
            physicsScene->Remove(this);
        } else {
            AutoFree([](auto&& pData) { delete pData; });
        }
    }

    void Rigidbody::OnAttached() {
        Component::OnAttached();
        GetCollisionShape()->UpdateDebugShape();
    }

    const Rigidbody::PhysicsScenePtr& Rigidbody::GetPhysicsScene() const {
        if (!m_physicsScene) {
            auto&& pScene = TryGetScene();
            if (!pScene) {
                static Rigidbody::PhysicsScenePtr empty;
                return empty;
            }

            m_physicsScene = pScene->GetDataStorage().GetValue<PhysicsScenePtr>();
        }

        return m_physicsScene;
    }

    void Rigidbody::SetShape(const CollisionShape::Ptr& pShape) {
        if (m_shape == pShape) {
            return;
        }

        if (!pShape) {
            SRHalt("Rigidbody::SetShape() : shape is nullptr!");
            return;
        }

        m_shape.AutoFree();
        m_shape = pShape;
        m_shape->SetRigidbody(this);

        SetShapeDirty();
    }

    void Rigidbody::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            pTransform->GetMatrix().Decompose(m_translation, m_rotation, m_scale);

            GetCollisionShape()->UpdateDebugShape();
        }

        SetMatrixDirty(true);

        Component::OnMatrixDirty();
    }

    bool Rigidbody::UpdateMatrix(bool force) {
        SR_TRACY_ZONE;

        if ((!force && !IsMatrixDirty())) {
            return false;
        }

        if (m_impl) {
            m_impl->UpdateMatrix(force);
        }

        SetMatrixDirty(false);

        GetCollisionShape()->UpdateMatrix();

        return true;
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenter() const noexcept { return m_center; }

    float_t Rigidbody::GetMass() const noexcept { return m_mass; }

    bool Rigidbody::IsStatic() const noexcept {
        const ShapeType type = GetCollisionShape()->GetType();

        if (type == ShapeType::Plane3D || type == ShapeType::TriangleMesh2D || type == ShapeType::TriangleMesh3D) {
            return true;
        }

        return m_isStatic;
    }

    void Rigidbody::SetCenter(const SR_MATH_NS::FVector3& center) {
        m_center = center;
        SetMatrixDirty(true);
        GetCollisionShape()->UpdateDebugShape();
    }

    void Rigidbody::SetMass(float_t mass) {
        m_mass = mass;
        UpdateInertia();
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenterDirection() const noexcept {
        /// TODO: cache direction
        return m_rotation * (m_scale * m_center);
    }

    ShapeType Rigidbody::GetType() const noexcept { return GetCollisionShape()->GetType(); }

    void Rigidbody::SetType(ShapeType type) {
        if (GetCollisionShape()->GetType() == type) {
            return;
        }

        if (m_library && !m_library->IsShapeSupported(type)) {
            SR_ERROR(
                "Rigidbody::SetType() : shape \"" + SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToStringRef() +
                "\" unsupported!"
            );
            return;
        }

        GetCollisionShape()->SetType(type);

        SetShapeDirty(true);
    }

    void Rigidbody::OnEnable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            if (!IsBodyDirty()) {
                UpdateInertia();
            }

            physicsScene->Register(this);
        } else {
            SRHalt("Failed to get physics scene!");
        }

        GetCollisionShape()->UpdateDebugShape();

        Super::OnEnable();
    }

    void Rigidbody::OnDisable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        } else {
            SRHalt("Failed to get physics scene!");
        }

        GetCollisionShape()->RemoveDebugShape();

        Super::OnDisable();
    }

    void Rigidbody::SetIsTrigger(bool value) {
        m_isTrigger = value;
        m_isBodyDirty = true;
    }

    void Rigidbody::SetIsStatic(bool value) {
        m_isStatic = value;
        m_isBodyDirty = true;
    }

    RBUpdShapeRes Rigidbody::UpdateShape() {
        SR_TRACY_ZONE;

        if (!IsShapeDirty()) {
            return RBUpdShapeRes::Nothing;
        }

        GetCollisionShape()->RemoveDebugShape();

        if (!GetCollisionShape()->UpdateShape()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to update shape!");
            return RBUpdShapeRes::Error;
        }

        if (!UpdateShapeInternal()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to internal update shape!");
            return RBUpdShapeRes::Error;
        }

        GetCollisionShape()->UpdateDebugShape();

        UpdateMatrix(true);

        SetShapeDirty(false);

        return RBUpdShapeRes::Updated;
    }

    bool Rigidbody::InitBody() {
        SR_TRACY_ZONE;

        if (!m_isBodyDirty) {
            SRHalt("Rigidbody::InitBody() : body is not dirty!");
            return false;
        }

        if (!m_impl) {
            m_library = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(GetMeasurement());
            if (!m_library) {
                SR_ERROR("Rigidbody::InitBody() : library not found!");
                return false;
            }

            switch (GetMeasurement()) {
            case SR_UTILS_NS::Measurement::Space2D:
                m_impl = m_library->CreateRigidbody2DImpl();
                break;
            case SR_UTILS_NS::Measurement::Space3D:
                m_impl = m_library->CreateRigidbody3DImpl();
                break;
            default:
                SR_ERROR("Rigidbody::InitBody() : unknown space type!");
                return false;
            }

            if (!m_impl) {
                SR_ERROR("Rigidbody::InitBody() : failed to allocate implementation!");
                return false;
            }

            m_impl->SetRigidbody(this);
        }

        m_impl->InitBody();

        m_isBodyDirty = false;

        return true;
    }

    void Rigidbody::SetMaterial(PhysicsMaterial* pMaterial) {
        if (pMaterial == m_material) {
            return;
        }

        if (m_material) {
            m_material->RemoveRigidbody(this);
            m_material->RemoveUsePoint();
        }

        if ((m_material = pMaterial)) {
            m_material->AddUsePoint();
            m_material->SetRigidbody(this);
        }
    }

    bool Rigidbody::IsDebugEnabled() const noexcept {
        if (auto&& pPhysicsScene = GetPhysicsScene()) {
            return pPhysicsScene->IsDebugEnabled();
        }

        return false;
    }

    void Rigidbody::Update(float_t dt) {
        GetCollisionShape()->Update(dt);
        Super::Update(dt);
    }

    void Rigidbody::SetMaterial(const SR_UTILS_NS::Path& path) {
        if (path.IsEmpty()) {
            SetMaterial(nullptr);
            return;
        }
        SR_PTYPES_NS::PhysicsMaterial* pMaterial = SR_PTYPES_NS::PhysicsMaterial::Load(path);
        SetMaterial(pMaterial);
    }

    void Rigidbody::UpdateInertia() {
        if (m_impl) {
            m_impl->UpdateInertia();
        }
    }

    void Rigidbody::ClearForces() {
        if (m_impl) {
            m_impl->ClearForces();
        }
    }

    bool Rigidbody::UpdateShapeInternal() {
        SR_TRACY_ZONE;

        if (m_impl) {
            return m_impl->UpdateShapeInternal();
        }
        return false;
    }

    void* Rigidbody::GetHandle() const noexcept { return m_impl ? m_impl->GetHandle() : nullptr; }

    void Rigidbody::Synchronize() {
        if (m_impl) {
            m_impl->Synchronize();
        }
    }

    bool Rigidbody::IsShapeSupported(const ShapeType type) const {
        if (!m_library || !m_library->IsShapeSupported(type)) {
            return false;
        }

        if (SR_PHYSICS_NS::Utils::Is2DShape(type) && GetMeasurement() == SR_UTILS_NS::Measurement::Space2D) {
            return true;
        }

        if (SR_PHYSICS_NS::Utils::Is3DShape(type) && GetMeasurement() == SR_UTILS_NS::Measurement::Space3D) {
            return true;
        }

        return false;
    }

    const CollisionShape::Ptr& Rigidbody::GetCollisionShape() const noexcept {
        if (!m_shape) {
            m_shape = CollisionShape::MakeShared();
        }
        return m_shape;
    }
} // namespace SR_PTYPES_NS
