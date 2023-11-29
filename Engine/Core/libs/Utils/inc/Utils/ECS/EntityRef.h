//
// Created by Monika on 26.11.2022.
//

#ifndef SR_ENGINE_UTILS_ENTITY_REF_H
#define SR_ENGINE_UTILS_ENTITY_REF_H

#include <Utils/ECS/EntityRefUtils.h>
#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Component;

    class EntityRef final : public SR_UTILS_NS::NonCopyable {
    public:
        EntityRef() = default;
        explicit EntityRef(const EntityRefUtils::OwnerRef& owner);

        EntityRef(EntityRef&& other) noexcept;

        EntityRef& operator=(EntityRef&& other) noexcept;

    public:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal) const;
        SR_NODISCARD EntityRef Copy(const EntityRefUtils::OwnerRef& owner) const;
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<Entity>& GetTarget() const { return m_target; }

        void Save(SR_HTYPES_NS::Marshal& marshal) const;
        void Load(SR_HTYPES_NS::Marshal& marshal);

        template<typename T> SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> GetComponent() const {
            if (auto&& pComponent = GetComponent()) {
                return pComponent.DynamicCast<T>();
            }
            return nullptr;
        }

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<GameObject> GetGameObject() const;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Component> GetComponent() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD bool IsRelative() const { return m_relative; }

        void SetRelative(bool relative);
        EntityRef& SetPathTo(SR_HTYPES_NS::SharedPtr<Entity> pEntity);
        void SetOwner(const EntityRefUtils::OwnerRef& owner);

    private:
        void UpdateTarget() const;
        void UpdatePath() const;

    private:
        mutable SR_UTILS_NS::EntityRefUtils::RefPath m_path;

        bool m_relative = true;

        EntityRefUtils::OwnerRef m_owner;
        mutable SR_HTYPES_NS::SharedPtr<Entity> m_target;

    };

    class EntityRefProperty : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(EntityRefProperty, 1000)
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        SR_UTILS_NS::EntityRef& GetEntityRef() noexcept { return m_entityRef; }

    private:
        SR_UTILS_NS::EntityRef m_entityRef;

    };
}

#endif //SR_ENGINE_UTILS_ENTITY_REF_H
