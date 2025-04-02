

# File EvoBehaviour.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Impl**](dir_24f2b9252cbd3f2e0c4afbfdbb5b103e.md) **>** [**EvoBehaviour.h**](EvoBehaviour_8h.md)

[Go to the documentation of this file](EvoBehaviour_8h.md)


```C++
//
// Created by Monika on 24.05.2022.
//

#ifndef SR_ENGINE_EVOBEHAVIOUR_H
#define SR_ENGINE_EVOBEHAVIOUR_H

#include <Scripting/Base/Behaviour.h>
#include <Scripting/ScriptHolder.h>
#include <Scripting/Impl/EvoScriptManager.h>

namespace SR_SCRIPTING_NS {
    typedef void(*CollisionFnPtr)(const SR_UTILS_NS::CollisionData& data);

    class EvoBehaviour : public SR_SCRIPTING_NS::IRawBehaviour {
        using Properties = std::vector<std::string>;
        using Super = SR_SCRIPTING_NS::IRawBehaviour;
    public:
        EvoBehaviour()
            : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(EvoBehaviour))
        { }

    public:
        Properties GetProperties() const override;
        std::any GetProperty(const std::string& id) const override;
        void SetProperty(const std::string& id, const std::any& val) override;

        void SetComponent(Behaviour* pBehaviour) override {
            Super::SetComponent(pBehaviour);
            SetGameObject();
        }

    protected:
        void Awake() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDetached() override;
        void Start() override;
        void Update(float_t dt) override;
        void FixedUpdate() override;
        void OnDestroy() override;

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override;

        void OnTransformSet() override;

        bool Load() override;
        bool Unload() override;
        SR_NODISCARD uint64_t GetFileHash() const override;

    private:
        template<typename T, typename ...Args> void CallFunction(T function, bool ignoreLoadState, Args&&... args) {
            if (!ignoreLoadState && GetResourceLoadState() != LoadState::Loaded) {
                return;
            }

            SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT

            SwitchContext();

            if (function) {
                function(std::forward<Args>(args)...);
            }
        }

        void InitHooks();
        void DeInitHooks();
        void SetGameObject();
        void DestroyScript();
        void SwitchContext() const;

        template<typename T> T GetFunction(const char* name) const {
            return m_script->GetScript<EvoScript::Script>()->GetFunction<T>(name);
        }

    private:
        ScriptHolder::Ptr m_script;
        void* m_behaviourContext = nullptr;

        EvoScript::Typedefs::AwakeFnPtr m_awake = nullptr;
        EvoScript::Typedefs::OnEnableFnPtr m_onEnable = nullptr;
        EvoScript::Typedefs::OnDisableFnPtr m_onDisable = nullptr;
        EvoScript::Typedefs::StartFnPtr m_start = nullptr;
        EvoScript::Typedefs::UpdateFnPtr m_update = nullptr;
        EvoScript::Typedefs::FixedUpdateFnPtr m_fixedUpdate = nullptr;

        CollisionFnPtr m_collisionEnter = nullptr;
        CollisionFnPtr m_collisionStay = nullptr;
        CollisionFnPtr m_collisionExit = nullptr;
        CollisionFnPtr m_triggerEnter = nullptr;
        CollisionFnPtr m_triggerStay = nullptr;
        CollisionFnPtr m_triggerExit = nullptr;

        EvoScript::Typedefs::InitBehaviourFnPtr m_initBehaviour = nullptr;
        EvoScript::Typedefs::ReleaseBehaviourFnPtr m_releaseBehaviour = nullptr;
        EvoScript::Typedefs::SwitchContextFnPtr m_switchContext = nullptr;
        EvoScript::Typedefs::GetPropertiesFnPtr m_getProperties = nullptr;
        EvoScript::Typedefs::GetPropertyFnPtr m_getProperty = nullptr;
        EvoScript::Typedefs::SetPropertyFnPtr m_setProperty = nullptr;

    };
}

#endif //SR_ENGINE_EVOBEHAVIOUR_H
```


