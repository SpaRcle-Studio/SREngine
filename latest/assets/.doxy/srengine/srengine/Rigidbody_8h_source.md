

# File Rigidbody.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**Rigidbody.h**](Rigidbody_8h.md)

[Go to the documentation of this file](Rigidbody_8h.md)


```C++
//
// Created by Monika on 28.07.2022.
//

#ifndef SR_ENGINE_RIGIDBODY_H
#define SR_ENGINE_RIGIDBODY_H

#include <Physics/macros.h>

#include <Physics/PhysicsLib.h>
#include <Physics/PhysicsMaterial.h>
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

    enum class RBUpdShapeRes : uint8_t {
        Updated = 0,
        Error = 1,
        Nothing = 2
    };
}

namespace SR_PTYPES_NS {
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

        void SetSyncAllowed(bool allowed) { m_isSyncAllowed = allowed; }

    protected:
        template<typename T> SR_NODISCARD T* GetRigidbody() const noexcept {
            return dynamic_cast<T*>(m_rigidbody);
        }

    protected:
        bool m_isSyncAllowed = true;
        Rigidbody* m_rigidbody = nullptr;
        SR_MATH_NS::Quaternion m_rigidbodyRotation = SR_MATH_NS::InfinityQuaternion;
        SR_MATH_NS::FVector3 m_rigidbodyTranslation = SR_MATH_NS::InfinityFV3;

    };


    class Rigidbody : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
        SR_CLASS()
    protected:
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Rigidbody>;

    public:
        Rigidbody();
        ~Rigidbody() override;

    public:
        bool UpdateMatrix(bool force = false);
        void Synchronize();

        void UpdateInertia();
        void ClearForces();

        SR_NODISCARD virtual SR_UTILS_NS::Measurement GetMeasurement() const = 0;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        //SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD const std::vector<CollisionShape*>& GetShapes() const noexcept { return m_shapes; }
        SR_NODISCARD float_t GetMass() const noexcept;
        SR_NODISCARD bool IsTrigger() const noexcept { return m_isTrigger; }
        SR_NODISCARD bool IsUseGravity() const noexcept { return m_useGravity; }
        SR_NODISCARD bool IsStatic() const noexcept;
        SR_NODISCARD bool IsMatrixDirty() const noexcept { return m_isMatrixDirty; }
        SR_NODISCARD bool IsShapeDirty() const noexcept { return m_isShapeDirty; }
        SR_NODISCARD bool IsBodyDirty() const noexcept { return m_isBodyDirty; }
        SR_NODISCARD void* GetHandle() const noexcept;
        SR_NODISCARD const SR_MATH_NS::FVector3& GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD const SR_MATH_NS::Quaternion& GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetScale() const noexcept { return m_scale; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetCenterOfMassOffset() const noexcept { return m_centerOfMassOffset; }
        SR_NODISCARD bool IsDebugEnabled() const noexcept;
        SR_NODISCARD RBUpdShapeRes UpdateShape();
        SR_NODISCARD bool IsShapeSupported(ShapeType type) const;

        SR_HTYPES_NS::SharedPtr<CollisionShape> AddCollider(ShapeType type);

        void SetMatrixDirty(const bool value = true) { m_isMatrixDirty = value; }
        void SetShapeDirty(const bool value = true) { m_isShapeDirty = value; }

        void AttachShape(CollisionShape* pShape);
        void DetachShape(CollisionShape* pShape);

        virtual void SetIsTrigger(bool value);
        virtual void SetIsStatic(bool value);
        virtual void SetUseGravity(bool value);
        virtual void SetFetchResults(bool value);

        virtual void SetCenterOfMassOffset(const SR_MATH_NS::FVector3& offset);

        void SetMass(float_t mass);

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
        float_t m_mass = 1.f;
        bool m_isTrigger = false;
        bool m_isStatic = false;
        bool m_useGravity = true;
        SR_MATH_NS::FVector3 m_centerOfMassOffset;

        bool m_fetchResults = true;

        RigidbodyImpl* m_impl = nullptr;
        LibraryPtr m_library = nullptr;

        mutable std::vector<CollisionShape*> m_shapes;
        mutable PhysicsScenePtr m_physicsScene;

        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();


        bool m_isBodyDirty = true;
        bool m_isMatrixDirty = false;
        bool m_isShapeDirty = false;

    };
}

#endif //SR_ENGINE_RIGIDBODY_H
```


