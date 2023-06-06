//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY_H
#define SRENGINE_RIGIDBODY_H

#include <Physics/PhysicsLib.h>
#include <Physics/CollisionShape.h>

#include <Utils/Common/Measurement.h>
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

    class Rigidbody : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
    protected:
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        explicit Rigidbody(LibraryPtr pLibrary);
        ~Rigidbody() override;

    public:
        static Component* LoadComponent(SR_UTILS_NS::Measurement measurement, SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        virtual bool UpdateMatrix(bool force = false);

        virtual void Synchronize() { }

        virtual std::string GetEntityInfo() const override;

        virtual bool UpdateShapeInternal() { return false; }
        virtual void UpdateInertia() { }
        virtual void ClearForces() { }

        SR_NODISCARD virtual SR_UTILS_NS::Measurement GetMeasurement() const;

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
        SR_NODISCARD virtual void* GetHandle() const noexcept = 0;
        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD SR_MATH_NS::Quaternion GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const noexcept { return m_scale; }
        SR_NODISCARD SR_HTYPES_NS::RawMesh* GetRawMesh() const noexcept { return m_rawMesh; }
        SR_NODISCARD int32_t GetMeshId() const noexcept { return m_meshId; }
        SR_NODISCARD PhysicsMaterial* GetPhysicsMaterial() const noexcept { return m_material; }
        SR_NODISCARD bool IsDebugEnabled() const noexcept;
        SR_NODISCARD RBUpdShapeRes UpdateShape();

        void SetMatrixDirty(bool value) { m_isMatrixDirty = value; }
        void SetShapeDirty(bool value) { m_isShapeDirty = value; }

        virtual void SetIsTrigger(bool value);
        virtual void SetIsStatic(bool value);

        virtual void SetCenter(const SR_MATH_NS::FVector3& center);
        virtual void SetType(ShapeType type);
        void SetMass(float_t mass);

        void SetMaterial(PhysicsMaterial* pMaterial);
        void SetRawMesh(SR_HTYPES_NS::RawMesh* pRawMesh);
        void SetMeshId(int32_t id) { m_meshId = id; }

        virtual bool InitBody();

    protected:
        void Update(float_t dt) override;
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDestroy() override;

        void OnMatrixDirty() override;

        SR_NODISCARD const PhysicsScenePtr& GetPhysicsScene() const;

        template<typename T> SR_NODISCARD T* GetLibrary() const {
            if (auto&& pLibrary = dynamic_cast<T*>(m_library)) {
                return pLibrary;
            }

            SRHalt("Failed to cast library!");

            return nullptr;
        }

    protected:
        /// shape всегда присутствует, но у него может отличаться внутрення реализация
        CollisionShape::Ptr m_shape = nullptr;
        LibraryPtr m_library = nullptr;

        mutable PhysicsScenePtr m_physicsScene;

        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::FVector3 m_rigidbodyTranslation = SR_MATH_NS::InfinityFV3;

        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::Quaternion m_rigidbodyRotation = SR_MATH_NS::InfinityQuaternion;

        SR_MATH_NS::FVector3 m_scale;

        SR_PTYPES_NS::PhysicsMaterial* m_material = nullptr;
        SR_HTYPES_NS::RawMesh* m_rawMesh = nullptr;

        int32_t m_meshId = 0;

        SR_MATH_NS::FVector3 m_center;

        bool m_isTrigger = false;
        bool m_isStatic = false;

        bool m_isBodyDirty = false;
        bool m_isMatrixDirty = false;
        bool m_isShapeDirty = false;

        float_t m_mass = 1.f;

    };
}

#endif //SRENGINE_RIGIDBODY_H
