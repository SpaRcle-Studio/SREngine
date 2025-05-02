//
// Created by Monika on 07.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
#define SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H

#include <Scripting/macros.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/PassKey.h>
#include <Utils/ECS/SceneObject.h>

namespace SR_SCRIPTING_NS {
    class SpaRcleAPIRegister : public SR_UTILS_NS::Singleton<SpaRcleAPIRegister> {
        SR_REGISTER_SINGLETON(SpaRcleAPIRegister)
        using FunctionHandle = void*;
    public:
        SR_NODISCARD uint64_t GetCountFunctions() { return m_functionTable.size(); }
        SR_NODISCARD void* GetFunction(uint64_t index) { return m_functionTable[index]; }
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override { return false; }

        void OnMemoryAlloc() { m_allocationsCount++; }
        void OnMemoryFree() { SRAssert(m_allocationsCount > 0); m_allocationsCount--; }
        void CheckMemoryLeaks() {
            if (m_allocationsCount > 0) {
                SRHalt("Memory leak detected! Allocations count: {}", m_allocationsCount.load());
            }
        }

    public:
        void SetRegisterFunction(std::function<void(std::vector<FunctionHandle>&)> func) {
            m_registerFunction = std::move(func);
        }

        void RegisterAPI() {
            if (!m_isRegistered) {
                if (m_registerFunction) {
                    m_registerFunction(m_functionTable);
                }
                m_isRegistered = true;
            }
        }

    private:
        std::function<void(std::vector<FunctionHandle>&)> m_registerFunction;
        std::vector<FunctionHandle> m_functionTable;
        bool m_isRegistered = false;
        std::atomic<uint64_t> m_allocationsCount = 0;

    };

    class ModuleManager;
    class ScriptSystem;

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

        void ResetBehaviours() { m_behaviours.clear(); }
        void AddBehaviour(SR_UTILS_NS::StringAtom behaviourName) { m_behaviours.insert(behaviourName); }

    private:
        SR_UTILS_NS::Path m_path;
        SR_UTILS_NS::StringAtom m_moduleName;
        std::set<SR_UTILS_NS::StringAtom> m_behaviours;
        void* m_moduleHandle = nullptr;

    };

    class CppBehaviourInstance {
        using ReloadCallback = SR_HTYPES_NS::Function<void()>;
        using ManagerPasskey = SR_UTILS_NS::Passkey<ModuleManager>;
        using VoidFunc = void(*)(void*);
        using UpdateFunc = void(*)(void*, float_t);
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetBehaviourName() const { return m_behaviourName; }
        SR_NODISCARD const ReloadCallback& GetReloadCallback() const { return m_reloadCallback; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetModuleName() const { return m_moduleName; }

        void SetBehaviourName(SR_UTILS_NS::StringAtom name, ManagerPasskey) { m_behaviourName = name; }
        void SetModuleName(SR_UTILS_NS::StringAtom name, ManagerPasskey) { m_moduleName = name; }
        void SetReloadCallback(const ReloadCallback& callback) { m_reloadCallback = callback; }

        void OnBehaviourUnloaded(ManagerPasskey);
        void OnBehaviourLoaded(ManagerPasskey);

        void Awake() { }
        void OnEnable() { }
        void OnDisable() { }
        void OnAttached() { }
        void OnDetached() { }
        void OnDestroy() { }
        void Start() { }
        void FixedUpdate() { }
        void Update(float_t dt) { }
        void SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject);

    private:
        SR_UTILS_NS::StringAtom m_moduleName;
        SR_UTILS_NS::StringAtom m_behaviourName;
        ReloadCallback m_reloadCallback;

    };

    class ModuleManager : public SR_HTYPES_NS::SharedPtr<ModuleManager> {
        using Super = SR_HTYPES_NS::SharedPtr<ModuleManager>;
    public:
        ModuleManager(ScriptSystem* pScriptSystem)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_pScriptSystem(pScriptSystem)
        { }

        ~ModuleManager() override;

    public:
        bool Init();

        SR_NODISCARD bool ReloadModule(const SR_UTILS_NS::Path& path);

        SR_NODISCARD CppBehaviourInstance* AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName);
        void FreeBehaviourInstance(CppBehaviourInstance* pInstance);

        SR_NODISCARD bool HasBehaviour(SR_UTILS_NS::StringAtom behaviourName) const;

    private:
        bool AllocateBehaviourInternalInstance(CppBehaviourInstance* pInstance);
        void FreeBehaviourInternalInstance(CppBehaviourInstance* pInstance);

        SR_NODISCARD void* LoadModule(const SR_UTILS_NS::Path& modulePath);
        bool InitModule(ScriptModule& module);
        bool UnloadModule(ScriptModule& module);
        SR_NODISCARD ScriptModule* FindModule(SR_UTILS_NS::StringAtom moduleName);

    private:
        SR_UTILS_NS::Path m_resourcesPath;
        SR_UTILS_NS::Path m_cachePath;

        std::string m_lastCompilerVersion;

        std::set<CppBehaviourInstance*> m_behaviourInstances;

        std::vector<ScriptModule> m_modules;
        std::recursive_mutex m_mutex;
        ScriptSystem* m_pScriptSystem = nullptr;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
