//
// Created by Monika on 16.05.2022.
//

#ifndef SRENGINE_REVERSIBLECOMMAND_H
#define SRENGINE_REVERSIBLECOMMAND_H

#include <CommandManager/ICommand.h>
#include <Xml.h>

namespace SR_UTILS_NS {
    class CmdManager;

    class ReversibleCommand : public ICommand {
        friend class CmdManager;
    public:
        ReversibleCommand() = default;
        ~ReversibleCommand() override = default;

    private:
        virtual bool Redo() = 0;
        virtual bool Undo() = 0;
        virtual std::string GetName() = 0;

    public:
        virtual bool Load(const Xml::Node& node) { return false; }
        SR_NODISCARD virtual Xml::Node Save() const { return Xml::Node(); }

    };
}

#define SR_MAKE_REVERSIBLE_CMD_ALLOCATOR(type) []() -> SR_UTILS_NS::ReversibleCommand* { return dynamic_cast<SR_UTILS_NS::ReversibleCommand*>(new type()); }
#define SR_REGISTER_REVERSIBLE_CMD(manager, type) manager->RegisterCommand(#type, SR_MAKE_REVERSIBLE_CMD_ALLOCATOR(type))

#endif //SRENGINE_REVERSIBLECOMMAND_H
