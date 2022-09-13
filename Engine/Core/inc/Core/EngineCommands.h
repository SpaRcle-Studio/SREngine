//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENGINECOMMANDS_H
#define SRENGINE_ENGINECOMMANDS_H

#include <Utils/Types/SafePointer.h>
#include <Utils/CommandManager/CmdManager.h>
#include <Utils/ECS/EntityManager.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS {
    class GameObject;

    namespace World {
        class Scene;
    }
}

namespace SR_CORE_NS::Commands {
    class GameObjectRename : public SR_UTILS_NS::ReversibleCommand {
    public:
        ~GameObjectRename() override = default;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectRename"; }
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
