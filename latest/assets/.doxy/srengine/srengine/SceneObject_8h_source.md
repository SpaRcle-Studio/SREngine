

# File SceneObject.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**SceneObject.h**](SceneObject_8h.md)

[Go to the documentation of this file](SceneObject_8h.md)


```C++
//
// Created by Monika on 04.10.2024.
//

#ifndef SR_ENGINE_UTILS_SCENE_OBJECT_H
#define SR_ENGINE_UTILS_SCENE_OBJECT_H

#include <Utils/ECS/EntityController.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/ECS/IComponentable.h>

namespace SR_UTILS_NS::World {
    class Scene;
}

namespace SR_UTILS_NS {
    class Prefab;

    SR_ENUM_NS_CLASS_T(SceneObjectType, int16_t,
        Invalid = -1,
        GameObject = 0
    )

    
    class SceneObject : public IComponentable {
        SR_CLASS()
        using Super = IComponentable;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<SceneObject>;
        using ScenePtr = SR_WORLD_NS::Scene*;
        using ObjectNameT = SR_UTILS_NS::StringAtom;
        using ChildrenType = std::vector<SceneObject::Ptr>;
        using OriginType = SceneObject;

    public:
        SceneObject();
        ~SceneObject() override;

    public:
        SR_NODISCARD SR_FORCE_INLINE StringAtom GetName() const { return m_name; }
        SR_NODISCARD SR_FORCE_INLINE bool IsEnabled() const noexcept { return m_isEnabled; }
        SR_NODISCARD SR_FORCE_INLINE uint64_t GetIdInScene() const noexcept { return m_idInScene; }

        SR_NODISCARD SR_FORCE_INLINE ScenePtr GetScene() const override { return m_scene; }
        SR_NODISCARD SR_FORCE_INLINE StringAtom GetLayer() const noexcept { return m_cachedLayer; }
        SR_NODISCARD SR_FORCE_INLINE StringAtom GetLocalLayer() const noexcept { return m_layer; }

        SR_NODISCARD SR_FORCE_INLINE Prefab* GetPrefab() const noexcept { return m_prefabInfo.pPrefab; }
        SR_NODISCARD SR_FORCE_INLINE bool IsPrefabOwner() const noexcept { return m_prefabInfo.isOwner; }

        SR_NODISCARD SR_FORCE_INLINE SceneObject::Ptr GetParent() const noexcept { return m_parent; }
        SR_NODISCARD SR_FORCE_INLINE SceneObject::Ptr GetRoot() const noexcept { return m_root; }

        SR_NODISCARD SR_FORCE_INLINE bool HasChildren() const { return !m_children.empty(); }
        SR_NODISCARD SR_FORCE_INLINE ChildrenType& GetChildrenRef() { return m_children; }
        SR_NODISCARD SR_FORCE_INLINE const ChildrenType& GetChildrenRef() const { return m_children; }
        SR_NODISCARD SR_FORCE_INLINE ChildrenType GetChildren() const { return m_children; }
        SR_NODISCARD SR_FORCE_INLINE bool IsDestroyed() const noexcept override { return m_isDestroyed; }
        SR_NODISCARD SR_FORCE_INLINE bool IsActive() const noexcept override { return m_isActive && !m_isDestroyed; }

        SR_NODISCARD SceneObject::Ptr Find(uint64_t hashName) const noexcept;
        SR_NODISCARD SceneObject::Ptr Find(const std::string& name) const noexcept;
        SR_NODISCARD SceneObject::Ptr Find(const std::string_view& name) const noexcept;
        SR_NODISCARD SceneObject::Ptr Find(StringAtom name) const noexcept;

        SR_NODISCARD Path GetPrefabPath() const;
        SR_NODISCARD StringAtom GetTag() const;
        SR_NODISCARD SR_UTILS_NS::EntityIdList GetEntityIdList() const;
        SR_NODISCARD bool IsPrefabLoadingState() const noexcept final { return m_isPrefabLoadingState; }

        SR_NODISCARD SceneObject::Ptr CloneSceneObject() const;
        SR_NODISCARD bool IsPrefab() const noexcept override { return m_prefabInfo.pPrefab; }

        SR_NODISCARD virtual SceneObjectType GetSceneObjectType() const noexcept = 0;

        bool Load(IDeserializer& deserializer) override;

        bool MoveToTree(const SceneObject::Ptr& destination);
        void RemoveChild(const SceneObject::Ptr& pChild);
        bool AddChild(const SceneObject::Ptr& pChild);
        void ForEachChild(const std::function<void(SceneObject::Ptr&)>& fn);
        void ForEachChild(const std::function<void(const SceneObject::Ptr&)>& fn) const;
        bool SetParent(const SceneObject::Ptr& parent);
        void SetName(ObjectNameT name);
        void SetTag(SR_UTILS_NS::StringAtom tag);
        bool Contains(const SceneObject::Ptr& pChild);
        void SetEnabled(bool value);
        void SetLayer(StringAtom layer);
        void SetIdInScene(uint64_t id);
        void SetScene(ScenePtr pScene);
        void SetPrefab(Prefab* pPrefab, bool isOwner);

        void UnlinkPrefab();
        void RemoveChildren();
        void DestroyChildren();

        void VerifyAfterLoad(SerializableVerifyContext& context) const noexcept override;

        bool PostLoad(bool force) override;
        void Awake(bool force, bool isPaused) noexcept override;
        void Start(bool force) noexcept override;
        void CheckActivity(bool force) noexcept override;
        bool SetDirty(bool value) override;

        void Destroy();

        void DestroyImpl();

        void OnPostLoad() override;

    protected:
        virtual void OnHierarchyChanged() { }
        void UpdateRoot();

    private:
        virtual void OnAttached() { }
        void OnParentLayerChanged();

    private:
        struct PrefabInfo {
            Prefab* pPrefab = nullptr;
            bool isOwner = false;
        } m_prefabInfo;

        SceneObject::Ptr m_root;
        SceneObject::Ptr m_parent;

        bool m_isActive = false;
        bool m_isDestroyed = false;
        bool m_isPrefabLoadingState = false;

        StringAtom m_cachedLayer;

        ScenePtr m_scene = nullptr;
        SRHashType m_idInScene = SR_ID_INVALID;

    private:
        SR_UTILS_NS::StringAtom m_tag;
        SR_UTILS_NS::StringAtom m_name;
        std::vector<SceneObject::Ptr> m_children;
        bool m_isEnabled = true;
        StringAtom m_layer = LayerManager::GetDefaultLayer();

        SR_VIRTUAL_PROPERTY;

    };
}

#endif //SR_ENGINE_UTILS_SCENE_OBJECT_H
```


