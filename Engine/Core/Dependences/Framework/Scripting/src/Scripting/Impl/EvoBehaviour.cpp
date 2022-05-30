//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    bool EvoBehaviour::Load() {
        SR_SCOPED_LOCK

        if (m_script) {
            SR_ERROR("EvoBehaviour::Load() : script already loaded!");
            return false;
        }

        auto&& path = GetResourceId();

        if (!path.empty()) {
            auto&& compiler = GlobalEvoCompiler::Instance();

            m_script = EvoScript::Script::Allocate("Behaviour", compiler.GetGenerator()->GetAddresses());

            if (!m_script || !m_script->Load(path, compiler, true)) {
                SR_ERROR("EvoBehaviour::Load() : failed to load script! \n\tPath: " + path);
                return false;
            }
        }

        return Behaviour::Load();
    }

    bool EvoBehaviour::Unload() {
        SR_SCOPED_LOCK

        bool hasErrors = !Behaviour::Unload();

        if (m_script) {
            m_script->Destroy();
            delete m_script;
            m_script = nullptr;
        }

        return !hasErrors;
    }
}