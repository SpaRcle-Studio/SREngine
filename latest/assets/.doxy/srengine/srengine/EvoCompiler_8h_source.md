

# File EvoCompiler.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Impl**](dir_4eaf059bf86cb1a50633501e0fe5274e.md) **>** [**EvoCompiler.h**](EvoCompiler_8h.md)

[Go to the documentation of this file](EvoCompiler_8h.md)


```C++
//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_EVOCOMPILER_H
#define SR_ENGINE_EVOCOMPILER_H

#include <Utils/Resources/Xml.h>

#include <Scripting/Base/Compiler.h>
#include <Scripting/Script.h>
#include <Scripting/Compilation/Compiler.h>
#include <Scripting/Compilation/AddressTableGen.h>
#include <Scripting/Compilation/Casting.h>

namespace SR_SCRIPTING_NS {
    class SR_SCRIPTING_DLL_API EvoCompiler : public SR_SCRIPTING_NS::Compiler, public EvoScript::Compiler {
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

    class SR_SCRIPTING_DLL_API GlobalEvoCompiler : public SR_UTILS_NS::Singleton<GlobalEvoCompiler>, public EvoCompiler  {
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


