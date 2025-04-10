//
// Created by Monika on 07.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
#define SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/PassKey.h>

namespace SR_SCRIPTING_NS {
    class ModuleManager;

    class ScriptModule {
    public:
        SR_NODISCARD void* GetModuleHandle() const { return m_moduleHandle; }
        void SetModuleHandle(void* pHandle) { m_moduleHandle = pHandle; }

        SR_NODISCARD const SR_UTILS_NS::Path& GetPath() const { return m_path; }
        void SetPath(const SR_UTILS_NS::Path& path) { m_path = path; }

        SR_NODISCARD const SR_UTILS_NS::StringAtom& GetModuleName() const { return m_moduleName; }
        void SetModuleName(const SR_UTILS_NS::StringAtom& name) { m_moduleName = name; }

        SR_NODISCARD bool HasBehaviour(SR_UTILS_NS::StringAtom behaviourName) const {
            return m_behaviours.count(behaviourName) > 0;
        }

    private:
        SR_UTILS_NS::Path m_path;
        SR_UTILS_NS::StringAtom m_moduleName;
        std::set<SR_UTILS_NS::StringAtom> m_behaviours;
        void* m_moduleHandle = nullptr;

    };

    class CppBehaviourInstance {
        using ReloadCallback = SR_HTYPES_NS::Function<void()>;
        using ManagerPasskey = SR_UTILS_NS::Passkey<ModuleManager>;
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetBehaviourName() const { return m_behaviourName; }
        SR_NODISCARD void* GetInstance() const { return m_pInstance; }
        SR_NODISCARD const ReloadCallback& GetReloadCallback() const { return m_reloadCallback; }

        void SetBehaviourName(const SR_UTILS_NS::StringAtom& name, ManagerPasskey) { m_behaviourName = name; }
        void SetInstance(void* pInstance, ManagerPasskey) { m_pInstance = pInstance; }
        void SetReloadCallback(const ReloadCallback& callback) { m_reloadCallback = callback; }

    private:
        SR_UTILS_NS::StringAtom m_behaviourName;
        void* m_pInstance = nullptr;
        ReloadCallback m_reloadCallback;

    };

    class ModuleManager : public SR_HTYPES_NS::SharedPtr<ModuleManager> {
        using Super = SR_HTYPES_NS::SharedPtr<ModuleManager>;
    public:
        ModuleManager()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    public:
        bool Init();

        SR_NODISCARD bool ReloadModule(const SR_UTILS_NS::Path& path);

        SR_NODISCARD CppBehaviourInstance* AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName);
        void FreeBehaviourInstance(CppBehaviourInstance* pInstance);

    private:
        SR_NODISCARD void* LoadModule(const SR_UTILS_NS::Path& modulePath);

    private:
        SR_UTILS_NS::Path m_resourcesPath;
        SR_UTILS_NS::Path m_cachePath;

        std::string m_lastCompilerVersion;

        std::set<CppBehaviourInstance*> m_behaviourInstances;

        std::vector<ScriptModule> m_modules;
        std::recursive_mutex m_mutex;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
