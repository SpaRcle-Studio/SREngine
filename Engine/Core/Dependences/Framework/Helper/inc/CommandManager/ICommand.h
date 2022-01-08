//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ICOMMAND_H
#define SRENGINE_ICOMMAND_H

#include <Xml.h>
#include <functional>

#define SR_MAKE_CMD_ALLOCATOR(type) []() -> ICommand* { return new type(); }

namespace Framework::Helper {
    class ICommand {
    public:
        ICommand() = default;
        virtual ~ICommand() = default;

    public:
        virtual bool Redo() = 0;
        virtual bool Undo() = 0;

        virtual bool Load(const Xml::Node& node) { return false; }
        [[nodiscard]] virtual Xml::Node Save() const { return Xml::Node(); }

    };
}

#endif //SRENGINE_ICOMMAND_H
