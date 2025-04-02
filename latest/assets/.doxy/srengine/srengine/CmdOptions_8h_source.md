

# File CmdOptions.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**CmdOptions.h**](CmdOptions_8h.md)

[Go to the documentation of this file](CmdOptions_8h.md)


```C++
//
// Created by Monika on 22.11.2021.
//

#ifndef SR_ENGINE_CMDOPTIONS_H
#define SR_ENGINE_CMDOPTIONS_H

#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    extern std::string GetCmdOption(char **begin, char **end, const std::string &option);
    extern bool HasCmdOption(char **begin, char **end, const std::string &option);
}

#endif //SR_ENGINE_CMDOPTIONS_H
```


