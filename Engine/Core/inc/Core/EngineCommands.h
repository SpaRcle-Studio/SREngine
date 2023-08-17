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

namespace SR_UTILS_NS {
    class GameObject;

    namespace World {
        class Scene;
    }
}

namespace SR_CORE_NS::GUI {
    class Hierarchy;
}

namespace SR_CORE_NS::Commands {
    class ChangeHierarchySelected : public SR_UTILS_NS::ReversibleCommand {
    public:
        ChangeHierarchySelected() = default;
        explicit ChangeHierarchySelected(SR_CORE_NS::GUI::Hierarchy* hierarchy,
                            const std::set<SR_UTILS_NS::GameObject::Ptr>& oldSelected,
                            const std::set<SR_UTILS_NS::GameObject::Ptr>& newSelected);

        ~ChangeHierarchySelected() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "ChangeHierarchySelected"; }

    private:
        SR_CORE_NS::GUI::Hierarchy* m_hierarchy = nullptr;
        std::set<SR_UTILS_NS::EntityId> m_newSelected;
        std::set<SR_UTILS_NS::EntityId> m_oldSelected;
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

    class GameObjectDelete : public SR_UTILS_NS::ReversibleCommand { ///TODO: подумать над удалением нескольких объектов за раз
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

    class GameObjectInstance : public SR_UTILS_NS::ReversibleCommand { ///TODO: Нужно сильно переработать, в частности для GUISystem
    public:
        GameObjectInstance() = default;
        explicit GameObjectInstance(SR_HTYPES_NS::Marshal::Ptr pMarshal,
                                    const SR_UTILS_NS::GameObject::Ptr& pParent = nullptr);

        ~GameObjectInstance() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectInstance"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_UTILS_NS::EntityBranch m_reserved;
        SR_HTYPES_NS::Marshal::Ptr m_marshal = nullptr;
        SR_HTYPES_NS::SafePtr<Helper::World::Scene> m_scene;
        SR_UTILS_NS::EntityId m_parent = { };

    };

    class HierarchyPaste : public SR_UTILS_NS::ReversibleCommand {
    public:
        HierarchyPaste() = default;
        explicit HierarchyPaste(SR_CORE_NS::GUI::Hierarchy* hierarchy, SR_HTYPES_NS::Marshal::Ptr marshal);

        ~HierarchyPaste() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "HierarchyPaste"; }

    private:

        SR_HTYPES_NS::Marshal::Ptr m_marshal = nullptr;
        SR_CORE_NS::GUI::Hierarchy* m_hierarchy = nullptr;
        std::list<SR_UTILS_NS::EntityPath> m_paths;
        std::list<SR_UTILS_NS::EntityBranch> m_reserved;
        SR_WORLD_NS::Scene::Ptr m_scene;
        SR_UTILS_NS::EntityId m_parent = { };

    };

    class GameObjectMove : public SR_UTILS_NS::ReversibleCommand {
    public:
        GameObjectMove() = default;
        explicit GameObjectMove(const SR_UTILS_NS::GameObject::Ptr& ptr, const SR_UTILS_NS::GameObject::Ptr& newDestination);

        ~GameObjectMove() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectMove"; }

    private:
        SR_UTILS_NS::EntityPath m_newDestinationPath;
        SR_UTILS_NS::EntityPath m_oldDestinationPath;
        SR_UTILS_NS::EntityPath m_path;
    };

    bool RegisterEngineCommands();
}

#endif //SRENGINE_ENGINECOMMANDS_H
