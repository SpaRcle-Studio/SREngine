

# File Compiler.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Compiler.h**](Compiler_8h.md)

[Go to the documentation of this file](Compiler_8h.md)


```C++
//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_COMPILER_H
#define SR_ENGINE_COMPILER_H

#include <Scripting/Base/Script.h>

namespace SR_SCRIPTING_NS {
    class Compiler : SR_UTILS_NS::NonCopyable {
        using Mutex = std::recursive_mutex;
    protected:
        Compiler() = default;

    public:
        ~Compiler() override = default;

    public:
        virtual bool Init() = 0;

    protected:
        Mutex m_mutex = Mutex();

    };
}

#endif //SR_ENGINE_COMPILER_H
```


