//
// Created by Monika on 02.03.2023.
//

#include <Scripting/Impl/EvoScriptManager.h>

namespace SR_SCRIPTING_NS {
    void EvoScriptManager::Update(bool force) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (force) {
            for (auto pIt = m_scripts.begin(); pIt != m_scripts.end(); ) {
                auto&& pHolder = pIt->second;

                if (!pHolder) {
                    pIt = m_scripts.erase(pIt);
                    continue;
                }

                auto&& pScript = pHolder->GetScript<EvoScript::Script>();
                if (!pScript) {
                    pIt = m_scripts.erase(pIt);
                    continue;
                }

                if (pHolder->GetUseCount() == 2) {
                    pHolder->AutoFree([](auto&& pHolder) {
                        delete pHolder->template GetScript<EvoScript::Script>();
                        pHolder->SetScript(nullptr);
                        delete pHolder;
                    });
                    pIt = m_scripts.erase(pIt);
                    continue;
                }

                ++pIt;
            }
            return;
        }

        if (m_scripts.empty()) {
            return;
        }

        if (!m_checkIterator.has_value()) {
            m_checkIterator = m_scripts.begin();
        }

        if (m_checkIterator.value() == m_scripts.end()) {
            m_checkIterator = m_scripts.begin();
            return;
        }

        if (m_checkIterator.value()->second.GetUseCount() == 2) {
            m_checkIterator.value()->second.AutoFree([](auto&& pHolder) {
                delete pHolder->template GetScript<EvoScript::Script>();
                pHolder->SetScript(nullptr);
                delete pHolder;
            });
            m_checkIterator = m_scripts.erase(m_checkIterator.value());
            return;
        }

        ++(m_checkIterator.value()); 
    }

    bool EvoScriptManager::ReloadScript(const SR_UTILS_NS::Path& localPath) {
        SR_LOCK_GUARD;

        auto&& compiler = GlobalEvoCompiler::Instance();

    #ifdef SR_WIN32
        if (m_compilerPath.empty()) {
            m_compilerPath = FindMSVCCompiler();
        }
    #elif defined(SR_LINUX)
        if (m_compilerPath.empty()) {
            m_compilerPath = "usr/bin/g++";
        }
    #endif

        compiler.SetCompilerPath(m_compilerPath);

        m_checkIterator = std::nullopt;

        m_scripts[localPath.ToStringRef()].AutoFree([](ScriptHolder* pHolder) {
            delete pHolder->GetScript<EvoScript::Script>();
            pHolder->SetScript(nullptr);
        });

        auto&& pEvoScript = EvoScript::Script::Allocate(localPath.GetWithoutExtension(), &compiler, compiler.GetGenerator()->GetAddresses());
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

        m_scripts[localPath.ToStringRef()] = new ScriptHolder(pEvoScript);

        return true;
    }

    EvoScriptManager::ScriptPtr EvoScriptManager::Load(const SR_UTILS_NS::Path& localPath) {
        SR_LOCK_GUARD;

        if (m_scripts.count(localPath.ToStringRef()) == 1 && m_scripts.at(localPath.ToStringRef()).Valid()) {
            return m_scripts.at(localPath.ToStringRef());
        }

        SR_LOG("EvoScriptManager::Load() : load \"" + localPath.ToStringRef() + "\" script");

        if (!ReloadScript(localPath)) {
            SR_ERROR("EvoScriptManager::Load() : failed to reload script!\n\tPath: " + localPath.ToStringRef());
            return EvoScriptManager::ScriptPtr();
        }

        return m_scripts.at(localPath.ToStringRef());
    }

    void EvoScriptManager::OnSingletonDestroy() {
        SR_LOCK_GUARD;

        Update(true);

        if (!m_scripts.empty()) {
            SR_ERROR("EvoScriptManager::OnSingletonDestroy() : not all scripts were deleted!\n\tCount: " + std::to_string(m_scripts.size()));
        }

        Singleton::OnSingletonDestroy();
    }

    std::string EvoScriptManager::FindMSVCCompiler() {
        auto&& resourceDirectory = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        auto&& vswherePath = resourceDirectory.Concat("Engine/Utilities/vswhere.exe");
        std::string command = vswherePath.ToStringRef() + " -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find VC/Tools/MSVC/**/bin/Hostx64/x64/cl.exe";
        command += " > vswhereOutput.txt";
        system(command.c_str());

        std::ifstream vswhereOutput("vswhereOutput.txt");
        std::string result;
        getline(vswhereOutput, result);
        vswhereOutput.close();
        return result;
    }
}
