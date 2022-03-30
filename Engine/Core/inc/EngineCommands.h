//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENGINECOMMANDS_H
#define SRENGINE_ENGINECOMMANDS_H

#include <Types/SafePointer.h>
#include <CommandManager/CmdManager.h>
#include <EntityComponentSystem/EntityManager.h>

namespace SR_UTILS_NS {
    class GameObject;

    namespace World {
        class Scene;
    }
}

namespace SR_CORE_NS::Commands {
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
        explicit GameObjectDelete(const SR_HTYPES_NS::SafePtr<Helper::GameObject>& ptr);

        ~GameObjectDelete() override;

        bool Redo() override;
        bool Undo() override;

        std::string GetName() override { return "GameObjectDelete"; }

    private:
        SR_UTILS_NS::EntityPath m_path;
        SR_UTILS_NS::EntityBranch m_reserved;
        SR_UTILS_NS::MarshalEncodeNode m_backup;
        SR_HTYPES_NS::SafePtr<Helper::World::Scene> m_scene;

    };

    bool RegisterEngineCommands();
}

#endif //SRENGINE_ENGINECOMMANDS_H
