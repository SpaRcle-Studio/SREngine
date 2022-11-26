//
// Created by Monika on 28.07.2022.
//

#include <Physics/Rigidbody.h>

#include <Utils/ECS/Transform.h>
#include <Utils/World/Scene.h>
#include <Utils/DebugDraw.h>

#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsScene.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody::Rigidbody(LibraryPtr pLibrary)
        : SR_UTILS_NS::Component()
        , m_library(pLibrary)
        , m_shape(pLibrary->CreateCollisionShape())
    { }

    Rigidbody::~Rigidbody() {
        SR_SAFE_DELETE_PTR(m_shape);
    }

    Rigidbody::ComponentPtr Rigidbody::LoadComponent(SR_UTILS_NS::Measurement measurement, SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& type = static_cast<ShapeType>(marshal.Read<int32_t>());
        const auto&& center = marshal.Read<SR_MATH_NS::FVector3>();
        const auto&& mass = marshal.Read<float_t>();

        static auto&& verifyType = [](LibraryImpl* pLibrary, ShapeType shapeType) -> ShapeType {
            if (!pLibrary->IsShapeSupported(shapeType)) {
                SR_WARN("Rigidbody::LoadComponent() : rigidbody has unsupported shape! Replace to default...");
                shapeType = pLibrary->GetDefaultShape();
            }

            return shapeType;
        };

        Rigidbody* pComponent = nullptr;
        LibraryImpl* pLibrary = nullptr;

        switch (measurement) {
            case SR_UTILS_NS::Measurement::Space3D: {
                pLibrary = dataStorage->GetPointer<LibraryImpl>("3DPLib");
                pComponent = pLibrary->CreateRigidbody3D();
                break;
            }
            default:
                SRHalt("Unsupported measurement!");
                return pComponent;
        }

        if (!pComponent) {
            SR_ERROR("Rigidbody::LoadComponent() : failed to create rigidbody!");
            return nullptr;
        }

        if (!pComponent->GetCollisionShape()) {
            SR_ERROR("Rigidbody::LoadComponent() : rigidbody have not collision shape!");
            delete pComponent;
            return nullptr;
        }

        pComponent->SetType(verifyType(pLibrary, type));
        pComponent->SetCenter(center);
        pComponent->SetMass(mass);

        return pComponent;
    }

    SR_HTYPES_NS::Marshal::Ptr Rigidbody::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write<int32_t>(static_cast<int32_t>(m_shape->GetType()));
        pMarshal->Write(m_center);
        pMarshal->Write(m_mass);

        return pMarshal;
    }

    void Rigidbody::OnDestroy() {
        DeInitBody();
        Super::OnDestroy();
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

        SetMatrixDirty(true);

        Component::OnMatrixDirty();
    }

    bool Rigidbody::UpdateMatrix() {
        if (!IsMatrixDirty() || !m_shape) {
            return false;
        }

        SetMatrixDirty(false);

        m_shape->SetScale(m_scale);
        m_shape->UpdateMatrix();

        return true;
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenter() const noexcept {
        return m_center;
    }

    float_t Rigidbody::GetMass() const noexcept {
        return m_mass;
    }

    void Rigidbody::SetCenter(const SR_MATH_NS::FVector3& center) {
        m_center = center;
        SetMatrixDirty(true);
        UpdateDebugShape();
    }

    void Rigidbody::SetMass(float_t mass) {
        m_mass = mass;
        UpdateInertia();
    }

    void Rigidbody::UpdateDebugShape() {
        if (SR_PHYSICS_UTILS_NS::IsBox(GetType())) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                    m_debugId,
                    m_translation + GetCenterDirection(),
                    m_rotation,
                    m_scale * m_shape->GetSize(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }

        if (SR_PHYSICS_UTILS_NS::IsSphere(GetType())) {
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
        return m_shape->GetType();
    }

    void Rigidbody::SetType(ShapeType type) {
        if (m_shape->GetType() == type) {
            return;
        }

        m_shape->SetType(type);

        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }

        UpdateDebugShape();

        SetShapeDirty(true);

    #ifdef SR_DEBUG
        SRAssert(m_library);

        switch (GetMeasurement()) {
            case SR_UTILS_NS::Measurement::Space2D:
                SRAssert(SR_PHYSICS_UTILS_NS::Is2DShape(GetType()));
                break;
            case SR_UTILS_NS::Measurement::Space3D:
                SRAssert(SR_PHYSICS_UTILS_NS::Is3DShape(GetType()));
                break;
            default:
                SRHalt("Unsupported measurement! Type: " + SR_UTILS_NS::EnumReflector::ToString(GetMeasurement()));
                break;
        }
    #endif
    }

    void Rigidbody::OnEnable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            if (!InitBody() || UpdateShape() == RBUpdShapeRes::Error) {
                SR_ERROR("Rigidbody::OnEnable() : failed to init/update!");
            }
            else {
                UpdateInertia();
                physicsScene->Register(this);
            }
        }
        else {
            SRHalt("Failed to get physics scene!");
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

        DeInitBody();
        Super::OnDisable();
    }

    SR_UTILS_NS::Measurement Rigidbody::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Unknown;
    }

    void Rigidbody::SetIsTrigger(bool value) {
        m_isTrigger = value;
    }

    void Rigidbody::SetIsStatic(bool value) {
        m_isStatic = value;
        SetShapeDirty(true);
    }

    RBUpdShapeRes Rigidbody::UpdateShape() {
        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }

        if (!m_shape->UpdateShape()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to update shape!");
            return RBUpdShapeRes::Error;
        }

        if (!UpdateShapeInternal()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to internal update shape!");
            return RBUpdShapeRes::Error;
        }

        UpdateDebugShape();

        SetShapeDirty(false);

        return RBUpdShapeRes::Updated;
    }
}
