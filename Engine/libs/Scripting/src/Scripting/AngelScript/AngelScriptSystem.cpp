//
// Created by Codex on 13.11.2026.
//

#include <Scripting/AngelScript/AngelScriptSystem.h>
#include <Scripting/AngelScript/AngelScriptRuntime.h>

#include <Utils/Platform/Platform.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/Events/Broadcaster.h>

namespace SR_SCRIPTING_NS {
    AngelScriptSystem::AngelScriptSystem()
        : SR_HTYPES_NS::SharedPtr<AngelScriptSystem>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        , m_pRuntime(new AngelScriptRuntime())
    { }

    AngelScriptSystem::~AngelScriptSystem() {
        SR_TRACY_ZONE;
        WaitForIdle();
        delete m_pRuntime;
    }

    void AngelScriptSystem::HandleFileEvent(const SR_UTILS_NS::Path& path) {
        std::lock_guard lock(m_pendingFilesMutex);
        m_pendingFiles.insert(path);
    }

    void AngelScriptSystem::SetReloadRequest() {
        m_reloadRequested = true;
    }

    void AngelScriptSystem::ReloadModuleIfNeeded() {
        if (m_isLoading) {
            if (!m_initializationFinished) {
                return;
            }
            m_isLoading = false;
            SR_UTILS_NS::Broadcaster::Instance().Broadcast(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID);
        }

        {
            std::lock_guard lock(m_pendingFilesMutex);
            for (auto&& path : m_pendingFiles) {
                m_pRuntime->HandleFileEvent(path);
            }
            m_pendingFiles.clear();
        }
        if (m_reloadRequested.exchange(false)) {
            m_pRuntime->SetReloadRequest();
        }
        m_pRuntime->ReloadModuleIfNeeded();
    }

    void AngelScriptSystem::WaitForIdle() {
        if (!m_initializationStarted) {
            return;
        }
        while (!m_initializationFinished) {
            SR_PLATFORM_NS::Sleep(10);
        }
    }

    void AngelScriptSystem::AsyncInitialize() {
        if (m_initializationStarted.exchange(true)) {
            return;
        }
        auto initialize = [this](auto&&) {
            SR_TRACY_ZONE_N("Initialize AngelScript asynchronously");
            SR_UTILS_NS::Set<SR_UTILS_NS::Path> pendingFiles;
            {
                std::lock_guard lock(m_pendingFilesMutex);
                pendingFiles.swap(m_pendingFiles);
            }
            for (auto&& path : pendingFiles) {
                m_pRuntime->HandleFileEvent(path);
            }
            m_pRuntime->EnsureInitialized();
            m_initializationFinished = true;
        };
        if (SR_PLATFORM_NS::IsSupportThreads()) {
            const auto taskId = SR_UTILS_NS::TaskManager::Instance().ExecuteAsync(initialize, SR_UTILS_NS::TaskPriority::High);
            SR_UTILS_NS::TaskManager::Instance().SetDescription(taskId, "Init Angel Script");
        }
        else {
            SR_UTILS_NS::Task::AtomicState state;
            initialize(state);
        }
    }

    SR_UTILS_NS::Set<SR_UTILS_NS::Path> AngelScriptSystem::GetSourceFiles() const {
        return IsLoading() ? SR_UTILS_NS::Set<SR_UTILS_NS::Path>() : m_pRuntime->GetSourceFiles();
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> AngelScriptSystem::GetBehaviourNames() const {
        return IsLoading() ? SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>() : m_pRuntime->GetBehaviourNames();
    }

    bool AngelScriptSystem::IsModuleDirty() const {
        return !IsLoading() && m_pRuntime->IsModuleDirty();
    }

    bool AngelScriptSystem::HasErrors() const {
        return !IsLoading() && m_pRuntime->HasErrors();
    }

    bool AngelScriptSystem::IsAvailable() const {
        return !IsLoading() && m_pRuntime->IsAvailable();
    }

    BehaviourInstance* AngelScriptSystem::AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name) {
        return IsLoading() ? nullptr : m_pRuntime->AllocateBehaviourInstance(name);
    }

    void AngelScriptSystem::FreeBehaviourInstance(BehaviourInstance* pInstance) {
        m_pRuntime->FreeBehaviourInstance(pInstance);
    }
}
