

# File EvoScriptImpl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Impl**](dir_4eaf059bf86cb1a50633501e0fe5274e.md) **>** [**EvoScriptImpl.h**](EvoScriptImpl_8h.md)

[Go to the documentation of this file](EvoScriptImpl_8h.md)


```C++
//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_SREVOSCRIPT_H
#define SR_ENGINE_SREVOSCRIPT_H

#include <Scripting/Base/Script.h>
#include <Scripting/Script.h>

#include <Utils/FileSystem/Path.h>

namespace SR_SCRIPTING_NS {
    class Compiler;

    class SR_DEPRECATED EvoScriptImpl : public Script {
        using Super = Script;
    public:
        EvoScriptImpl(Compiler* compiler, const std::string& name, const SR_UTILS_NS::Path& path)
            : Super(compiler, name, path.ToString())
        { }

        ~EvoScriptImpl() override = default;

    public:
        bool Compile() override;

    private:
        EvoScript::Script* m_script = nullptr;

    };
}

#endif //SR_ENGINE_SREVOSCRIPT_H
```


