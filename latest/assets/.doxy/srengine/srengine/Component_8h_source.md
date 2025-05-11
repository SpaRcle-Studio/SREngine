

# File Component.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**Component.h**](Component_8h.md)

[Go to the documentation of this file](Component_8h.md)


```C++
//
// Created by Nikita on 27.11.2020.
//

#ifndef SR_ENGINE_UTILS_COMPONENT_H
#define SR_ENGINE_UTILS_COMPONENT_H

#include <Utils/ECS/Entity.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/Marshal.h>
#include <Utils/Types/SafeVariable.h>
#include <Utils/Common/CollisionData.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_HTYPES_NS {
    class DataStorage;
}

#define SR_INITIALIZE_COMPONENT(name)                                                                                   \
public:                                                                                                                 \
    SR_INLINE static const SR_UTILS_NS::StringAtom COMPONENT_NAME = #name;                                 \
    SR_NODISCARD const SR_UTILS_NS::StringAtom& GetComponentName() const override { return name::COMPONENT_NAME; }      \
private:                                                                                                                \

namespace SR_UTILS_NS {
    class ComponentManager;
    class Component;
    class IComponentable;
    class Transform2D;
    class Transform3D;
    class Transform;
    class GameObject;

    class SR_COMMON_DLL_API Component : public Entity {
        SR_CLASS()
        friend class GameObject;
        friend class IComponentable;
        friend class ComponentManager;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Component>;
        using OriginType = Component;
        using ScenePtr = SR_WORLD_NS::Scene*;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using SceneObjectPtr = SR_HTYPES_NS::SharedPtr<SceneObject>;
    public:
        Component();
        ~Component() override;

    public:
        virtual void OnMatrixDirty();
        virtual void OnPriorityChanged();
        virtual void OnTransformSet();

        virtual void OnLoaded();
        virtual void OnAttached();
        virtual void OnDetached();
        virtual void OnDestroy();

        virtual void OnEnable();
        virtual void OnDisable();

        virtual void Awake();
        virtual void Start();
        virtual void Update(float_t dt);
        virtual void FixedUpdate();
        virtual void LateUpdate();

        virtual void OnBeforeLayerChanged();
        virtual void OnLayerChanged();

        virtual void OnCollisionEnter(const CollisionData& data);
        virtual void OnCollisionStay(const CollisionData& data);
        virtual void OnCollisionExit(const CollisionData& data);

        virtual void OnTriggerEnter(const CollisionData& data);
        virtual void OnTriggerStay(const CollisionData& data);
        virtual void OnTriggerExit(const CollisionData& data);

    public:
        void CheckActivity();

        void Detach();

        void SetEnabled(bool value);
        void SetIndexIdSceneUpdater(int32_t index);

        SR_NODISCARD virtual bool IsComponentLoaded() const noexcept;
        SR_NODISCARD virtual bool IsComponentValid() const noexcept;
        SR_NODISCARD virtual bool IsAttached() const noexcept;

        SR_NODISCARD virtual bool IsUpdatable() const noexcept;
        SR_NODISCARD virtual bool IsActive() const noexcept;
        SR_NODISCARD virtual bool IsEnabled() const noexcept;

        SR_NODISCARD virtual bool IsAwake() const noexcept;
        SR_NODISCARD virtual bool IsStarted() const noexcept;

        SR_NODISCARD bool IsPlayingMode() const;
        SR_NODISCARD bool IsPausedMode() const;

        SR_NODISCARD virtual bool ExecuteInEditMode() const;
        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const;
        SR_NODISCARD Component* BaseComponent() noexcept;
        SR_NODISCARD IComponentable* GetParent() const;
        SR_NODISCARD IComponentable* TryGetParent() const;
        SR_NODISCARD ScenePtr GetScene() const;
        SR_NODISCARD bool HasScene() const;
        SR_NODISCARD GameObjectPtr GetGameObject() const;
        SR_NODISCARD SceneObjectPtr GetSceneObject() const;
        SR_NODISCARD ScenePtr TryGetScene() const;
        SR_NODISCARD SceneObjectPtr GetRoot() const;
        SR_NODISCARD Transform* GetTransform() const noexcept;
        SR_NODISCARD int32_t GetIndexInSceneUpdater() const noexcept;
        SR_NODISCARD bool HasParent() const;

        SR_NODISCARD Component::Ptr CloneComponent() const;

    protected:
        void SetParent(IComponentable* pParent);

    protected:
        bool m_isComponentLoaded = false;
        bool m_isAttached = false;
        bool m_isActive = false;
        bool m_isAwake = false;
        bool m_isStarted = false;

        bool m_isEnabled = true;

        int32_t m_indexInSceneUpdater = SR_ID_INVALID;

        SceneObjectPtr m_sceneObject = nullptr;
        IComponentable* m_parent = nullptr;
        SR_WORLD_NS::Scene* m_scene = nullptr;

    };
}


#endif //SR_ENGINE_UTILS_COMPONENT_H
```


