//
// Created by Codex on 13.11.2026.
//

#include <Scripting/AngelScript/AngelScriptSystem.h>
#include <Scripting/AngelScript/AngelScriptRuntime.h>

namespace SR_SCRIPTING_NS {
    AngelScriptSystem::AngelScriptSystem()
        : SR_HTYPES_NS::SharedPtr<AngelScriptSystem>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        , m_pRuntime(new AngelScriptRuntime())
    { }

    AngelScriptSystem::~AngelScriptSystem() {
        delete m_pRuntime;
    }

    void AngelScriptSystem::HandleFileEvent(const SR_UTILS_NS::Path& path) {
        m_pRuntime->HandleFileEvent(path);
    }

    void AngelScriptSystem::SetReloadRequest() {
        m_pRuntime->SetReloadRequest();
    }

    void AngelScriptSystem::ReloadModuleIfNeeded() {
        m_pRuntime->ReloadModuleIfNeeded();
    }

    SR_UTILS_NS::Set<SR_UTILS_NS::Path> AngelScriptSystem::GetSourceFiles() const {
        return m_pRuntime->GetSourceFiles();
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> AngelScriptSystem::GetBehaviourNames() const {
        return m_pRuntime->GetBehaviourNames();
    }

    bool AngelScriptSystem::IsModuleDirty() const {
        return m_pRuntime->IsModuleDirty();
    }

    bool AngelScriptSystem::HasErrors() const {
        return m_pRuntime->HasErrors();
    }

    bool AngelScriptSystem::IsAvailable() const {
        return m_pRuntime->IsAvailable();
    }

    BehaviourInstance* AngelScriptSystem::AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name) {
        return m_pRuntime->AllocateBehaviourInstance(name);
    }

    void AngelScriptSystem::FreeBehaviourInstance(BehaviourInstance* pInstance) {
        m_pRuntime->FreeBehaviourInstance(pInstance);
    }
}
