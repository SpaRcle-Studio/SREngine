

# File EvoScriptImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Impl**](dir_24f2b9252cbd3f2e0c4afbfdbb5b103e.md) **>** [**EvoScriptImpl.h**](EvoScriptImpl_8h.md)

[Go to the documentation of this file](EvoScriptImpl_8h.md)


```C++
//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_SREVOSCRIPT_H
#define SR_ENGINE_SREVOSCRIPT_H

#include <Scripting/Base/Script.h>
#include <EvoScript/Script.h>
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


