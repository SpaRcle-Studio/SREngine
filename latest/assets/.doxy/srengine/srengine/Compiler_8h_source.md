

# File Compiler.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Compiler.h**](Compiler_8h.md)

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


