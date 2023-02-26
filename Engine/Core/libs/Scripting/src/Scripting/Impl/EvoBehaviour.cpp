//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    EvoBehaviour::~EvoBehaviour() {
        DestroyScript();
    }

    bool EvoBehaviour::Load() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_script) {
            SR_ERROR("EvoBehaviour::Load() : script is already loaded!");
            return false;
        }

        m_hasErrors = false;

        auto&& path = GetResourcePath();

        if (!path.empty()) {
            auto&& compiler = GlobalEvoCompiler::Instance();

            m_script = EvoScript::Script::Allocate(path.GetWithoutExtension(), compiler.GetGenerator()->GetAddresses());

            auto&& fullPath = GetAssociatedPath().Concat(path).GetWithoutExtension();
            if (!m_script || !m_script->Load(fullPath, compiler, true)) {
                SR_ERROR("EvoBehaviour::Load() : failed to load script! \n\tPath: " + path.ToString());
                SR_SAFE_DELETE_PTR(m_script);
                m_hasErrors = true;
                return false;
            }
        }

        InitHooks();

        if (m_initBehaviour) {
            m_initBehaviour();
        }

        SR_LOG("EvoBehaviour::Load() : behaviour successfully initialized!");

        return Behaviour::Load();
    }

    bool EvoBehaviour::Unload() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        bool hasErrors = !Behaviour::Unload();

        if (m_releaseBehaviour) {
            m_releaseBehaviour();
        }

        DeInitHooks();

        SR_SAFE_DELETE_PTR(m_script)

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
        m_initBehaviour = m_script->GetFunction<EvoScript::Typedefs::InitBehaviourFnPtr>("InitBehaviour");
        m_releaseBehaviour = m_script->GetFunction<EvoScript::Typedefs::ReleaseBehaviourFnPtr>("ReleaseBehaviour");
        m_getProperties = m_script->GetFunction<EvoScript::Typedefs::GetPropertiesFnPtr>("GetProperties");
        m_getProperty = m_script->GetFunction<EvoScript::Typedefs::GetPropertyFnPtr>("GetProperty");
        m_setProperty = m_script->GetFunction<EvoScript::Typedefs::SetPropertyFnPtr>("SetProperty");

        m_awake = m_script->GetFunction<EvoScript::Typedefs::AwakeFnPtr>("Awake");
        m_onEnable = m_script->GetFunction<EvoScript::Typedefs::OnEnableFnPtr>("OnEnable");
        m_onDisable = m_script->GetFunction<EvoScript::Typedefs::OnDisableFnPtr>("OnDisable");
        m_start = m_script->GetFunction<EvoScript::Typedefs::StartFnPtr>("Start");
        m_update = m_script->GetFunction<EvoScript::Typedefs::UpdateFnPtr>("Update");
        m_fixedUpdate = m_script->GetFunction<EvoScript::Typedefs::FixedUpdateFnPtr>("FixedUpdate");

        m_collisionEnter = m_script->GetFunction<CollisionFnPtr>("OnCollisionEnter");
        m_collisionStay = m_script->GetFunction<CollisionFnPtr>("OnCollisionStay");
        m_collisionExit = m_script->GetFunction<CollisionFnPtr>("OnCollisionExit");
        m_triggerEnter = m_script->GetFunction<CollisionFnPtr>("OnTriggerEnter");
        m_triggerStay = m_script->GetFunction<CollisionFnPtr>("OnTriggerStay");
        m_triggerExit = m_script->GetFunction<CollisionFnPtr>("OnTriggerExit");
    }

    EvoBehaviour::Properties EvoBehaviour::GetProperties() const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_hasErrors) {
            return EvoBehaviour::Properties();
        }

        if (!m_getProperties) {
            SR_ERROR("EvoBehaviour::GetProperties() : properties getter invalid!");
            return EvoBehaviour::Properties();
        }

        return m_getProperties();
    }

    std::any EvoBehaviour::GetProperty(const std::string &id) const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (!m_getProperty) {
            SR_ERROR("EvoBehaviour::GetProperty() : property getter invalid!");
            return std::any();
        }

        std::any copy1 = m_getProperty(id);
        std::any copy = copy1;
        return copy;
    }

    void EvoBehaviour::SetProperty(const std::string &id, const std::any &val) {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (!m_setProperty) {
            return;
        }

        m_setProperty(id, val);
    }

    void EvoBehaviour::Awake() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_awake) {
            m_awake();
        }
        Behaviour::Awake();
    }

    void EvoBehaviour::OnEnable() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_onEnable) {
            m_onEnable();
        }
        Behaviour::OnEnable();
    }

    void EvoBehaviour::OnDisable() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_onDisable) {
            m_onDisable();
        }
        Behaviour::OnDisable();
    }

    void EvoBehaviour::Start() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_start) {
            m_start();
        }
        Behaviour::Start();
    }

    void EvoBehaviour::Update(float_t dt) {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_update) {
            m_update(dt);
        }
        Behaviour::Update(dt);
    }

    SR_HTYPES_NS::DataStorage EvoBehaviour::Stash() {
        auto&& data = Behaviour::Stash();

        if (m_script) {
            data.SetPointer(m_script);
            m_script = nullptr;
        }

        return std::move(data);
    }

    void EvoBehaviour::PopStash(const SR_HTYPES_NS::DataStorage &data) {
        if (auto&& pScript = data.GetPointerDef<EvoScript::Script>(nullptr)) {
            delete pScript;
        }

        Behaviour::PopStash(data);
    }

    void EvoBehaviour::OnDestroy() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        DestroyScript();

        Behaviour::OnDestroy();
    }

    void EvoBehaviour::OnAttached() {
        SetGameObject();
        Behaviour::OnAttached();
    }

    void EvoBehaviour::SetGameObject() {
        if (!m_script) {
            return;
        }

        typedef void(*SetGameObjectFnPtr)(SR_UTILS_NS::GameObject::Ptr);
        typedef void(*SetSceneFnPtr)(SR_WORLD_NS::Scene::Ptr);

        if (auto&& gameObject = GetGameObject()) {
            if (auto&& setter = m_script->GetFunction<SetGameObjectFnPtr>("SetGameObject")) {
                setter(gameObject);
            }
        }
        else if (auto&& pScene = GetScene()) {
            if (auto&& setter = m_script->GetFunction<SetSceneFnPtr>("SetScene")) {
                setter(pScene->GetThis());
            }
        }
    }

    void EvoBehaviour::FixedUpdate() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_fixedUpdate) {
            m_fixedUpdate();
        }
        Behaviour::FixedUpdate();
    }

    void EvoBehaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData &data) {
        if (m_collisionEnter) {
            m_collisionEnter(data);
        }
        Behaviour::OnCollisionEnter(data);
    }

    void EvoBehaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData &data) {
        if (m_collisionStay) {
            m_collisionStay(data);
        }
        Behaviour::OnCollisionStay(data);
    }

    void EvoBehaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData &data) {
        if (m_collisionExit) {
            m_collisionExit(data);
        }
        Behaviour::OnCollisionExit(data);
    }

    void EvoBehaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData &data) {
        if (m_triggerEnter) {
            m_triggerEnter(data);
        }
        Behaviour::OnTriggerEnter(data);
    }

    void EvoBehaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData &data) {
        if (m_triggerStay) {
            m_triggerStay(data);
        }
        Behaviour::OnTriggerStay(data);
    }

    void EvoBehaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData &data) {
        if (m_triggerExit) {
            m_triggerExit(data);
        }
        Behaviour::OnTriggerExit(data);
    }

    void EvoBehaviour::DestroyScript() {
        if (m_releaseBehaviour) {
            m_releaseBehaviour();
        }

        DeInitHooks();

        SR_SAFE_DELETE_PTR(m_script)
    }

    void EvoBehaviour::OnTransformSet() {
        SetGameObject();
        Component::OnTransformSet();
    }
}