//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_EVOCOMPILER_H
#define GAMEENGINE_EVOCOMPILER_H

#include <Base/Compiler.h>

#include <EvoScript/Script.h>
#include <EvoScript/Compilation/Compiler.h>
#include <EvoScript/Compilation/AddressTableGen.h>
#include <EvoScript/Compilation/Casting.h>

namespace Framework::Scripting {
    class EvoCompiler : public Compiler {
    public:
        EvoCompiler() = default;
        EvoCompiler(const EvoCompiler&) = delete;
    private:
        ~EvoCompiler() override = default;
    private:
        EvoScript::Compiler*        m_compiler      = nullptr;
        EvoScript::AddressTableGen* m_generator     = nullptr;
        EvoScript::CastingGen*      m_casting       = nullptr;
    public:
        [[nodiscard]] EvoScript::CastingGen*      GetCasting()           const { return m_casting;   }
        [[nodiscard]] EvoScript::AddressTableGen* GetGenerator()         const { return m_generator; }
        [[nodiscard]] EvoScript::Compiler*        GetEvoScriptCompiler() const { return m_compiler;  }

    public:
        bool Init() override;

        bool Destroy() override {
            if (m_compiler) {
                m_compiler->Destroy();
                m_compiler->Free();
                m_compiler = nullptr;
            }

            if (m_generator) {
                delete m_generator;
                m_generator = nullptr;
            }

            return true;
        }

        void Free() override {
            delete this;
        }
    };
}

#endif //GAMEENGINE_EVOCOMPILER_H
