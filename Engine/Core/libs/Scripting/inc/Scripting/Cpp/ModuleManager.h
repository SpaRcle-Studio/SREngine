//
// Created by Monika on 07.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
#define SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H

#include <Scripting/macros.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/PassKey.h>
#include <Utils/ECS/SceneObject.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SR_SCRIPTING_NS {
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

    private:
        SR_UTILS_NS::Path m_path;
        SR_UTILS_NS::StringAtom m_moduleName;
        void* m_moduleHandle = nullptr;

    };

    class CppBehaviourInstance {
        using ReloadCallback = SR_HTYPES_NS::Function<void()>;
        using ManagerPasskey = SR_UTILS_NS::Passkey<ModuleManager>;
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetBehaviourName() const { return m_behaviourName; }
        SR_NODISCARD const ReloadCallback& GetReloadCallback() const { return m_reloadCallback; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetModuleName() const { return m_moduleName; }

        void SetBehaviourName(SR_UTILS_NS::StringAtom name, ManagerPasskey) { m_behaviourName = name; }
        void SetModuleName(SR_UTILS_NS::StringAtom name, ManagerPasskey) { m_moduleName = name; }
        void SetReloadCallback(const ReloadCallback& callback) { m_reloadCallback = callback; }

        void OnBehaviourUnloaded(ManagerPasskey);

        void Awake() { if (m_pBehaviour) { m_pBehaviour->Awake(); } }
        void OnEnable() { if (m_pBehaviour) { m_pBehaviour->OnEnable(); } }
        void OnDisable() { if (m_pBehaviour) { m_pBehaviour->OnDisable(); } }
        void OnAttached() { if (m_pBehaviour) { m_pBehaviour->OnAttached(); } }
        void OnDetached() { if (m_pBehaviour) { m_pBehaviour->OnDetached(); } }
        void OnDestroy() { if (m_pBehaviour) { m_pBehaviour->OnDestroy(); } }
        void Start() { if (m_pBehaviour) { m_pBehaviour->Start(); } }
        void FixedUpdate() { if (m_pBehaviour) { m_pBehaviour->FixedUpdate(); } }
        void Update(float_t dt) { if (m_pBehaviour) { m_pBehaviour->Update(dt); } }

        void SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject);

        SR_NODISCARD bool IsValid() const { return m_pBehaviour; }
        SR_NODISCARD bool ExecuteInEditMode() const;

        void SetInstance(const SR_HTYPES_NS::SharedPtr<CppBehaviour>& pBehaviour, ManagerPasskey) {
            m_pBehaviour = pBehaviour;
        }

    private:
        SR_SCRIPTING_NS::CppBehaviour::Ptr m_pBehaviour;
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

    private:
        bool AllocateBehaviourInternalInstance(CppBehaviourInstance* pInstance);
        void FreeBehaviourInternalInstance(CppBehaviourInstance* pInstance);

        SR_NODISCARD void* LoadModule(const SR_UTILS_NS::Path& modulePath);
        bool UnloadModule(ScriptModule& module);
        void OnModuleLoaded(ScriptModule& module);

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
