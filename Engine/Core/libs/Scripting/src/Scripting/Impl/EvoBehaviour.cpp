//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    EvoBehaviour::~EvoBehaviour() {
        SRAssert(!m_script);
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

            m_script = EvoScript::Script::Allocate(path, compiler.GetGenerator()->GetAddresses());

            auto&& fullPath = GetAssociatedPath().Concat(path);
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

        SetGameObject();

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

        if (path.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            if (auto&& hash = path.GetFolderHash(); hash != SR_UINT64_MAX) {
                return hash;
            }
        }

        SRHalt("Failed to get behaviour hash! \n\tResource id: " + std::string(GetResourceId()) +
               "\n\tResource path: " + path.ToString());

        return 0;
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
        m_update = nullptr;
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

        if (m_releaseBehaviour) {
            m_releaseBehaviour();
        }

        DeInitHooks();

        SR_SAFE_DELETE_PTR(m_script)

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

        if (auto&& setter = m_script->GetFunction<SetGameObjectFnPtr>("SetGameObject")) {
            setter(GetGameObject());
        }
    }

    void EvoBehaviour::FixedUpdate() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_fixedUpdate) {
            m_fixedUpdate();
        }
        Behaviour::FixedUpdate();
    }
}