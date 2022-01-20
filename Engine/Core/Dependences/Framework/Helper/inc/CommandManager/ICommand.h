//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ICOMMAND_H
#define SRENGINE_ICOMMAND_H

#include <Xml.h>
#include <functional>

#define SR_MAKE_CMD_ALLOCATOR(type) []() -> ICommand* { return dynamic_cast<ICommand*>(new type()); }
#define SR_REGISTER_CMD(manager, type) manager->RegisterCommand(#type, SR_MAKE_CMD_ALLOCATOR(type))

namespace Framework::Helper {
    class CmdManager;

    class ICommand {
        friend class CmdManager;
    public:
        ICommand() = default;
        virtual ~ICommand() = default;

    private:
        virtual bool Redo() = 0;
        virtual bool Undo() = 0;

    public:
        virtual bool Load(const Xml::Node& node) { return false; }
        [[nodiscard]] virtual Xml::Node Save() const { return Xml::Node(); }

    };
}

#endif //SRENGINE_ICOMMAND_H
