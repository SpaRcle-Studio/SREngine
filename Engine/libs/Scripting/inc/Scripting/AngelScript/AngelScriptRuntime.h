//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_RUNTIME_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_RUNTIME_H

#include <Scripting/stdInclude.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Set.h>
#include <Utils/Types/Vector.h>
#include <Utils/Types/Time.h>

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
class asIScriptEngine;
class asIScriptModule;
class asIScriptObject;
class asIScriptContext;
#endif

namespace SR_SCRIPTING_NS {
    class BehaviourInstance;
    class AngelScriptBehaviourInstance;
    class AngelScriptBindings;
    class AngelScriptDebugger;

    class AngelScriptRuntime {
    public:
        AngelScriptRuntime();
        ~AngelScriptRuntime();
        bool EnsureInitialized();

    public:
        void HandleFileEvent(const SR_UTILS_NS::Path& path);
        void SetReloadRequest();
        void ReloadModuleIfNeeded();
    public:
        SR_NODISCARD SR_UTILS_NS::Set<SR_UTILS_NS::Path> GetSourceFiles() const;
        SR_NODISCARD bool IsModuleDirty() const;
        SR_NODISCARD bool HasErrors() const;
        SR_NODISCARD bool IsAvailable() const;
        SR_NODISCARD SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> GetBehaviourNames() const;
        SR_NODISCARD BehaviourInstance* AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name);

        void FreeBehaviourInstance(BehaviourInstance* pInstance);

    #if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
        SR_NODISCARD AngelScriptBindings* GetBindings() const {
            return m_pBindings;
        }

        SR_NODISCARD asIScriptEngine* GetEngine() const {
            return m_pEngine;
        }

        bool Execute(asIScriptContext* pContext) const;
    #endif

    private:
    #if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
        bool BuildModule();
        void GeneratePredefined(const SR_UTILS_NS::String& behaviourDeclaration) const;
        void DiscoverSourceNames() const;
        asIScriptObject* CreateObject(asIScriptModule* pModule, SR_UTILS_NS::StringAtom name);
    #endif

    private:
        mutable std::recursive_mutex m_mutex;
        SR_UTILS_NS::Set<SR_UTILS_NS::Path> m_sourceFiles;
        SR_UTILS_NS::Set<AngelScriptBehaviourInstance*> m_instances;
        SR_UTILS_NS::TimePointType m_lastFileSystemEvent;
        mutable SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> m_behaviourNames;
        mutable bool m_namesDirty = true;
        bool m_moduleDirty = false;
        bool m_hasErrors = false;
        bool m_initializationAttempted = false;
        bool m_initializing = false;
        uint64_t m_generation = 0;
    #if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
        asIScriptEngine* m_pEngine = nullptr;
        asIScriptModule* m_pModule = nullptr;
        AngelScriptBindings* m_pBindings = nullptr;
        AngelScriptDebugger* m_pDebugger = nullptr;
    #endif
    };
}

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_RUNTIME_H
