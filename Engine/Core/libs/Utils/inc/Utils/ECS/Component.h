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
#include <Utils/TypeTraits/Properties.h>

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
        virtual void OnPriorityDirty() { }
        virtual void OnTransformSet() { }

        /// Вызывается при загрузке компонента на игровой объект
        virtual void OnLoaded() { m_isComponentLoaded = true; }
        /// Вызывается после добавления компонента к игровому объекту
        virtual void OnAttached() { m_isAttached = true; SRAssert(GetParent()); }
        /// Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached
        virtual void OnDetached();
        /// Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно.
        virtual void OnDestroy() { SetParent(nullptr); }

        virtual void OnEnable();
        virtual void OnDisable();

        virtual void Awake() { m_isAwake = true; }
        virtual void Start();
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

        void Detach();

        void SetEnabled(bool value);
        void SetIndexIdSceneUpdater(int32_t index) { m_indexInSceneUpdater = index; }

        SR_NODISCARD virtual Component* CopyComponent() const;

        SR_NODISCARD virtual uint64_t GetComponentHashName() const = 0;
        SR_NODISCARD virtual const std::string& GetComponentName() const = 0;

        SR_NODISCARD SR_FORCE_INLINE virtual bool IsComponentLoaded() const noexcept { return m_isComponentLoaded; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsComponentValid() const noexcept { return m_parent; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsAttached() const noexcept { return m_isAttached; }

        /// Активен и компонент и его родительский объект
        SR_NODISCARD virtual bool IsUpdatable() const noexcept;
        /// Активен и компонент и его родительский объект
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsActive() const noexcept { return m_isActive; }
        /// Активен сам компонент, независимо от объекта
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsEnabled() const noexcept { return m_isEnabled; }

        SR_NODISCARD SR_FORCE_INLINE virtual bool IsAwake() const noexcept { return m_isAwake; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsStarted() const noexcept { return m_isStarted; }

        /// Запущена ли сцена
        SR_NODISCARD bool IsPlayingMode() const;
        /// На паузе ли сцена (если запущена)
        SR_NODISCARD bool IsPausedMode() const;

        SR_NODISCARD SR_FORCE_INLINE virtual bool ExecuteInEditMode() const { return false; }
        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const { return SR_MATH_NS::InfinityFV3; }
        SR_NODISCARD Component* BaseComponent() { return this; }
        SR_NODISCARD IComponentable* GetParent() const;
        SR_NODISCARD ScenePtr GetScene() const;
        SR_NODISCARD bool HasScene() const { return TryGetScene(); }
        SR_NODISCARD GameObjectPtr GetGameObject() const;
        SR_NODISCARD bool HasParent() const { return m_parent; }
        SR_NODISCARD ScenePtr TryGetScene() const;
        SR_NODISCARD GameObjectPtr GetRoot() const;
        SR_NODISCARD Transform* GetTransform() const noexcept;
        SR_NODISCARD SR_UTILS_NS::PropertyContainer& GetComponentProperties() noexcept { return m_properties; }
        SR_NODISCARD const SR_UTILS_NS::PropertyContainer& GetComponentProperties() const noexcept { return m_properties; }
        SR_NODISCARD int32_t GetIndexInSceneUpdater() const noexcept { return m_indexInSceneUpdater; }

        SR_NODISCARD std::string GetEntityInfo() const override;

    protected:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SavableSaveData data) const override;

        void SetParent(IComponentable* pParent);

    protected:
        bool m_isComponentLoaded = false;
        bool m_isAttached = false;
        bool m_isEnabled = true;
        bool m_isActive = false;
        bool m_isAwake = false;
        bool m_isStarted = false;

        int32_t m_indexInSceneUpdater = SR_ID_INVALID;

        GameObjectPtr m_gameObject;
        IComponentable* m_parent = nullptr;
        SR_WORLD_NS::Scene* m_scene = nullptr;

        SR_UTILS_NS::PropertyContainer m_properties;

    };
}


#endif //GAMEENGINE_COMPONENT_H
