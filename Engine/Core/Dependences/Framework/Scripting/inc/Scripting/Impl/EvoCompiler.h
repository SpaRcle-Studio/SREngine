//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_EVOCOMPILER_H
#define GAMEENGINE_EVOCOMPILER_H

#include <Scripting/Base/Compiler.h>

#include <Xml.h>
#include <EvoScript/Script.h>
#include <EvoScript/Compilation/Compiler.h>
#include <EvoScript/Compilation/AddressTableGen.h>
#include <EvoScript/Compilation/Casting.h>

namespace SR_SCRIPTING_NS {
    class EvoCompiler : public Compiler {
    public:
        EvoCompiler() = default;
        ~EvoCompiler() override = default;

    public:
        SR_NODISCARD EvoScript::CastingGen*      GetCasting()           const { return m_casting;   }
        SR_NODISCARD EvoScript::AddressTableGen* GetGenerator()         const { return m_generator; }
        SR_NODISCARD EvoScript::Compiler*        GetEvoScriptCompiler() const { return m_compiler;  }

    public:
        bool Init() override;
        bool Destroy() override;

    private:
        SR_NODISCARD std::string GetGenerator(const SR_XML_NS::Node& config) const;

    private:
        EvoScript::Compiler*        m_compiler      = nullptr;
        EvoScript::AddressTableGen* m_generator     = nullptr;
        EvoScript::CastingGen*      m_casting       = nullptr;

    };
}

#endif //GAMEENGINE_EVOCOMPILER_H
