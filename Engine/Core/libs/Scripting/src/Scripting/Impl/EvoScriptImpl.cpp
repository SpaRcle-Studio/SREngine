//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Impl/EvoScriptImpl.h>
#include <Scripting/Impl/EvoCompiler.h>

#include <Utils/Common/Features.h>

namespace SR_SCRIPTING_NS {
    bool EvoScriptImpl::Compile() {
        auto&& compiler = dynamic_cast<Scripting::EvoCompiler*>(m_compiler);

        if (!compiler || !compiler->GetGenerator()) {
            SR_ERROR("EvoScriptImpl::Compile() : compiler is not init! \n\tPath: " + m_path);
            return false;
        }

        m_script = EvoScript::Script::Allocate(m_name, compiler->GetGenerator()->GetAddresses());

        const bool canCompile = SR_UTILS_NS::Features::Instance().Enabled("EvoCompiler");
        if (!m_script->Load(m_path, *compiler, canCompile)) {
            SR_ERROR("EvoScriptImpl::Compile() : failed to load script!");
            return false;
        }

        return true;
    }
}
