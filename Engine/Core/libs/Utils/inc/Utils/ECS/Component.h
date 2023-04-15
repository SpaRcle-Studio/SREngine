//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <Utils/ECS/EntityManager.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/Marshal.h>
#include <Utils/Types/SafeVariable.h>
#include <Utils/World/Scene.h>
#include <Utils/Common/CollisionData.h>

/**
 * Awake -> OnEnabled -> Start -> Update -> FixedUpdate
 */

namespace SR_HTYPES_NS {
    class DataStorage;
}

#define SR_INITIALIZE_COMPONENT(name)                                                                                   \
public:                                                                                                                 \
    SR_INLINE static const std::string COMPONENT_NAME = #name; /** NOLINT */                                            \
    SR_INLINE static const uint64_t COMPONENT_HASH_NAME = SR_HASH_STR(name::COMPONENT_NAME); /** NOLINT */              \
    SR_NODISCARD uint64_t GetComponentHashName() const override { return name::COMPONENT_HASH_NAME; }                   \
    SR_NODISCARD const std::string& GetComponentName() const override { return name::COMPONENT_NAME; }                  \

namespace SR_UTILS_NS {
    class ComponentManager;
    class Component;
    class IComponentable;
    class Transform2D;
    class Transform3D;
    class Transform;
    class GameObject;

    class SR_DLL_EXPORT Component : public Entity {
        friend class GameObject;
        friend class IComponentable;
        friend class ComponentManager;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Component>;
        using ScenePtr = SR_WORLD_NS::Scene*;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
    public:
        ~Component() override;

    public:
        virtual void OnMatrixDirty() { }
        virtual void OnTransformSet() { }

        /// Вызывается при загрузке компонента на игровой объект
        virtual void OnLoaded() { m_isComponentLoaded = true; }
        /// Вызывается после добавления компонента к игровому объекту
        virtual void OnAttached() { m_isAttached = true; }
        /// Вызывается кода компонент убирается с объекта, либо объект уничтожается
        virtual void OnDestroy() { SetParent(nullptr); }

        virtual void OnEnable() { m_isActive = true; }
        virtual void OnDisable() { m_isActive = false; }

        virtual void Awake() { m_isAwake = true; }
        virtual void Start() { m_isStarted = true; }
        virtual void Update(float_t dt) { }
        virtual void FixedUpdate() { }
        virtual void LateUpdate() { }

        virtual void OnCollisionEnter(const CollisionData& data) { }
        virtual void OnCollisionStay(const CollisionData& data) { }
        virtual void OnCollisionExit(const CollisionData& data) { }

        virtual void OnTriggerEnter(const CollisionData& data) { }
        virtual void OnTriggerStay(const CollisionData& data) { }
        virtual void OnTriggerExit(const CollisionData& data) { }

    public:
        void CheckActivity();

        void SetEnabled(bool value);
        void SetComponentBuildId(uint64_t buildId) { m_componentBuildId = buildId; }

        SR_NODISCARD virtual Component* CopyComponent() const;

        SR_NODISCARD virtual uint64_t GetComponentHashName() const = 0;
        SR_NODISCARD virtual const std::string& GetComponentName() const = 0;

        SR_NODISCARD SR_FORCE_INLINE virtual bool IsComponentLoaded() const noexcept { return m_isComponentLoaded; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsAttached() const noexcept { return m_isAttached; }

        /// Активен и компонент и его родительский объект
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsCanUpdate() const noexcept { return m_isStarted && m_isActive; }
        /// Активен и компонент и его родительский объект
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsActive() const noexcept { return m_isActive; }
        /// Активен сам компонент, независимо от объекта
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsEnabled() const noexcept { return m_isEnabled; }

        SR_NODISCARD SR_FORCE_INLINE virtual bool IsAwake() const noexcept { return m_isAwake; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsStarted() const noexcept { return m_isStarted; }

        SR_NODISCARD SR_FORCE_INLINE virtual bool ExecuteInEditMode() const { return false; }
        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const { return SR_MATH_NS::InfinityFV3; }
        SR_NODISCARD Component* BaseComponent() { return this; }
        SR_NODISCARD IComponentable* GetParent() const;
        SR_NODISCARD ScenePtr GetScene() const;
        SR_NODISCARD bool HasScene() const { return TryGetScene(); }
        SR_NODISCARD GameObjectPtr GetGameObject() const;
        SR_NODISCARD ScenePtr TryGetScene() const;
        SR_NODISCARD GameObjectPtr GetRoot() const;
        SR_NODISCARD Transform* GetTransform() const noexcept;
        SR_NODISCARD uint64_t GetComponentBuildId() const noexcept { return m_componentBuildId; }

        SR_NODISCARD std::string GetEntityInfo() const override;

    protected:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const override;

        void SetParent(IComponentable* pParent);

    protected:
        bool m_isComponentLoaded = false;
        bool m_isAttached = false;
        bool m_isEnabled = true;
        bool m_isActive = false;
        bool m_isAwake = false;
        bool m_isStarted = false;

        /// позиция компонента в списке обновляемых компонентов
        uint64_t m_componentBuildId = SR_ID_INVALID;

        IComponentable* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
