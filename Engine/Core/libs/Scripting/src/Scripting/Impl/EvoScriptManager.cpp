//
// Created by Monika on 02.03.2023.
//

#include <Scripting/Impl/EvoScriptManager.h>

namespace SR_SCRIPTING_NS {
    void EvoScriptManager::Update(float_t dt) {
        SR_LOCK_GUARD
    }

    bool EvoScriptManager::ReloadScript(const SR_UTILS_NS::Path& localPath) {
        SR_LOCK_GUARD

        auto&& compiler = GlobalEvoCompiler::Instance();

        m_scripts[localPath.ToStringRef()].AutoFree([](ScriptHolder* pHolder) {
            delete pHolder->GetScript<EvoScript::Script>();
            pHolder->SetScript(nullptr);
        });

        auto&& pEvoScript = EvoScript::Script::Allocate(localPath.GetWithoutExtension(), compiler.GetGenerator()->GetAddresses());
        if (!pEvoScript) {
            SR_ERROR("EvoScriptManager::Load() : failed to allocate evo script!\n\tPath: " + localPath.ToStringRef());
            return true;
        }

        auto&& fullPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(localPath).GetWithoutExtension();
        if (!pEvoScript->Load(fullPath, compiler, true)) {
            SR_ERROR("EvoScriptManager::Load() : failed to load script! \n\tPath: " + localPath.ToString());
            SR_SAFE_DELETE_PTR(pEvoScript);
            return false;
        }

        m_scripts[localPath.ToStringRef()] = ScriptHolder::Ptr(new ScriptHolder(pEvoScript));

        return true;
    }

    EvoScriptManager::ScriptPtr EvoScriptManager::Load(const SR_UTILS_NS::Path& localPath) {
        SR_LOCK_GUARD

        if (m_scripts.count(localPath.ToStringRef()) == 1 && m_scripts.at(localPath.ToStringRef()).Valid()) {
            return m_scripts.at(localPath.ToStringRef());
        }

        if (!ReloadScript(localPath)) {
            SR_ERROR("EvoScriptManager::Load() : failed to reload script!\n\tPath: " + localPath.ToStringRef());
            return EvoScriptManager::ScriptPtr();
        }

        return m_scripts.at(localPath.ToStringRef());
    }
}
