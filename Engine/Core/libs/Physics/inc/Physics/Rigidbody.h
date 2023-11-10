//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY_H
#define SRENGINE_RIGIDBODY_H

#include <Physics/PhysicsLib.h>
#include <Physics/CollisionShape.h>

#include <Utils/Common/Measurement.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_PHYSICS_NS {
    class PhysicsScene;
    class LibraryImpl;

    /// Rigidbody Update Shape Result
    enum class RBUpdShapeRes : uint8_t {
        Updated = 0,
        Error = 1,
        Nothing = 2
    };
}

namespace SR_PTYPES_NS {
    class PhysicsMaterial;
    class Rigidbody;

    class RigidbodyImpl : public SR_UTILS_NS::NonCopyable {
    protected:
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        SR_NODISCARD virtual void* GetHandle() const noexcept = 0;

    public:
        void SetRigidbody(Rigidbody* pRigidbody) { m_rigidbody = pRigidbody; }

        virtual void UpdateInertia() { }
        virtual void ClearForces() { }

        virtual void Synchronize() { }

        virtual bool InitBody() { return true; }

        virtual bool UpdateMatrix(bool force) { return true; }
        virtual bool UpdateShapeInternal() { return true; }

    protected:
        template<typename T> SR_NODISCARD T* GetRigidbody() const noexcept {
            return dynamic_cast<T*>(m_rigidbody);
        }

    protected:
        Rigidbody* m_rigidbody = nullptr;
        SR_MATH_NS::Quaternion m_rigidbodyRotation = SR_MATH_NS::InfinityQuaternion;
        SR_MATH_NS::FVector3 m_rigidbodyTranslation = SR_MATH_NS::InfinityFV3;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class Rigidbody : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
    protected:
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        ~Rigidbody() override;

    public:
        static Component* LoadComponent(SR_UTILS_NS::Measurement measurement, SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

        bool UpdateMatrix(bool force = false);
        void Synchronize();

        std::string GetEntityInfo() const override;

        void UpdateInertia();
        void ClearForces();

        SR_NODISCARD virtual SR_UTILS_NS::Measurement GetMeasurement() const;
        SR_NODISCARD bool InitializeEntity() noexcept override;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD CollisionShape* GetCollisionShape() const noexcept { return m_shape; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenter() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenterDirection() const noexcept;
        SR_NODISCARD float_t GetMass() const noexcept;
        SR_NODISCARD bool IsTrigger() const noexcept { return m_isTrigger; }
        SR_NODISCARD bool IsStatic() const noexcept { return m_isStatic; }
        SR_NODISCARD bool IsMatrixDirty() const noexcept { return m_isMatrixDirty; }
        SR_NODISCARD bool IsShapeDirty() const noexcept { return m_isShapeDirty; }
        SR_NODISCARD bool IsBodyDirty() const noexcept { return m_isBodyDirty; }
        SR_NODISCARD void* GetHandle() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD SR_MATH_NS::Quaternion GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const noexcept { return m_scale; }
        SR_NODISCARD SR_HTYPES_NS::RawMesh* GetRawMesh() const noexcept { return m_rawMesh; }
        SR_NODISCARD int32_t GetMeshId() const noexcept { return m_meshId; }
        SR_NODISCARD PhysicsMaterial* GetPhysicsMaterial() const noexcept { return m_material; }
        SR_NODISCARD bool IsDebugEnabled() const noexcept;
        SR_NODISCARD RBUpdShapeRes UpdateShape();
        SR_NODISCARD bool IsShapeSupported(ShapeType type) const;

        void SetMatrixDirty(bool value) { m_isMatrixDirty = value; }
        void SetShapeDirty(bool value) { m_isShapeDirty = value; }

        virtual void SetIsTrigger(bool value);
        virtual void SetIsStatic(bool value);

        virtual void SetCenter(const SR_MATH_NS::FVector3& center);
        virtual void SetType(ShapeType type);
        void SetMass(float_t mass);

        void SetMaterial(PhysicsMaterial* pMaterial);
        void SetMaterial(const SR_UTILS_NS::Path& path);
        void SetRawMesh(SR_HTYPES_NS::RawMesh* pRawMesh);
        void SetMeshId(int32_t id) { m_meshId = id; SetShapeDirty(true); }

        bool InitBody();

        template<typename T = LibraryImpl> SR_NODISCARD T* GetLibrary() const {
            if (auto&& pLibrary = dynamic_cast<T*>(m_library)) {
                return pLibrary;
            }
            SRHalt("Failed to cast library!");
            return nullptr;
        }

    protected:
        bool UpdateShapeInternal();

        void Update(float_t dt) override;
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDestroy() override;

        void OnMatrixDirty() override;

        SR_NODISCARD const PhysicsScenePtr& GetPhysicsScene() const;

        template<typename T> SR_NODISCARD T* GetImpl() const {
            return dynamic_cast<T*>(m_impl);
        }

    protected:
        /// shape всегда присутствует, но у него может отличаться внутрення реализация
        CollisionShape::Ptr m_shape = nullptr;
        RigidbodyImpl* m_impl = nullptr;
        LibraryPtr m_library = nullptr;

        mutable PhysicsScenePtr m_physicsScene;

        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;

        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();

        SR_PTYPES_NS::PhysicsMaterial* m_material = nullptr;
        SR_HTYPES_NS::RawMesh* m_rawMesh = nullptr;

        int32_t m_meshId = 0;

        SR_MATH_NS::FVector3 m_center;

        bool m_isTrigger = false;
        bool m_isStatic = false;

        bool m_isBodyDirty = true;
        bool m_isMatrixDirty = false;
        bool m_isShapeDirty = false;

        float_t m_mass = 1.f;

    };
}

#endif //SRENGINE_RIGIDBODY_H
