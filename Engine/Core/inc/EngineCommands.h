//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENGINECOMMANDS_H
#define SRENGINE_ENGINECOMMANDS_H

#include <Types/SafePointer.h>
#include <CommandManager/CmdManager.h>
#include <EntityComponentSystem/EntityManager.h>

namespace Framework::Helper {
    class GameObject;

    namespace World {
        class Scene;
    }
}

namespace Framework::Core::Commands {
    class GameObjectRename : public Helper::ICommand {
    public:
        ~GameObjectRename() override = default;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectRename"; }
    };

    class GameObjectDelete : public Helper::ICommand {
    public:
        GameObjectDelete() = default;
        explicit GameObjectDelete(const Helper::Types::SafePtr<Helper::GameObject>& ptr);

        ~GameObjectDelete() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectDelete"; }

    private:
        Helper::EntityPath m_path;
        Helper::EntityBranch m_reserved;
        SR_XML_NS::Document m_backup;
        Helper::Types::SafePtr<Helper::World::Scene> m_scene;

    };

    bool RegisterEngineCommands();
}

#endif //SRENGINE_ENGINECOMMANDS_H
