

# File ICommand.h

[**File List**](files.md) **>** [**CommandManager**](dir_ccc40ac273e6f569bc0e58b2cdbc2be5.md) **>** [**ICommand.h**](ICommand_8h.md)

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

    class SR_COMMON_DLL_API ICommand {
    public:
        inline static auto DATA_ID = SR_UTILS_NS::SerializationId::Create("command");

    public:
        ICommand() = default;
        virtual ~ICommand() = default;

    };
}

#endif //SR_ENGINE_ICOMMAND_H
```


