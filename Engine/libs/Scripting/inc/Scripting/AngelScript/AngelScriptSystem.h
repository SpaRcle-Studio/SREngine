//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_SYSTEM_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_SYSTEM_H

#include <Scripting/stdInclude.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Set.h>
#include <Utils/Types/Vector.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    class BehaviourInstance;
    class AngelScriptRuntime;

    class SR_SCRIPTING_DLL_API AngelScriptSystem : public SR_HTYPES_NS::SharedPtr<AngelScriptSystem> {
    public:
        AngelScriptSystem();
        ~AngelScriptSystem() override;

    public:
        void HandleFileEvent(const SR_UTILS_NS::Path& path);
        void SetReloadRequest();
        void ReloadModuleIfNeeded();

    public:
        SR_NODISCARD SR_UTILS_NS::Set<SR_UTILS_NS::Path> GetSourceFiles() const;
        SR_NODISCARD SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> GetBehaviourNames() const;
        SR_NODISCARD bool IsModuleDirty() const;
        SR_NODISCARD bool HasErrors() const;
        SR_NODISCARD bool IsAvailable() const;

    public:
        SR_NODISCARD BehaviourInstance* AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name);
        void FreeBehaviourInstance(BehaviourInstance* pInstance);

    private:
        AngelScriptRuntime* m_pRuntime = nullptr;
    };
}

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_SYSTEM_H
