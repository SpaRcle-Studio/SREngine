//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENGINECOMMANDS_H
#define SRENGINE_ENGINECOMMANDS_H

#include <Utils/Types/SafePointer.h>
#include <Utils/CommandManager/CmdManager.h>
#include <Utils/ECS/EntityManager.h>
#include <Utils/ECS/GameObject.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Core/GUI/Hierarchy.h>

namespace SR_UTILS_NS {
    class GameObject;

    namespace World {
        class Scene;
    }
}

namespace SR_CORE_NS::Commands {

    class HierarchyClearSelected : public SR_UTILS_NS::ReversibleCommand {
    public:
        HierarchyClearSelected() = default;
        explicit HierarchyClearSelected(std::set<SR_UTILS_NS::GameObject::Ptr>* pSelected);

        ~HierarchyClearSelected() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "HierarchyClearSelected"; }

    private:
        std::set<SR_UTILS_NS::GameObject::Ptr>* m_selected;
        std::set<SR_UTILS_NS::GameObject::Ptr> m_oldSelected;
    };

    class SelectGameObject : public SR_UTILS_NS::ReversibleCommand {
    public:
        SelectGameObject() = default;
        explicit SelectGameObject(const SR_UTILS_NS::GameObject::Ptr& pMesh,
                                    std::set<SR_UTILS_NS::GameObject::Ptr>* pSelected,
                                    bool shiftPressed);

        ~SelectGameObject() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "SelectGameObject"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        std::set<SR_UTILS_NS::GameObject::Ptr>* m_selected;
        std::set<SR_UTILS_NS::GameObject::Ptr> m_oldSelected;
        bool m_shiftPressed = false;
    };

    class GameObjectTransform : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectTransform() = default;
        explicit GameObjectTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, SR_HTYPES_NS::Marshal::Ptr pOldMarshal);

        ~GameObjectTransform() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectTransform"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_HTYPES_NS::Marshal::Ptr m_newMarshal = nullptr;
        SR_HTYPES_NS::Marshal::Ptr m_oldMarshal = nullptr;
    };
    
    class GameObjectEnable : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectEnable() = default;
        explicit GameObjectEnable(const SR_UTILS_NS::GameObject::Ptr& ptr, bool newEnabled);

        ~GameObjectEnable() override = default;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectEnable"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        bool m_newEnabled = false;
        bool m_previousEnabled = false;
    };
    
    class GameObjectRename : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectRename() = default;
        explicit GameObjectRename(const SR_UTILS_NS::GameObject::Ptr& ptr, SR_UTILS_NS::GameObject::Name newName);

        ~GameObjectRename() override = default;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectRename"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_UTILS_NS::GameObject::Name m_previousName;
        SR_UTILS_NS::GameObject::Name m_newName;
    };

    class GameObjectDelete : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectDelete() = default;
        explicit GameObjectDelete(const SR_UTILS_NS::GameObject::Ptr& ptr);

        ~GameObjectDelete() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectDelete"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_UTILS_NS::EntityBranch m_reserved;
        SR_HTYPES_NS::Marshal::Ptr m_backup = nullptr;
        SR_HTYPES_NS::SafePtr<Helper::World::Scene> m_scene;
        SR_UTILS_NS::EntityId m_parent = { };
    };

    bool RegisterEngineCommands();

    class GameObjectPaste : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectPaste() = default;
        explicit GameObjectPaste(const SR_UTILS_NS::GameObject::Ptr& ptr);

        ~GameObjectPaste() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectDelete"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_UTILS_NS::EntityBranch m_reserved;
        SR_HTYPES_NS::Marshal::Ptr m_backup = nullptr;
        SR_HTYPES_NS::SafePtr<Helper::World::Scene> m_scene;

    };

    bool RegisterEngineCommands();
}

#endif //SRENGINE_ENGINECOMMANDS_H
