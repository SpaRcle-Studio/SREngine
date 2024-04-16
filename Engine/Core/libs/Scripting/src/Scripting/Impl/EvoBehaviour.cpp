//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    bool EvoBehaviour::Load() {
        SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

        if (m_script) {
            SR_ERROR("EvoBehaviour::Load() : script is already loaded!");
            return false;
        }

        m_hasErrors = false;

        if (auto&& path = GetResourcePath(); !path.empty()) {
            m_script = EvoScriptManager::Instance().Load(path);
        }

        if (!m_script) {
            SR_ERROR("EvoBehaviour::Load() : failed to load script!");
            return false;
        }

        SRAssert(!m_behaviourContext);

        InitHooks();
        SwitchContext();

        if (m_initBehaviour) {
            m_behaviourContext = m_initBehaviour();
        }

        if (!m_behaviourContext) {
            SR_ERROR("EvoBehaviour::Load() : failed to initialize behaviour context!");
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("EvoBehaviour::Load() : behaviour successfully initialized!");
        }

        return IRawBehaviour::Load();
    }

    bool EvoBehaviour::Unload() {
        SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

        bool hasErrors = !IRawBehaviour::Unload();

        DestroyScript();

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
        SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

        if (m_hasErrors) {
            return EvoBehaviour::Properties();
        }

        SwitchContext();

        if (!m_getProperties) {
            SR_ERROR("EvoBehaviour::GetProperties() : properties getter invalid!\n\tPath: " + GetResourcePath().ToStringRef());
            m_hasErrors = true;
            return EvoBehaviour::Properties();
        }

        return m_getProperties();
    }

    std::any EvoBehaviour::GetProperty(const std::string &id) const {
        SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

        SwitchContext();

        if (!m_getProperty) {
            SR_ERROR("EvoBehaviour::GetProperty() : property getter invalid!");
            return std::any();
        }

        std::any copy1 = m_getProperty(id);

        /// HACK: так как dll может выгрузиться, то RTTI типа в std::any станет невалидным,
        /// и это значение превратится в замедленную бомбу, потому что любое обращение к переменной
        /// вызовет краш. При перекопировании RTTI обновится на актуальный для самого приложения.
        std::any copy = copy1;

        return copy;
    }

    void EvoBehaviour::SetProperty(const std::string &id, const std::any &val) {
        SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

        SwitchContext();

        if (!m_setProperty) {
            return;
        }

        m_setProperty(id, val);
    }

    void EvoBehaviour::Awake() {
        CallFunction(m_awake, false);
    }

    void EvoBehaviour::OnEnable() {
        CallFunction(m_onEnable, false);
    }

    void EvoBehaviour::OnDisable() {
        CallFunction(m_onDisable, false);
    }

    void EvoBehaviour::Start() {
        CallFunction(m_start, false);
    }

    void EvoBehaviour::Update(float_t dt) {
        CallFunction(m_update, false, dt);
    }

    void EvoBehaviour::OnAttached() {
        SR_HTYPES_NS::Function<void()> fn = [this]() { SetGameObject(); };
        CallFunction(fn, false);
    }

    void EvoBehaviour::FixedUpdate() {
        CallFunction(m_fixedUpdate, false);
    }

    void EvoBehaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_collisionEnter, false, data);
    }

    void EvoBehaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_collisionStay, false, data);
    }

    void EvoBehaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_collisionExit, false, data);
    }

    void EvoBehaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_triggerEnter, false, data);
    }

    void EvoBehaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_triggerStay, false, data);
    }

    void EvoBehaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        CallFunction(m_triggerExit, false, data);
    }

    void EvoBehaviour::SetGameObject() {
        if (!m_component || !m_script || !m_component->HasParent()) {
            return;
        }

        SwitchContext();

        typedef void(*SetGameObjectFnPtr)(SR_UTILS_NS::GameObject::Ptr);
        typedef void(*SetSceneFnPtr)(SR_WORLD_NS::Scene*);

        if (auto&& gameObject = m_component->GetGameObject()) {
            if (auto&& setter = GetFunction<SetGameObjectFnPtr>("SetGameObject")) {
                setter(gameObject);
            }
        }
        else if (auto&& pScene = m_component->GetScene()) {
            if (auto&& setter = GetFunction<SetSceneFnPtr>("SetScene")) {
                setter(pScene);
            }
        }
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

    void EvoBehaviour::SwitchContext() const {
        if (m_switchContext) {
            m_switchContext(m_behaviourContext);
        }
    }

    void EvoBehaviour::OnTransformSet() {
        SR_HTYPES_NS::Function<void()> fn = [this]() { SetGameObject(); };
        CallFunction(fn, false);
    }

    void EvoBehaviour::OnDestroy() {
        SR_HTYPES_NS::Function<void()> fn = [this]() { DestroyScript(); };
        CallFunction(fn, false);
    }

    void EvoBehaviour::OnDetached() {

    }
}