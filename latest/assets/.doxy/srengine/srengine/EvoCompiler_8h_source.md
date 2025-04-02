

# File EvoCompiler.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Impl**](dir_24f2b9252cbd3f2e0c4afbfdbb5b103e.md) **>** [**EvoCompiler.h**](EvoCompiler_8h.md)

[Go to the documentation of this file](EvoCompiler_8h.md)


```C++
//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_EVOCOMPILER_H
#define SR_ENGINE_EVOCOMPILER_H

#include <Scripting/Base/Compiler.h>

#include <Utils/Resources/Xml.h>
#include <EvoScript/Script.h>
#include <EvoScript/Compilation/Compiler.h>
#include <EvoScript/Compilation/AddressTableGen.h>
#include <EvoScript/Compilation/Casting.h>

namespace SR_SCRIPTING_NS {
    class SR_DLL_EXPORT EvoCompiler : public SR_SCRIPTING_NS::Compiler, public EvoScript::Compiler {
    public:
        explicit EvoCompiler(std::string cachePath);
        ~EvoCompiler() override;

    public:
        SR_NODISCARD EvoScript::CastingGen* GetCasting() const { return m_casting; }
        SR_NODISCARD EvoScript::AddressTableGen* GetGenerator() const;

    public:
        bool Init() override;

    private:
        SR_NODISCARD std::string GetGeneratorName(const SR_XML_NS::Node& config) const;

    private:
        EvoScript::AddressTableGen* m_generator = nullptr;
        EvoScript::CastingGen*      m_casting   = nullptr;

    };

    class SR_DLL_EXPORT GlobalEvoCompiler : public SR_UTILS_NS::Singleton<GlobalEvoCompiler>, public EvoCompiler  {
        SR_REGISTER_SINGLETON(GlobalEvoCompiler)
    protected:
        GlobalEvoCompiler();
        ~GlobalEvoCompiler() override = default;

    protected:
        void OnSingletonDestroy() override {
            SR_INFO("GlobalEvoCompiler::OnSingletonDestroy() : free global compiler...");
        }

    };
}

#endif //SR_ENGINE_EVOCOMPILER_H
```


