//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>
#include <Scripting/Impl/EvoScriptManager.h>

namespace SR_SCRIPTING_NS {
    bool EvoBehaviour::Load() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_script) {
            SR_ERROR("EvoBehaviour::Load() : script is already loaded!");
            return false;
        }

        m_hasErrors = false;

        if (auto&& path = GetResourcePath(); !path.empty()) {
            m_script = EvoScriptManager::Instance().Load(path);
        }

        SRAssert(!m_behaviourContext);

        InitHooks();
        SwitchContext();

        if (m_initBehaviour) {
            m_behaviourContext = m_initBehaviour();
        }

        if (!m_behaviourContext) {
            SR_ERROR("Failed to initialize behaviour context!");
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("EvoBehaviour::Load() : behaviour successfully initialized!");
        }

        return Behaviour::Load();
    }

    bool EvoBehaviour::Unload() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        bool hasErrors = !Behaviour::Unload();

        DestroyScript();

        /// чтобы скрипт занаво отработал логику после перезагрузки,
        /// делаем такой маневр
        m_isStarted = false;
        m_isAwake = false;

        return !hasErrors;
    }

    uint64_t EvoBehaviour::GetFileHash() const {
        auto&& path = SR_UTILS_NS::Path(GetResourcePath());

        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        path = path.GetWithoutExtension();

        auto&& cpp = path.ConcatExt("cpp");
        auto&& header = path.ConcatExt("h");

        uint64_t hash = 0;

        if (cpp.Exists(SR_UTILS_NS::Path::Type::File)) {
            if (auto&& fileHash = cpp.GetFileHash(); hash != SR_UINT64_MAX) {
                hash = SR_UTILS_NS::CombineTwoHashes(hash, fileHash);
            }
        }

        if (header.Exists(SR_UTILS_NS::Path::Type::File)) {
            if (auto&& fileHash = header.GetFileHash(); hash != SR_UINT64_MAX) {
                hash = SR_UTILS_NS::CombineTwoHashes(hash, fileHash);
            }
        }

        return hash;
    }

    void EvoBehaviour::DeInitHooks() {
        m_initBehaviour = nullptr;
        m_switchContext = nullptr;
        m_releaseBehaviour = nullptr;
        m_getProperties = nullptr;
        m_getProperty = nullptr;
        m_setProperty = nullptr;
        m_awake = nullptr;
        m_onEnable = nullptr;
        m_onDisable = nullptr;
        m_start = nullptr;
        m_fixedUpdate = nullptr;
        m_update = nullptr;
        m_collisionEnter = nullptr;
        m_collisionStay = nullptr;
        m_collisionExit = nullptr;
        m_triggerEnter = nullptr;
        m_triggerStay = nullptr;
        m_triggerExit = nullptr;
    }

    void EvoBehaviour::InitHooks() {
        m_initBehaviour = GetFunction<EvoScript::Typedefs::InitBehaviourFnPtr>("InitBehaviour");
        m_switchContext = GetFunction<EvoScript::Typedefs::SwitchContextFnPtr>("SwitchContext");
        m_releaseBehaviour = GetFunction<EvoScript::Typedefs::ReleaseBehaviourFnPtr>("ReleaseBehaviour");
        m_getProperties = GetFunction<EvoScript::Typedefs::GetPropertiesFnPtr>("GetProperties");
        m_getProperty = GetFunction<EvoScript::Typedefs::GetPropertyFnPtr>("GetProperty");
        m_setProperty = GetFunction<EvoScript::Typedefs::SetPropertyFnPtr>("SetProperty");

        m_awake = GetFunction<EvoScript::Typedefs::AwakeFnPtr>("Awake");
        m_onEnable = GetFunction<EvoScript::Typedefs::OnEnableFnPtr>("OnEnable");
        m_onDisable = GetFunction<EvoScript::Typedefs::OnDisableFnPtr>("OnDisable");
        m_start = GetFunction<EvoScript::Typedefs::StartFnPtr>("Start");
        m_update = GetFunction<EvoScript::Typedefs::UpdateFnPtr>("Update");
        m_fixedUpdate = GetFunction<EvoScript::Typedefs::FixedUpdateFnPtr>("FixedUpdate");

        m_collisionEnter = GetFunction<CollisionFnPtr>("OnCollisionEnter");
        m_collisionStay = GetFunction<CollisionFnPtr>("OnCollisionStay");
        m_collisionExit = GetFunction<CollisionFnPtr>("OnCollisionExit");
        m_triggerEnter = GetFunction<CollisionFnPtr>("OnTriggerEnter");
        m_triggerStay = GetFunction<CollisionFnPtr>("OnTriggerStay");
        m_triggerExit = GetFunction<CollisionFnPtr>("OnTriggerExit");
    }

    EvoBehaviour::Properties EvoBehaviour::GetProperties() const {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_hasErrors) {
            return EvoBehaviour::Properties();
        }

        SwitchContext();

        if (!m_getProperties) {
            SR_ERROR("EvoBehaviour::GetProperties() : properties getter invalid!");
            return EvoBehaviour::Properties();
        }

        return m_getProperties();
    }

    std::any EvoBehaviour::GetProperty(const std::string &id) const {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (!m_getProperty) {
            SR_ERROR("EvoBehaviour::GetProperty() : property getter invalid!");
            return std::any();
        }

        std::any copy1 = m_getProperty(id);
        std::any copy = copy1;
        return copy;
    }

    void EvoBehaviour::SetProperty(const std::string &id, const std::any &val) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (!m_setProperty) {
            return;
        }

        m_setProperty(id, val);
    }

    void EvoBehaviour::Awake() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_awake) {
            m_awake();
        }
        Behaviour::Awake();
    }

    void EvoBehaviour::OnEnable() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_onEnable) {
            m_onEnable();
        }
        Behaviour::OnEnable();
    }

    void EvoBehaviour::OnDisable() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_onDisable) {
            m_onDisable();
        }
        Behaviour::OnDisable();
    }

    void EvoBehaviour::Start() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_start) {
            m_start();
        }
        Behaviour::Start();
    }

    void EvoBehaviour::Update(float_t dt) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_update) {
            m_update(dt);
        }
        Behaviour::Update(dt);
    }

    void EvoBehaviour::OnAttached() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SetGameObject();

        Behaviour::OnAttached();
    }

    void EvoBehaviour::SetGameObject() {
        if (!m_script) {
            return;
        }

        SwitchContext();

        typedef void(*SetGameObjectFnPtr)(SR_UTILS_NS::GameObject::Ptr);
        typedef void(*SetSceneFnPtr)(SR_WORLD_NS::Scene::Ptr);

        if (auto&& gameObject = GetGameObject()) {
            if (auto&& setter = GetFunction<SetGameObjectFnPtr>("SetGameObject")) {
                setter(gameObject);
            }
        }
        else if (auto&& pScene = GetScene()) {
            if (auto&& setter = GetFunction<SetSceneFnPtr>("SetScene")) {
                setter(pScene->GetThis());
            }
        }
    }

    void EvoBehaviour::FixedUpdate() {
        SRAssert(!IsDestroyed());

        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_fixedUpdate) {
            m_fixedUpdate();
        }
        Behaviour::FixedUpdate();
    }

    void EvoBehaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_collisionEnter) {
            m_collisionEnter(data);
        }
        Behaviour::OnCollisionEnter(data);
    }

    void EvoBehaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_collisionStay) {
            m_collisionStay(data);
        }
        Behaviour::OnCollisionStay(data);
    }

    void EvoBehaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_collisionExit) {
            m_collisionExit(data);
        }
        Behaviour::OnCollisionExit(data);
    }

    void EvoBehaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_triggerEnter) {
            m_triggerEnter(data);
        }
        Behaviour::OnTriggerEnter(data);
    }

    void EvoBehaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_triggerStay) {
            m_triggerStay(data);
        }
        Behaviour::OnTriggerStay(data);
    }

    void EvoBehaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData &data) {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SwitchContext();

        if (m_triggerExit) {
            m_triggerExit(data);
        }
        Behaviour::OnTriggerExit(data);
    }

    void EvoBehaviour::DestroyScript() {
        SwitchContext();

        if (m_releaseBehaviour) {
            m_releaseBehaviour();
        }

        DeInitHooks();

        m_behaviourContext = nullptr;

        m_script = ScriptHolder::Ptr();
    }

    void EvoBehaviour::OnTransformSet() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SetGameObject();
        Component::OnTransformSet();
    }

    void EvoBehaviour::SwitchContext() const {
        if (m_switchContext) {
            m_switchContext(m_behaviourContext);
        }
    }

    void EvoBehaviour::OnDestroy() {
        auto&& lockGuard = EvoScriptManager::ScopeLockSingleton();
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        DestroyScript();

        Behaviour::OnDestroy();
    }
}