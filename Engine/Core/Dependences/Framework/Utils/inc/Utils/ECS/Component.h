//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <Utils/ECS/EntityManager.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Marshal.h>

/**
 *  Component adding if enabled:
 *      Reset() -> OnEnabled()
 *
 *  Component adding if disabled: nothing
 *
 *  Component removing if enabled:
 *      OnDisabled() -> OnDestroy()
 *
 *  Component removing if disabled and started:
 *      OnDestroy()
 */

namespace SR_HTYPES_NS {
    class DataStorage;
}

namespace SR_UTILS_NS {
    class Component;
    class GameObject;

    class SR_DLL_EXPORT Component : public Entity {
        friend class GameObject;
    public:
        ~Component() override = default;

    public:
        virtual void OnRotate(const Math::FVector3& newValue) { }
        virtual void OnMove(const Math::FVector3& newValue) { }
        virtual void OnScaled(const Math::FVector3& newValue) { }
        virtual void OnSkewed(const Math::FVector3& newValue) { }

        /// Вызывается когда компонент добавляется на объект
        virtual void Reset() { }
        /// Вызывается кода компонент убирается с объекта, либо объект уничтожается
        virtual void OnDestroy() { }

        virtual void OnEnabled() { }
        virtual void OnDisabled() { }

        virtual void Awake() { }
        virtual void Start() { }
        virtual void Update() { }
        virtual void FixedUpdate() { }
        virtual void LateUpdate() { }
        virtual void OnGUI() { }

    public:
        void SetEnabled(bool value);
        void SetParent(GameObject* parent);

    public:
        /// Активен и компонент и его родительский объект
        SR_NODISCARD bool IsActive() const noexcept;
        /// Активен сам компонент, независимо от объекта
        SR_NODISCARD SR_INLINE bool IsEnabled() const noexcept { return m_isEnabled; }

        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        SR_NODISCARD SR_INLINE std::string GetComponentName() const { return m_name; }
        SR_NODISCARD SR_INLINE size_t GetComponentId() const { return m_componentId; }
        SR_NODISCARD SR_INLINE Component* BaseComponent() { return this; }
        SR_NODISCARD SR_INLINE GameObject* GetParent() const { return m_parent; }

    protected:
        template<typename T> void InitComponent() {
            m_componentId = typeid(T).hash_code();
            m_name = StringUtils::BackRead(typeid(T).name(), ':');
        }

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SavableFlags flags) const override;

    private:
        void CheckActivity();

    protected:
        std::atomic<bool> m_isEnabled = true;
        std::atomic<bool> m_isActive = false;

        /// TODO: need remove for optimization, use numeric id
        std::string m_name = "Unknown";

        uint64_t m_componentId = SIZE_MAX;
        GameObject* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
