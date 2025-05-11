

# File CmdOptions.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**CmdOptions.h**](CmdOptions_8h.md)

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


