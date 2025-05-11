

# File EngineCommands.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**EngineCommands.h**](EngineCommands_8h.md)

[Go to the documentation of this file](EngineCommands_8h.md)


```C++
//
// Created by Monika on 08.01.2022.
//

#ifndef SR_ENGINE_ENGINECOMMANDS_H
#define SR_ENGINE_ENGINECOMMANDS_H

#include <Engine/Engine.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/CommandManager/CmdManager.h>
#include <Utils/ECS/EntityController.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

namespace SR_UTILS_NS {
    class GameObject;
    class SceneObject;

    namespace World {
        class Scene;
    }
}

namespace SR_CORE_GUI_NS {
    class Hierarchy;
}

namespace SR_CORE_NS::Commands {
    SR_MAYBE_UNUSED SR_NODISCARD static std::unique_ptr<SR_UTILS_NS::ISerializer> CreateSerializer() {
        auto&& pSerializer = std::make_unique<SR_UTILS_NS::SRASerializer>();
        pSerializer->SetWriteDefaults(true);
        return pSerializer;
    }

    class IEngineReversibleCommand : public SR_UTILS_NS::ReversibleCommand {
    public:
        using EnginePtr = SR_HTYPES_NS::SharedPtr<Engine>;
    public:
        explicit IEngineReversibleCommand(EnginePtr pEngine)
            : m_engine(std::move(pEngine))
            , m_scene(m_engine->GetScene())
        { }

    protected:
        SR_HTYPES_NS::SharedPtr<Engine> m_engine;
        SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> m_scene;

    };


    class ChangeHierarchySelected : public IEngineReversibleCommand {
        using Selection = std::set<SR_UTILS_NS::SceneObject::Ptr>;
        using Super = IEngineReversibleCommand;
    public:
        ChangeHierarchySelected(const EnginePtr& pEngine, SR_CORE_GUI_NS::Hierarchy* pHierarchy, const Selection& oldSelected, const Selection& newSelected);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_CORE_NS::GUI::Hierarchy* m_hierarchy = nullptr;
        std::set<SR_UTILS_NS::EntityId> m_newSelected;
        std::set<SR_UTILS_NS::EntityId> m_oldSelected;

    };


    class GameObjectTransform : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        GameObjectTransform(const EnginePtr& pEngine, const SR_UTILS_NS::GameObject::Ptr& pGameObject, SR_UTILS_NS::ISerializer::UniquePtr pOld, SR_UTILS_NS::ISerializer::UniquePtr pNew = nullptr)
            : Super(pEngine)
            , m_entityId(pGameObject->GetEntityId())
            , m_pOld(std::move(pOld))
            , m_pNew(std::move(pNew))
        {
            if (!m_pNew) {
                m_pNew = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_pNew, pGameObject->GetTransform(), DATA_ID);
            }
        }

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::ISerializer::UniquePtr m_pNew;
        SR_UTILS_NS::ISerializer::UniquePtr m_pOld;

    };


    class ComponentsChange : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        ComponentsChange(const EnginePtr& pEngine, const SR_UTILS_NS::IComponentable::Ptr& pComponentable, SR_UTILS_NS::ISerializer::UniquePtr pOld)
            : Super(pEngine)
            , m_entityId(pComponentable->GetEntityId())
            , m_pOld(std::move(pOld))
        {
            m_pNew = SR_CORE_NS::Commands::CreateSerializer();
            SR_UTILS_NS::Serialization::Save(*m_pNew, pComponentable->GetComponents(), DATA_ID);
        }

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::ISerializer::UniquePtr m_pNew;
        SR_UTILS_NS::ISerializer::UniquePtr m_pOld;

    };


    class ComponentChange : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        ComponentChange(const EnginePtr& pEngine, const SR_UTILS_NS::Component::Ptr& pComponent, SR_UTILS_NS::ISerializer::UniquePtr pOld)
            : Super(pEngine)
            , m_entityId(pComponent->GetEntityId())
            , m_pOld(std::move(pOld))
        {
            m_pNew = SR_CORE_NS::Commands::CreateSerializer();
            SR_UTILS_NS::Serialization::Save(*m_pNew, *pComponent, DATA_ID);
        }

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::ISerializer::UniquePtr m_pNew;
        SR_UTILS_NS::ISerializer::UniquePtr m_pOld;

    };


    class SceneObjectRename : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        SceneObjectRename(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::SceneObject::ObjectNameT newName);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::GameObject::ObjectNameT m_previousName;
        SR_UTILS_NS::GameObject::ObjectNameT m_newName;

    };


    class SceneObjectTag : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        SceneObjectTag(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::StringAtom newTag);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::StringAtom m_previousTag;
        SR_UTILS_NS::StringAtom m_newTag;

    };


    class SceneObjectLayer : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        SceneObjectLayer(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::StringAtom newLayer);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::StringAtom m_previousLayer;
        SR_UTILS_NS::StringAtom m_newLayer;

    };


    class EntityEnable : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        EntityEnable(const EnginePtr& pEngine, const SR_UTILS_NS::Entity::Ptr& pEntity, bool newEnabled);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        bool m_newEnabled = false;
        bool m_previousEnabled = false;

    };


    class SceneObjectDelete : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        SceneObjectDelete(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO);
        ~SceneObjectDelete() override;

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::EntityId m_parentEntityId = SR_ID_INVALID;
        SR_UTILS_NS::EntityIdList::Optional m_reserved;
        SR_UTILS_NS::ISerializer::UniquePtr m_pBackup;

    };


    class SceneObjectInstance : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        SceneObjectInstance(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO);
        ~SceneObjectInstance() override;

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::EntityId m_parentEntityId = SR_ID_INVALID;
        SR_UTILS_NS::EntityIdList::Optional m_reserved;
        SR_UTILS_NS::ISerializer::UniquePtr m_pBackup;

    };


    class GameObjectMove : public IEngineReversibleCommand {
        using Super = IEngineReversibleCommand;
    public:
        GameObjectMove(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::EntityId newParentId);

        bool Redo() override;
        bool Undo() override;

    private:
        SR_UTILS_NS::EntityId m_entityId = SR_ID_INVALID;
        SR_UTILS_NS::EntityId m_newParentId = SR_ID_INVALID;
        SR_UTILS_NS::EntityId m_previousParentId = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_ENGINECOMMANDS_H
```


