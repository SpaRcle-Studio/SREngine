//
// Created by Monika on 28.07.2022.
//

#include <Physics/Rigidbody.h>

#include <Utils/ECS/Transform.h>
#include <Utils/World/Scene.h>
#include <Utils/DebugDraw.h>
#include <Utils/Types/RawMesh.h>

#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsScene.h>
#include <Physics/PhysicsMaterial.h>
#include <Physics/Utils/Utils.h>
#include <Physics/2D/Rigidbody2D.h>
#include <Physics/3D/Rigidbody3D.h>

namespace SR_PTYPES_NS {
    Rigidbody::~Rigidbody() {
        SR_SAFE_DELETE_PTR(m_shape);
        SR_SAFE_DELETE_PTR(m_impl);

        SetMaterial(nullptr);
        SetRawMesh(nullptr);
    }

    bool Rigidbody::InitializeEntity() noexcept {
        m_library = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(GetMeasurement());
        if (!m_library) {
            SR_ERROR("Rigidbody::InitializeEntity() : library not found!");
            return false;
        }

        m_shape = m_library->CreateCollisionShape();
        if (!m_shape) {
            SR_ERROR("Rigidbody::InitializeEntity() : failed to initialize collision shape!");
            return false;
        }

        m_shape->SetRigidbody(this);

        switch (GetMeasurement()) {
            case SR_UTILS_NS::Measurement::Space2D:
                m_impl = m_library->CreateRigidbody2DImpl();
                break;
            case SR_UTILS_NS::Measurement::Space3D:
                m_impl = m_library->CreateRigidbody3DImpl();
                break;
            default:
                SR_ERROR("Rigidbody::InitializeEntity() : unknown space type!");
                return false;
        }

        if (!m_impl) {
            SR_ERROR("Rigidbody::InitializeEntity() : failed to allocate implementation!");
            return false;
        }

        m_impl->SetRigidbody(this);

        m_properties.AddStandardProperty("Center", &m_center)
            .SetSetter([this](void* pValue){
                SetCenter(*reinterpret_cast<SR_MATH_NS::FVector3*>(pValue));
            })
            .SetDrag(0.1f);

        m_properties.AddStandardProperty("Is trigger", &m_isTrigger)
            .SetSetter([this](void* pValue){
                SetIsTrigger(*reinterpret_cast<bool*>(pValue));
            });

        m_properties.AddStandardProperty("Is static", &m_isStatic)
            .SetSetter([this](void* pValue){
                SetIsStatic(*reinterpret_cast<bool*>(pValue));
            })
            .SetSameLine();

        m_properties.AddCustomProperty<SR_UTILS_NS::PathProperty>("Physics material")
            .SetGetter([this]() { return m_material ? m_material->GetResourcePath() : SR_UTILS_NS::Path(); })
            .SetSetter([this](const SR_UTILS_NS::Path& path) {
                SetMaterial(path);
            })
            .AddFileFilter("Physics material", "physmat")
            .SetWidgetEditor("Physics Material Editor");

        m_properties.AddStandardProperty("Mass", &m_mass)
            .SetDrag(0.01f)
            .SetResetValue(1.f)
            .SetSetter([this](void* pValue){
                SetMass(*reinterpret_cast<float_t*>(pValue));
            })
            .SetActiveCondition([this]() -> bool { return !IsStatic(); });

        m_properties.AddEnumProperty<ShapeType>("Collision shape type")
            .SetGetter([this]() -> SR_UTILS_NS::StringAtom {
               return SR_UTILS_NS::EnumReflector::ToStringAtom(GetType());
            })
            .SetSetter([this](const SR_UTILS_NS::StringAtom& value) {
                SetType(SR_UTILS_NS::EnumReflector::FromString<ShapeType>(value));
            })
            .SetFilter([this](const SR_UTILS_NS::StringAtom& value) -> bool {
                return IsShapeSupported(SR_UTILS_NS::EnumReflector::FromString<ShapeType>(value));
            });

        m_properties.AddExternalProperty(m_shape->GetProperties());

        return Entity::InitializeEntity();
    }

    std::string Rigidbody::GetEntityInfo() const {
        return Super::GetEntityInfo() + " | " + SR_UTILS_NS::EnumReflector::ToStringAtom(m_shape->GetType()).ToStringRef();
    }

