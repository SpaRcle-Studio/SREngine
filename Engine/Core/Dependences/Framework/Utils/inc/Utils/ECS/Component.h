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
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/Marshal.h>
#include <Utils/Types/SafeVariable.h>
#include <Utils/World/Scene.h>

/**
 * Awake -> OnEnabled -> Start -> Update -> FixedUpdate
 */

namespace SR_HTYPES_NS {
    class DataStorage;
}

namespace SR_UTILS_NS {
    class ComponentManager;
    class Component;
    class Transform2D;
    class Transform3D;
    class Transform;
    class GameObject;

    class SR_DLL_EXPORT Component : public Entity {
        friend class GameObject;
        friend class ComponentManager;
    public:
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
    public:
        ~Component() override = default;

    public:
        virtual void OnMatrixDirty() { }

        /// Вызывается после добавления компонента к игровому объекту
        virtual void OnAttached() { }
        /// Вызывается кода компонент убирается с объекта, либо объект уничтожается
        virtual void OnDestroy() { }

        virtual void OnEnable() { m_isActive = true; }
        virtual void OnDisable() { m_isActive = false; }

        virtual void Awake() { m_isAwake = true; }
        virtual void Start() { m_isStarted = true; }
        virtual void Update(float_t dt) { }
        virtual void FixedUpdate() { }
        virtual void LateUpdate() { }

    public:
        void CheckActivity();

        void SetEnabled(bool value);

        /// Активен и компонент и его родительский объект
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsCanUpdate() const noexcept { return m_isStarted && m_isActive; }
        /// Активен и компонент и его родительский объект
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsActive() const noexcept { return m_isActive; }
        /// Активен сам компонент, независимо от объекта
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsEnabled() const noexcept { return m_isEnabled; }

        SR_NODISCARD SR_FORCE_INLINE virtual bool IsAwake() const noexcept { return m_isAwake; }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsStarted() const noexcept { return m_isStarted; }

        SR_NODISCARD SR_FORCE_INLINE virtual bool ExecuteInEditMode() const { return false; }
        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        SR_NODISCARD SR_INLINE std::string GetComponentName() const { return m_name; }
        SR_NODISCARD SR_INLINE size_t GetComponentId() const { return m_componentId; }
        SR_NODISCARD SR_INLINE Component* BaseComponent() { return this; }
        SR_NODISCARD SR_INLINE GameObject* GetParent() const;
        SR_NODISCARD SR_WORLD_NS::Scene::Ptr GetScene() const;
        SR_NODISCARD SR_WORLD_NS::Scene::Ptr TryGetScene() const;
        SR_NODISCARD GameObjectPtr GetRoot() const;
        SR_NODISCARD Transform* GetTransform() const noexcept;

    protected:
        template<typename T> void InitComponent() {
            m_componentId = typeid(T).hash_code();
            ///TODO: Это может быть медленным, стоит завести в каждом компоненте констунту COMPONENT_NAME
            m_name = StringUtils::BackRead(typeid(T).name(), ':');
        }

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const override;

    private:
        void SetParent(GameObject* parent);

    protected:
        bool m_isEnabled = true;
        bool m_isActive = false;
        bool m_isAwake = false;
        bool m_isStarted = false;

        /// TODO: need remove for optimization, use numeric id
        std::string m_name = "Unknown";

        uint64_t m_componentId = SIZE_MAX;
        GameObject* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
