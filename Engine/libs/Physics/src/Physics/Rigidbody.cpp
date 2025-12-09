//
// Created by Monika on 28.07.2022.
//

#include <Physics/Rigidbody.h>

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/World/Scene.h>
#include <Utils/DebugDraw.h>
#include <Utils/Types/RawMesh.h>

#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsScene.h>
#include <Physics/PhysicsMaterial.h>
#include <Physics/Utils/Utils.h>
#include <Physics/2D/Rigidbody2D.h>
#include <Physics/3D/Rigidbody3D.h>

#include <Codegen/Rigidbody.generated.hpp>

namespace SR_PTYPES_NS {
    Rigidbody::Rigidbody() { }

    Rigidbody::~Rigidbody() {
        SRAssert(m_shapes.empty());
        SR_SAFE_DELETE_PTR(m_impl);
    }

    void Rigidbody::OnDestroy() {
        for (auto&& pShape : m_shapes) {
            pShape->OnRigidbodyDetached();
        }

        /// получаем указатель обязательно до OnDestroy
        PhysicsScene::Ptr physicsScene = GetPhysicsScene();

        /// Super::OnDestroy();
        /// TODO: неправильно. уничтожение компонента делегировано другой сущности (PhysicsScene)
        SetParent(nullptr);

        if (physicsScene) {
            physicsScene->Remove(this);
        }
        else {
           GetThis().AutoFree([](auto&& pData) {
               delete pData;
           });
        }
    }

    void Rigidbody::OnAttached() {
        Component::OnAttached();
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

    void Rigidbody::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            pTransform->GetMatrix().Decompose(
                m_translation,
                m_rotation,
                m_scale
            );

            for (auto&& pShape : m_shapes) {
                pShape->UpdateDebugShape();
            }
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

        for (auto&& pShape : m_shapes) {
            pShape->UpdateMatrix();
        }

        return true;
    }

    //SR_MATH_NS::FVector3 Rigidbody::GetCenter() const noexcept {
    //    return m_center;
    //}

    float_t Rigidbody::GetMass() const noexcept {
        return m_mass;
    }

    bool Rigidbody::IsStatic() const noexcept {
        //const ShapeType type = GetCollisionShape()->GetType();

        //if (type == ShapeType::Plane3D || type == ShapeType::TriangleMesh2D || type == ShapeType::TriangleMesh3D) {
        //    return true;
        //}

        return m_isStatic;
    }

    void Rigidbody::SetMass(float_t mass) {
        if (m_mass == mass) {
            return;
        }
        m_mass = SR_CLAMP(mass, static_cast<float_t>(SR_EPSILON), std::numeric_limits<float_t>::max());
        UpdateInertia();
    }

    void Rigidbody::OnEnable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            if (!IsBodyDirty()) {
                UpdateInertia();
            }

            physicsScene->Register(this);
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        for (auto&& pShape : m_shapes) {
            pShape->UpdateDebugShape();
        }

        Super::OnEnable();
    }

    void Rigidbody::OnDisable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        for (auto&& pShape : m_shapes) {
            pShape->RemoveDebugShape();
        }

        Super::OnDisable();
    }

    void Rigidbody::AttachShape(CollisionShape* pShape) {
        if (std::ranges::find(m_shapes, pShape) != m_shapes.end()) {
            SRHalt("Rigidbody::AttachShape() : shape already attached!");
            return;
        }
        m_shapes.emplace_back(pShape);
        m_isBodyDirty = true;
    }

    void Rigidbody::DetachShape(CollisionShape* pShape) {
        auto&& pIt = std::ranges::find(m_shapes, pShape);
        if (pIt != m_shapes.end()) {
            m_shapes.erase(pIt);
            pShape->OnRigidbodyDetached();
            m_isBodyDirty = true;
        }
    }

    void Rigidbody::SetIsTrigger(bool value) {
        m_isTrigger = value;
        m_isBodyDirty = true;
    }

    void Rigidbody::SetIsStatic(bool value) {
        m_isStatic = value;
        m_isBodyDirty = true;
    }

    void Rigidbody::SetUseGravity(bool value) {
        m_useGravity = value;
        m_isBodyDirty = true;
    }

    void Rigidbody::SetFetchResults(bool value) {
        m_fetchResults = value;

        if (auto&& pImpl = GetImpl<RigidbodyImpl>()) {
            pImpl->SetSyncAllowed(m_fetchResults);
        }
    }

    RBUpdShapeRes Rigidbody::UpdateShape() {
        SR_TRACY_ZONE;

        if (!IsShapeDirty()) {
            return RBUpdShapeRes::Nothing;
        }

        bool changed = false;
        for (auto&& pShape : m_shapes) {
            const auto result = pShape->UpdateShape();
            changed |= result.has_value() && result.value();

            if (result && !result.value()) {
                SR_ERROR("Rigidbody::UpdateShape() : failed to update shape!");
                return RBUpdShapeRes::Error;
            }
        }

        if (changed && !UpdateShapeInternal()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to internal update shape!");
            return RBUpdShapeRes::Error;
        }

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
        m_impl->SetSyncAllowed(m_fetchResults);

        m_isBodyDirty = false;

        return true;
    }

    bool Rigidbody::IsDebugEnabled() const noexcept {
        if (auto&& pPhysicsScene = GetPhysicsScene()) {
            return pPhysicsScene->IsDebugEnabled();
        }

        return false;
    }

    void Rigidbody::Update(float_t dt) {
        //GetCollisionShape()->Update(dt);
        Super::Update(dt);
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

    void* Rigidbody::GetHandle() const noexcept {
        return m_impl ? m_impl->GetHandle() : nullptr;
    }

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

    void Rigidbody::SetCenterOfMassOffset(const SR_MATH_NS::FVector3& offset) {
        m_centerOfMassOffset = offset;
        if (m_impl) {
            m_impl->UpdateInertia();
        }
    }

    SR_HTYPES_NS::SharedPtr<CollisionShape> Rigidbody::AddCollider(ShapeType type) {
        auto&& pSceneObject = GetSceneObject();
        if (!pSceneObject) {
            SRHalt("Rigidbody::AddCollider() : scene object is nullptr!");
            return nullptr;
        }

        auto&& pCollider = pSceneObject->AddComponent<CollisionShape>();
        if (!pCollider) {
            SRHalt("Rigidbody::AddCollider() : failed to add collider!");
            return nullptr;
        }

        pCollider->SetType(type);
        pCollider->SetRigidbody(this);
        return pCollider;
    }
}
