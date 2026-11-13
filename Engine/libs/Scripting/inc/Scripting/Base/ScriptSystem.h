//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_H
#define SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_H

#include <Scripting/Cpp/CppScriptSystem.h>
#include <Scripting/AngelScript/AngelScriptSystem.h>

#include <Utils/Common/Singleton.h>

namespace SR_SCRIPTING_NS {
    class BehaviourInstance;

    class SR_SCRIPTING_DLL_API ScriptSystem : public SR_UTILS_NS::Singleton<ScriptSystem> {
        SR_REGISTER_SINGLETON(ScriptSystem)
    private:
        ScriptSystem() = default;
        ~ScriptSystem() override;

    public:
        SR_NODISCARD bool Init(bool compilationEnabled);
        SR_NODISCARD bool IsInitialized() const {
            return m_isInit;
        }

        SR_NODISCARD ScriptSystemState GetState() const;
        SR_NODISCARD bool HasErrors() const;
        SR_NODISCARD const SR_UTILS_NS::Path& GetAPIFolder() const {
            return m_cppSystem->GetAPIFolder();
        }

        SR_NODISCARD CppScriptSystem* GetCppSystem() const {
            return const_cast<CppScriptSystem*>(m_cppSystem.Get());
        }

        SR_NODISCARD AngelScriptSystem* GetAngelScriptSystem() const {
            return const_cast<AngelScriptSystem*>(m_angelScriptSystem.Get());
        }

        SR_NODISCARD BehaviourInstance* AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name);
        void FreeBehaviourInstance(BehaviourInstance* pInstance);
        SR_NODISCARD SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> GetBehaviourNames() const;

        void WaitForIdle();
        void ReloadModulesIfNeeded();
        void SetReloadRequest();

    private:
        void InitialAnalyse();
        void HandleFileSystemEvent(const SR_UTILS_NS::SubscriptionMessage& message, SR_UTILS_NS::FileSystemWatcher::EventType eventType);
        void HandleFileEvent(SR_UTILS_NS::Path path);
        void ResetSubscriptions();

    private:
        bool m_isInit = false;
        CppScriptSystem::Ptr m_cppSystem;
        AngelScriptSystem::Ptr m_angelScriptSystem;
        SR_UTILS_NS::Subscription m_fileChangedSubscription;
        SR_UTILS_NS::Subscription m_fileCreatedSubscription;
        SR_UTILS_NS::Subscription m_fileDeletedSubscription;
        SR_UTILS_NS::Subscription m_fileMovedSubscription;
        SR_UTILS_NS::Set<SR_UTILS_NS::Path> m_knownFiles;
    };
}

#endif // SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_H