    void Rigidbody::OnDestroy() {
        m_shape->RemoveDebugShape();

        /// получаем указатель обязательно до OnDestroy
        PhysicsScene::Ptr physicsScene = GetPhysicsScene();

        Super::OnDestroy();

        if (physicsScene) {
            physicsScene->Remove(this);
        }
        else {
           AutoFree([](auto&& pData) {
               delete pData;
           });
        }
    }

    void Rigidbody::OnAttached() {
        Component::OnAttached();
        GetCollisionShape()->UpdateDebugShape();
    }

    const Rigidbody::PhysicsScenePtr& Rigidbody::GetPhysicsScene() const {
        if (!m_physicsScene.Valid()) {
            auto&& pScene = TryGetScene();
            if (!pScene) {
                static Rigidbody::PhysicsScenePtr empty;
                return empty;
            }

            m_physicsScene = pScene->Do<PhysicsScenePtr>([](SR_WORLD_NS::Scene* ptr) {
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

            m_shape->UpdateDebugShape();
        }

        SetMatrixDirty(true);

        Component::OnMatrixDirty();
    }

    bool Rigidbody::UpdateMatrix(bool force) {
        if ((!force && !IsMatrixDirty())) {
            return false;
        }

        if (m_impl) {
            m_impl->UpdateMatrix(force);
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
        m_shape->UpdateDebugShape();
    }

    void Rigidbody::SetMass(float_t mass) {
        m_mass = mass;
        UpdateInertia();
    }

    SR_MATH_NS::FVector3 Rigidbody::GetCenterDirection() const noexcept {
        /// TODO: cache direction
        return m_rotation * (m_scale * m_center);
    }

    ShapeType Rigidbody::GetType() const noexcept {
        return m_shape->GetType();
    }

    void Rigidbody::SetType(ShapeType type) {
        if (m_shape->GetType() == type) {
            return;
        }

        if (m_library && !m_library->IsShapeSupported(type)) {
            SR_ERROR("Rigidbody::SetType() : shape \"" + SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToStringRef() + "\" unsupported!");
            return;
        }

        m_shape->SetType(type);

        SetShapeDirty(true);
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

        m_shape->UpdateDebugShape();

        Super::OnEnable();
    }

    void Rigidbody::OnDisable() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        m_shape->RemoveDebugShape();

        Super::OnDisable();
    }

    SR_UTILS_NS::Measurement Rigidbody::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Unknown;
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
        if (!IsShapeDirty()) {
            return RBUpdShapeRes::Nothing;
        }

        m_shape->RemoveDebugShape();

        if (!m_shape->UpdateShape()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to update shape!");
            return RBUpdShapeRes::Error;
        }

        if (!UpdateShapeInternal()) {
            SR_ERROR("Rigidbody::UpdateShape() : failed to internal update shape!");
            return RBUpdShapeRes::Error;
        }

        m_shape->UpdateDebugShape();

        UpdateMatrix(true);

        SetShapeDirty(false);

        return RBUpdShapeRes::Updated;
    }

    bool Rigidbody::InitBody() {
        if (!m_isBodyDirty) {
            SRHalt("Rigidbody::InitBody() : body is not dirty!");
            return false;
        }

        if (m_impl) {
            m_impl->InitBody();
        }

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

    void Rigidbody::SetRawMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        if (pRawMesh == m_rawMesh) {
            return;
        }

        if (m_rawMesh) {
            m_rawMesh->RemoveUsePoint();
        }

        if ((m_rawMesh = pRawMesh)) {
            m_rawMesh->AddUsePoint();
        }

        SetShapeDirty(true);

        m_meshId = 0;

        if (m_shape) {
            m_shape->ReInitDebugShape();
        }
    }

    bool Rigidbody::IsDebugEnabled() const noexcept {
        if (auto&& pPhysicsScene = GetPhysicsScene()) {
            return pPhysicsScene->IsDebugEnabled();
        }

        return false;
    }

    void Rigidbody::Update(float_t dt) {
        m_shape->Update(dt);
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

    bool Rigidbody::IsShapeSupported(ShapeType type) const {
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

    void Rigidbody::SetMeshId(uint32_t id) {
        m_meshId = id;
        SetShapeDirty(true);
        if (m_shape) {
            m_shape->ReInitDebugShape();
        }
    }

    void Rigidbody::SetRawMesh(const SR_UTILS_NS::Path& path) {
        auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(path);
        if (!pRawMesh) {
            return;
        }

        SetRawMesh(pRawMesh);
    }

    void Rigidbody::Start() {
        Super::Start();
    }
}
