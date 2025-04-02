

# File ICommand.h

[**File List**](files.md) **>** [**CommandManager**](dir_24ef48620107e14c766ff883ed46f46c.md) **>** [**ICommand.h**](ICommand_8h.md)

[Go to the documentation of this file](ICommand_8h.md)


```C++
//
// Created by Monika on 08.01.2022.
//

#ifndef SR_ENGINE_ICOMMAND_H
#define SR_ENGINE_ICOMMAND_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    class CmdManager;

    class SR_DLL_EXPORT ICommand {
    public:
        inline static auto DATA_ID = SR_UTILS_NS::SerializationId::Create("command");

    public:
        ICommand() = default;
        virtual ~ICommand() = default;

    };
}

#endif //SR_ENGINE_ICOMMAND_H
```


