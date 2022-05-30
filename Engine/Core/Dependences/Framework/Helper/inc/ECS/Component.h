//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <ECS/EntityManager.h>
#include <Math/Vector3.h>
#include <Types/SafePointer.h>
#include <Utils/Singleton.h>
#include <Utils/NonCopyable.h>
#include <Utils/StringUtils.h>
#include <Types/DataStorage.h>

namespace SR_UTILS_NS {
    class Component;
    class GameObject;

    class Component : public Entity {
        friend class GameObject;
    public:
        ~Component() override = default;

    public:
        virtual void OnRotate(const Math::FVector3& newValue) { }
        virtual void OnMove(const Math::FVector3& newValue) { }
        virtual void OnScaled(const Math::FVector3& newValue) { }
        virtual void OnSkewed(const Math::FVector3& newValue) { }

        virtual void OnEnabled() { }
        virtual void OnDisabled() { }
        virtual void OnDestroy() { }

    public:
        void SetEnabled(bool value) { m_isEnabled = value; }
        void SetParent(GameObject* parent) { m_parent = parent; }

    public:
        /// Активен и компонент и его родительский объект
        SR_NODISCARD bool IsActive() const;
        /// Активен сам компонент, независимо от объекта
        SR_NODISCARD SR_INLINE bool IsEnabled() const { return m_isEnabled; }

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

    protected:
        std::atomic<bool> m_isEnabled = true;
        std::string m_name = "Unknown";
        uint64_t m_componentId = SIZE_MAX;
        GameObject* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
