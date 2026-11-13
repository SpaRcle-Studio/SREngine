//
// Created by Monika on 07.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
#define SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H

#include <Scripting/macros.h>
#include <Scripting/Base/BehaviourInstance.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/PassKey.h>
#include <Utils/ECS/SceneObject.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SR_SCRIPTING_NS {
    class ModuleManager;
    class CppScriptSystem;

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

    class SR_SCRIPTING_DLL_API CppBehaviourInstance : public BehaviourInstance {

    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetBehaviourName() const {
            return m_behaviourName;
        }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetModuleName() const {
            return m_moduleName;
        }

        SR_NODISCARD CppBehaviour::Ptr& GetBehaviour() {
            return m_pBehaviour;
        }

        SR_NODISCARD const CppBehaviour::Ptr& GetBehaviour() const {
            return m_pBehaviour;
        }

        void SetBehaviourName(SR_UTILS_NS::StringAtom name, SR_UTILS_NS::PassKey<ModuleManager>) {
            m_behaviourName = name;
        }

        void SetModuleName(SR_UTILS_NS::StringAtom name, SR_UTILS_NS::PassKey<ModuleManager>) {
            m_moduleName = name;
        }

        void OnBehaviourUnloaded(SR_UTILS_NS::PassKey<ModuleManager>);

        void Awake() override {
            if (m_pBehaviour) {
                m_pBehaviour->Awake();
            }
        }

        void OnEnable() override {
            if (m_pBehaviour) {
                m_pBehaviour->OnEnable();
            }
        }

        void OnDisable() override {
            if (m_pBehaviour) {
                m_pBehaviour->OnDisable();
            }
        }

        void OnAttached() override {
            if (m_pBehaviour) {
                m_pBehaviour->OnAttached();
            }
        }

        void OnDetached() override {
            if (m_pBehaviour) {
                m_pBehaviour->OnDetached();
            }
        }

        void OnDestroy() override {
            if (m_pBehaviour) {
                m_pBehaviour->OnDestroy();
            }
        }

        void Start() override {
            if (m_pBehaviour) {
                m_pBehaviour->Start();
            }
        }

        void FixedUpdate() override {
            if (m_pBehaviour) {
                m_pBehaviour->FixedUpdate();
            }
        }

        void Update(float_t dt) override {
            if (m_pBehaviour) {
                m_pBehaviour->Update(dt);
            }
        }

        SR_NODISCARD CppBehaviour* GetCppBehaviour() const override {
            return const_cast<CppBehaviour*>(m_pBehaviour.Get());
        }

        SR_NODISCARD SR_UTILS_NS::SRClass* GetPropertiesObject() const override {
            return (Utils::SRClass*)m_pBehaviour.Get();
        }

        void Save(SR_UTILS_NS::ISerializer& serializer) const override {
            if (m_pBehaviour) {
                m_pBehaviour->Save(serializer);
            }
        }

        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override {
            return m_pBehaviour && m_pBehaviour->Load(deserializer);
        }

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnCollisionEnter(data);
            }
        }

        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnCollisionStay(data);
            }
        }

        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnCollisionExit(data);
            }
        }

        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnTriggerEnter(data);
            }
        }

        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnTriggerStay(data);
            }
        }

        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override {
            if (m_pBehaviour) {
                m_pBehaviour->OnTriggerExit(data);
            }
        }

        void SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) override;

        SR_NODISCARD bool IsValid() const override {
            return m_pBehaviour;
        }

        SR_NODISCARD bool ExecuteInEditMode() const override;

        void SetInstance(const SR_HTYPES_NS::SharedPtr<CppBehaviour>& pBehaviour, SR_UTILS_NS::PassKey<ModuleManager>) {
            m_pBehaviour = pBehaviour;
        }

    private:
        SR_SCRIPTING_NS::CppBehaviour::Ptr m_pBehaviour;
        SR_UTILS_NS::StringAtom m_moduleName;
        SR_UTILS_NS::StringAtom m_behaviourName;

    };


    class SR_SCRIPTING_DLL_API ModuleManager : public SR_HTYPES_NS::SharedPtr<ModuleManager> {
        using Super = SR_HTYPES_NS::SharedPtr<ModuleManager>;
    public:
        ModuleManager(CppScriptSystem* pScriptSystem)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_pScriptSystem(pScriptSystem)
        { }

        ~ModuleManager() override;

    public:
        bool Init();

        SR_NODISCARD bool ReloadModule(const SR_UTILS_NS::Path& path);
        SR_NODISCARD bool IsRuntimeModule(SR_UTILS_NS::StringAtom name);

        SR_NODISCARD CppBehaviourInstance* AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName);
        void FreeBehaviourInstance(CppBehaviourInstance* pInstance);

    private:
        bool AllocateBehaviourInternalInstance(CppBehaviourInstance* pInstance);
        void FreeBehaviourInternalInstance(CppBehaviourInstance* pInstance);

        SR_NODISCARD void* LoadModule(const SR_UTILS_NS::Path& modulePath);
        bool UnloadModule(ScriptModule& module, bool willBeReloaded);
        void OnModuleLoaded(ScriptModule& module);

        SR_NODISCARD ScriptModule* FindModule(SR_UTILS_NS::StringAtom moduleName);

    private:
        SR_UTILS_NS::Path m_resourcesPath;
        SR_UTILS_NS::Path m_cachePath;

        SR_UTILS_NS::String m_lastCompilerVersion;

        SR_UTILS_NS::Set<CppBehaviourInstance*> m_behaviourInstances;

        SR_UTILS_NS::Vector<ScriptModule> m_modules;
        std::recursive_mutex m_mutex;
        CppScriptSystem* m_pScriptSystem = nullptr;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_MODULE_MANAGER_H
