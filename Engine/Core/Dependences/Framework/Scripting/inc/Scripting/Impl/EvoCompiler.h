//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_EVOCOMPILER_H
#define GAMEENGINE_EVOCOMPILER_H

#include <Scripting/Base/Compiler.h>

#include <Utils/Xml.h>
#include <EvoScript/Script.h>
#include <EvoScript/Compilation/Compiler.h>
#include <EvoScript/Compilation/AddressTableGen.h>
#include <EvoScript/Compilation/Casting.h>

namespace SR_SCRIPTING_NS {
    class EvoCompiler : public SR_SCRIPTING_NS::Compiler, public EvoScript::Compiler {
    public:
        explicit EvoCompiler(std::string cachePath);
        ~EvoCompiler() override;

    public:
        SR_NODISCARD EvoScript::CastingGen* GetCasting() const { return m_casting; }
        SR_NODISCARD EvoScript::AddressTableGen* GetGenerator() const { return m_generator; }

    public:
        bool Init() override;

    private:
        SR_NODISCARD std::string GetGeneratorName(const SR_XML_NS::Node& config) const;

    private:
        EvoScript::AddressTableGen* m_generator = nullptr;
        EvoScript::CastingGen*      m_casting   = nullptr;

    };

    class GlobalEvoCompiler : public EvoCompiler, public SR_UTILS_NS::Singleton<GlobalEvoCompiler> {
        friend SR_UTILS_NS::Singleton<GlobalEvoCompiler>;
    protected:
        GlobalEvoCompiler();
        ~GlobalEvoCompiler() override = default;

    protected:
        void OnSingletonDestroy() override {
            SR_INFO("GlobalEvoCompiler::OnSingletonDestroy() : free global compiler...")
        }

    };
}

#endif //GAMEENGINE_EVOCOMPILER_H
