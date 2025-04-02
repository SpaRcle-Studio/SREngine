

# File EntityRef.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**EntityRef.h**](EntityRef_8h.md)

[Go to the documentation of this file](EntityRef_8h.md)


```C++
//
// Created by Monika on 26.11.2022.
//

#ifndef SR_ENGINE_UTILS_ENTITY_REF_H
#define SR_ENGINE_UTILS_ENTITY_REF_H

#include <Utils/ECS/EntityRefUtils.h>
#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    class GameObject;
    class SceneObject;
    class Component;

    class EntityRef final : public SR_UTILS_NS::Serializable {
        SR_CLASS()
    public:
        EntityRef() = default;
        explicit EntityRef(EntityRefUtils::OwnerRef owner);

    public:
        void OnPreSave() override;

        SR_NODISCARD EntityRef Copy(const EntityRefUtils::OwnerRef& owner) const;
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<Entity>& GetTarget() const { return m_target; }

        template<typename T> SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> GetComponent() const {
            if (auto&& pComponent = GetComponent()) {
                return pComponent.DynamicCast<T>();
            }
            return nullptr;
        }

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<GameObject> GetGameObject() const;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<SceneObject> GetSceneObject() const;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Component> GetComponent() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD bool IsRelative() const { return m_relative; }

        void SetRelative(bool relative);
        EntityRef& SetPathTo(const SR_HTYPES_NS::SharedPtr<Entity>& pEntity);
        void SetOwner(const EntityRefUtils::OwnerRef& owner);

        void UpdateTarget() const;

    private:
        void UpdatePath() const;

    private:
        mutable SR_UTILS_NS::EntityRefUtils::RefPath m_path;
        bool m_relative = true;

        EntityRefUtils::OwnerRef m_owner;
        mutable SR_HTYPES_NS::SharedPtr<Entity> m_target;

    };

    class EntityRefProperty : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(EntityRefProperty, 1001)
    public:
        //void SaveProperty(MarshalRef marshal) const noexcept override;
        //void LoadProperty(MarshalRef marshal) noexcept override;

        SR_UTILS_NS::EntityRef& GetEntityRef() noexcept { return m_entityRef; }

    private:
        SR_UTILS_NS::EntityRef m_entityRef;

    };
}

#endif //SR_ENGINE_UTILS_ENTITY_REF_H
```


