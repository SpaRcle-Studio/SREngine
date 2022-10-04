//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ICOMMAND_H
#define SRENGINE_ICOMMAND_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    class CmdManager;

    class SR_DLL_EXPORT ICommand {
    public:
        ICommand() = default;
        virtual ~ICommand() = default;

    };
}

#endif //SRENGINE_ICOMMAND_H
